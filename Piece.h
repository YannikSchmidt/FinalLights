#ifndef Piece_h
#define Piece_h

#include "LightsMgr.h"
#include "DataStore.h"
#include "Arduino.h"

class Piece{

private:
    int _prgNr;
    int _pos;

    int _clearBefore;
    int _showAfter;

    unsigned long _timeStamp = 0;
    int _isTime;
    int _timeDelay;

    void _processColors(DataStore* progData);

    LightsMgr* _lightsMgr;
    Adafruit_NeoPixel* _strip;
    std::vector<uint32_t> colors;

public:
    //LightAction(LightsMgr *lightsMgr, int prgNr);

    Piece(class LightsMgr *lightsMgr);
    
    void init(DataStore *ProgMgr);       //class DataStore *progData 

    void process();

    int startPos;
    int endPos;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    int Hz;
    int length = 5;
    int speed = 1;
    bool fade = true;

    //~Piece();
};
#endif
 