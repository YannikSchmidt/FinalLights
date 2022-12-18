#include "Piece.h"

Piece::Piece(class LightsMgr *lightsMgr) {      

    _lightsMgr = lightsMgr;
    _timeDelay = 100;
}

void Piece::init(class DataStore *progData){

    for(int i = 0; i < progData->getLength(); i++){

        string nameInput = progData->getName(i).c_str();

        if(nameInput == "red"){
            red = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "blue"){
            blue = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "green"){
            green = atoi(progData->getValue(i).c_str());
        }
        else if (nameInput == "pos") {
            _pos = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "length"){
            length = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "speed"){
            speed = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "timeDelay"){
            _timeDelay = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "startPos"){
            startPos = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "endPos"){
            endPos = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "progNr"){
            _prgNr = atoi(progData->getValue(i).c_str());
        }
        else if (nameInput == "fade") {
            fade = progData->getValue(i).c_str() == "true";
        }
        else if(nameInput == "clearBefore"){
            _clearBefore = atoi(progData->getValue(i).c_str());
        }
        else if(nameInput == "showAfter"){
            _showAfter = atoi(progData->getValue(i).c_str());
        }

        Serial.println(progData->getName(i).c_str());
        Serial.println(progData->getValue(i).c_str());
        
    }
}


void Piece::process(){

    int currentTime = millis();
    bool move;
    //if (_clearBefore == 1) _lightsMgr->clear(true);
    if(_timeDelay <= currentTime - _timeStamp){
        move = true;
        _timeStamp = millis();
    }else{
        move = false;
    }


    switch (_prgNr)
    {
    case 1:
        _lightsMgr->setStripColor(false,startPos, endPos, red, green,blue);
        break;
    case 2:
        _lightsMgr->snake(_pos, startPos, endPos, red, green, blue, length, speed, fade, move);
        break;
    case 3:
        _lightsMgr->rainbow(move,startPos, endPos, speed);
        break;
    case 4:
        _lightsMgr->strobo(move, startPos, endPos, red, green, blue);
        break;
    case 5:
        _lightsMgr->setBackgroundColor(red, green, blue);
        break;
    default:
        break;
    }
        

//    if (_showAfter == 1) _lightsMgr->show();
}

void Piece::_processColors(DataStore* progData) {
    for (int i = 0; progData->hasThisData("col1") != "NODATA"; i++) {

    }
}
