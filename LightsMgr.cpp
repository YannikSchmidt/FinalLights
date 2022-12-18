
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "LightsMgr.h"
    
LightsMgr::LightsMgr(class Adafruit_NeoPixel *strip, int pin, int pixelAmount) {

    _pin = pin;
    _pixelAmount = pixelAmount;
    _strip = strip;
    _lastTime = 0;

}

bool LightsMgr::_isTime(int time) {
    if (millis() > _lastTime + time) {
        _lastTime = millis();
        return true;
    }
    else return false;
}

void LightsMgr::_packedRGBtoRGB(uint8_t& r, uint8_t& g, uint8_t& b, uint32_t color) {
    r = (color & 0xFF0000) / 0x010000;
    g = (color & 0x00FF00) / 0x000100;
    b = (color & 0x0000FF);
}

void LightsMgr::Init() {

    _strip->begin();
    _strip->setBrightness(100);
    _strip->show();
    _pixelPos = 0;
    _backgroundColor = _strip->Color(0, 0, 0);
}



Adafruit_NeoPixel* LightsMgr::Strip(){
    return _strip;
}



void LightsMgr::show(){
    _strip->show();
}



int LightsMgr::getPixelAmount(){
    return _pixelAmount;
}



void LightsMgr::setOnePixel(int r, int g, int b) {

    _strip->setPixelColor(_pixelPos, _strip->Color(r, g, b));
    _strip->show();

    _pixelPos++;
    if (_pixelPos > _pixelAmount - 1){
        _pixelPos = _pixelAmount - 1;
    }
}

void LightsMgr::setOnePixel(int pixelPos, int r, int g, int b) {

    _pixelPos = pixelPos;

    setOnePixel(r, g, b);

}



void LightsMgr::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b) {
    _backgroundColor = _strip->Color(r, g, b);
    clear();
}



void LightsMgr::clear() {

    clear(0, _pixelAmount, true);
}

void LightsMgr::clear(bool show) {

    clear(0, _pixelAmount, show);
}

void LightsMgr::clear(int startPos, int endPos) {

    clear(0, _pixelAmount, true);
}

void LightsMgr::clear(int startPos, int endPos, bool show) {

    for (int i = startPos; i < endPos; i++) {
        _strip->setPixelColor(i, _backgroundColor);    
    }

    if(show) _strip->show();
   _pixelPos = 0;
}



void LightsMgr::setStripColor(uint8_t r, uint8_t g, uint8_t b) {

    setStripColor(true, 0, _pixelAmount, r, g, b);
}

void LightsMgr::setStripColor(bool show, uint8_t r, uint8_t g, uint8_t b) {

    setStripColor(show, 0, _pixelAmount, r, g, b);

}

void LightsMgr::setStripColor(bool show, int startPos, int endPos, uint8_t r, uint8_t g, uint8_t b) {

    for (int i = startPos; i < endPos; i++) {
        _strip->setPixelColor(i, r, g, b);
    }
    if(show) _strip->show();
}



void LightsMgr::strobo(int Hz){
    if (_isTime(Hz)) strobo(true, 0, _pixelAmount, 0, 0, 0);
    else            strobo(false, 0, _pixelAmount, 0, 0, 0);
}

void LightsMgr::strobo(int Hz, uint8_t r, uint8_t g, uint8_t b){
    if (_isTime(Hz)) strobo(true, 0, _pixelAmount, r, g, b);
    else            strobo(false, 0, _pixelAmount, r, g, b);
}

void LightsMgr::strobo(bool move, int startPos, int endPos, uint8_t r, uint8_t g, uint8_t b){
 
    if(_stToggle == true){
        setStripColor(false, startPos, endPos, r, g, b);
    }
    if(move){
        _stToggle = !_stToggle;
    }
}


void LightsMgr::snake(int length, int speed, uint8_t r, uint8_t g, uint8_t b){

    uint32_t color = _strip->Color(r, g, b);

    static int pos;


  for(int a = pos; a <= pos + length; a++){
    _strip->setPixelColor(a, color);
  }

  pos = pos + speed;

    if(pos > _pixelAmount + length){
        pos = 0;
    }
    
}


bool LightsMgr::snake(int& pos, int start, int end, uint8_t r, uint8_t g, uint8_t b, int length, int speed, bool move){

    return snake(pos, start, end, r, g, b, length, speed, false, move);

}

bool LightsMgr::snake(int& pos, int start, int end, uint8_t r, uint8_t g, uint8_t b, int length, int speed, bool fade, bool move) {

    uint32_t color = _strip->Color(r, g, b);

    if (pos < start) {
        pos = end;
    }

    if (pos > end) {
        pos = start;
    }

    if (speed > 0) {
        for (int a = pos; a > pos - length; a--) {

            int pixelPos = a;
            if (pixelPos < start) pixelPos = end + pixelPos - start;

            if (fade) {
                uint8_t fade = 255 * (a - pos) / length;
                uint32_t curentColor = _strip->getPixelColor(pixelPos);
                uint32_t fadeColor = _fade(color, curentColor, fade);
                _strip->setPixelColor(pixelPos, fadeColor);
            }
            else {
                _strip->setPixelColor(pixelPos, color);
            }
        }
    }else {
        for (int a = pos; a <= pos + length; a++) {

            int pixelPos = a;
            if (pixelPos >= end) pixelPos = start + pixelPos - end;

            if (fade) {
                uint8_t fade = 255 * (a - pos) / length;
                uint32_t curentColor = _strip->getPixelColor(pixelPos);
                uint32_t fadeColor = _fade(curentColor, color, fade);
                _strip->setPixelColor(pixelPos, fadeColor);
            }
            else {
                _strip->setPixelColor(pixelPos, color);
            }
        }
    }

    if (move) pos = pos + speed;

    if (pos > end - length) {
        return true;      // loop ready
    }
    else {
        return false;     // loop not ready
    }

}

void LightsMgr::RGB_DEBUG(uint32_t color) {
    uint8_t DebugR;
    uint8_t DebugG;
    uint8_t DebugB;
    _packedRGBtoRGB(DebugR, DebugG, DebugB, color);
    Serial.print(DebugR); Serial.print("  "); Serial.print(DebugG); Serial.print("  "); Serial.println(DebugB);
}

uint32_t LightsMgr::_fade(uint32_t endColor, uint32_t startColor, uint8_t fade) {
    uint8_t startR;
    uint8_t startG;
    uint8_t startB;
    uint8_t endR;
    uint8_t endG;
    uint8_t endB;
    _packedRGBtoRGB(startR, startG, startB, startColor);
    _packedRGBtoRGB(endR, endG, endB, endColor);
    uint8_t fadeR = _fadeValue(startR, endR, fade);
    uint8_t fadeG = _fadeValue(startG, endG, fade);
    uint8_t fadeB = _fadeValue(startB, endB, fade);

    //Serial.print("R:"); Serial.println(fadeR);   Serial.print("G:"); Serial.println(fadeG);    Serial.println("B:"); Serial.println(fadeB);


    return _strip->Color(fadeR, fadeG, fadeB);
}

uint8_t LightsMgr::_fadeValue(uint8_t start, uint8_t end, uint8_t fade) {
    uint8_t res;
    uint8_t dif;
    if (start > end) {
        dif = start - end;
        dif = dif * fade / 255;
        res = start - dif;
    } else {
        dif = end - start;
        dif = dif * fade / 255;
        res = start + dif;
    }
    return res;
}

void LightsMgr::rotate(int startPos, int endPos, int sigmentCount, std::vector<uint32_t> colors, int speed) {

    int segLength = (endPos - startPos) / sigmentCount;         // Anzahl LED pro Segment
    float segAngle = 360 / sigmentCount;                  // Anzahl Grad pro Segment
    float stepLength = (endPos - startPos) / 360.0;             // Anzahl LED pro Grad
    /*
    for (int k = startPos; k <= endPos; k++) {
        strip.setPixelColor(k, strip.Color(0, 0, 0));
    }
    */
    int pos = startPos + speed * stepLength;
    
    if (sigmentCount > colors.size()) {
        for (int i = 0; colors.size() > sigmentCount; ) {
            colors.push_back(colors[i]);
        }
    }

    for (int i = 0; i < segLength; i++) {

        for (int j = 0; j < sigmentCount; j++) {

            int pixelPos = pos + i + j * segLength;

            if (pixelPos > endPos) {
                pixelPos = startPos + pixelPos - endPos;
            }
            _strip->setPixelColor(pixelPos, colors[j]);
        }
    }
    speed++;

    if (speed >= 360 - 1) {
        speed = 0;
    }
}



void LightsMgr::rainbow(){

    rainbow(true);
}

void LightsMgr::rainbow(bool move){

    rainbow(move, 0, _pixelAmount, 1);
}

void LightsMgr::rainbow(bool move, int startPos, int endPos, int speed){

    static long firstPixelHue = 0;

    if(firstPixelHue > 5 * 65536){
    firstPixelHue = 0;
    }

    for(int i=startPos; i < endPos; i++) { // For each pixel in strip... _pixelAmount

    int pixelHue = firstPixelHue + (i * 65536L / endPos);

    _strip->setPixelColor(i, _strip->gamma32(_strip->ColorHSV(pixelHue)));
    }

    if(move) firstPixelHue += 256;

}

bool LightsMgr::endOfStrip() {
    return (_pixelPos >= _pixelAmount - 1);
}


