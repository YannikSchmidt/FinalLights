
#ifndef LightsMgr_h
#define LightsMgr_h
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class LightsMgr {

private:

    int _pin;
    int _pixelAmount;
    int _pixelPos;
    Adafruit_NeoPixel* _strip;
    uint32_t _backgroundColor;
    int _lastTime;
    bool _isTime(int Hz);
    bool _stToggle;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    void _packedRGBtoRGB(uint8_t& r, uint8_t& g, uint8_t& b, uint32_t color);
    uint32_t _fade(uint32_t stratColor, uint32_t endColor, uint8_t fade);
    uint8_t _fadeValue(uint8_t start, uint8_t end, uint8_t fade);
    void RGB_DEBUG(uint32_t color);

public:

    LightsMgr(class Adafruit_NeoPixel *strip, int pin, int pixelAmount);

    void Init();                                                        // Initialisierung

    int getPixelAmount();

    Adafruit_NeoPixel* Strip();

    void show();

    void setOnePixel(int r, int g, int b);                              // Setzt einen Pixel und z�hlt pixelPos++
    void setOnePixel(int pixelPos, int r, int g, int b);                // Setzt einen Pixel auf Pos pixelPos

    void clear();                                                       // Setzt alle Pixel auf BackgroundColor
    void clear(bool show);                                          // Setzt alle Pixel auf BackgroundColor
    void clear(int startPos, int endPos);
    void clear(int startPos, int endPos, bool show);

    void setStripColor(uint8_t r, uint8_t g, uint8_t b);                // Setzt den gesamten Streifen auf eine Farbe
    void setStripColor(bool Show, uint8_t r, uint8_t g, uint8_t b);
    void setStripColor(bool Show, int startPos, int endPos, uint8_t r, uint8_t g, uint8_t b);

    void strobo(int Hz);                                                // Lässt den Streifen im angegeben mHz takt Schwarz blinken
    void strobo(int Hz, uint8_t r, uint8_t g, uint8_t b);
    void strobo(bool move, int startPos, int endPos, uint8_t r, uint8_t g, uint8_t b);

    void snake(int length, int speed, uint8_t r, uint8_t g, uint8_t b);          // Macht eine Schlage an Pixeln mit der Länge length und der Geschwindigkeit speed
    bool snake(int& pos, int startPos, int endPos, uint8_t r, uint8_t g, uint8_t b,int length, int speed, bool move);  
    bool snake(int& pos, int startPos, int endPos, uint8_t r, uint8_t g, uint8_t b, int length, int speed, bool fade, bool move);

    void rotate(int startPos, int endPos, int sigmentCount, std::vector<uint32_t> colors, int speed);

    void rainbow();                                                              // Macht einen Regenbogen Farbverlauf über den ganzen Streifen
    void rainbow(bool move);
    void rainbow(bool move, int startPos, int endPos, int speed);

    void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b);           // Legt die Hintergrund Farbe fest
    bool endOfStrip();                                                  // Gibt true zur�ck wenn der die pixelPos am Ende des Streifens angekommen ist


};
#endif
