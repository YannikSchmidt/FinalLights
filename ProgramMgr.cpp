#include "ProgramMgr.h"

ProgramMgr::ProgramMgr() {}

ProgramMgr::ProgramMgr(std::vector<Piece> pieceArray, DataStore data, LightsMgr* lightsMgr) {
	_pieceArray = pieceArray;
	_progData = data;
	_lightsMgr = lightsMgr;
}

void ProgramMgr::Init(std::string endPos) {
	_endPos = endPos;
}


void ProgramMgr::Init(std::string startPos, std::string endPos) {
	_startPos = startPos;
	_endPos = endPos;
}

void ProgramMgr::_playProgram(int progNr) {

	_pieceArray.clear();

	switch (progNr)
	{
	case 1:
		_progDataArray.clear();
		_progData.set("progNr", "4");
		_progData.set("red", "255");
		_progData.set("green", "255");
		_progData.set("blue", "255");
		_progData.set("speed", "1");
		_progData.set("length", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "200");
		_progDataArray.push_back(_progData);
		_progData.clear();
		_progData.set("progNr", "2");
		_progData.set("red", "0");
		_progData.set("green", "255");
		_progData.set("blue", "255");
		_progData.set("speed", "1");
		_progData.set("length", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "1");
		_progDataArray.push_back(_progData);
		_progData.clear();
		_progData.set("progNr", "2");
		_progData.set("red", "255");
		_progData.set("green", "0");
		_progData.set("blue", "255");
		_progData.set("speed", "-1");
		_progData.set("length", "30");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "5");
		_progDataArray.push_back(_progData);
		_progData.clear();
		_progData.set("progNr", "2");
		_progData.set("red", "0");
		_progData.set("green", "0");
		_progData.set("blue", "255");
		_progData.set("speed", "1");
		_progData.set("length", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "5");
		_progDataArray.push_back(_progData);
		_progData.clear();
		break;
	case 2:
		_progDataArray.clear();
		_progData.clear();
		_progData.set("pos", "0");
		_progData.set("progNr", "2");
		_progData.set("red", "255");
		_progData.set("green", "0");
		_progData.set("blue", "0");
		_progData.set("speed", "1");
		_progData.set("length", "57");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "50");
		_progDataArray.push_back(_progData);
		_progData.clear();
		_progData.set("pos", "243");
		_progData.set("progNr", "2");
		_progData.set("red", "255");
		_progData.set("green", "255");
		_progData.set("blue", "255");
		_progData.set("speed", "1");
		_progData.set("length", "57");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "50");
		_progDataArray.push_back(_progData);
		_progData.clear();
		_progData.set("progNr", "2");
		_progData.set("red", "0");
		_progData.set("green", "255");
		_progData.set("blue", "255");
		_progData.set("speed", "1");
		_progData.set("length", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "0");
		_progDataArray.push_back(_progData);
		_progData.clear();
		_progData.set("progNr", "2");
		_progData.set("red", "255");
		_progData.set("green", "0");
		_progData.set("blue", "255");
		_progData.set("speed", "-1");
		_progData.set("length", "30");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "0");
		_progDataArray.push_back(_progData);
		_progData.clear();
		break;
	case 3:
		_progDataArray.clear();
		_progData.clear();
		_progData.set("pos", "0");
		_progData.set("progNr", "2");
		_progData.set("red", "255");
		_progData.set("green", "0");
		_progData.set("blue", "0");
		_progData.set("speed", "1");
		_progData.set("length", "100");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "0");
		_progDataArray.push_back(_progData);
		_progData.set("pos", "100");
		_progData.set("progNr", "2");
		_progData.set("red", "0");
		_progData.set("green", "0");
		_progData.set("blue", "255");
		_progData.set("speed", "1");
		_progData.set("length", "100");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "0");
		_progDataArray.push_back(_progData);
		_progData.clear();
		break;
	case 4:
		_progDataArray.clear();
		_progData.clear();
		_progData.set("progNr", "1");
		_progData.set("red", "255");
		_progData.set("green", "100");
		_progData.set("blue", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progDataArray.push_back(_progData);
		_progData.clear();
		break;

	default:
		break;
	}

	for (size_t i = 0; i < _progDataArray.size(); i++)
	{
		Piece lightPiece = Piece(_lightsMgr);
		lightPiece.init(&_progDataArray[i]);
		_pieceArray.push_back(lightPiece);
	}
	_progDataArray.clear();
}

void ProgramMgr::_playSinglePiece(DataStore data) {
	_progDataArray.push_back(data);

	for (size_t i = 0; i < _progDataArray.size(); i++)
	{
		Piece lightPiece = Piece(_lightsMgr);
		lightPiece.init(&_progDataArray[i]);
		_pieceArray.push_back(lightPiece);
	}
	data.clear();
	_progDataArray.clear();

}


void ProgramMgr::_playSinglePiece(int pNr) {

	if (pNr == 0) pNr = random(1, 8);

	switch (pNr)
	{
	case 1:
		_progData.set("progNr", "2");
		_progData.set("red", "255");
		_progData.set("speed", "1");
		_progData.set("length", "30");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "1");
		break;
	case 2:
		_progData.set("progNr", "2");
		_progData.set("blue", "255");
		_progData.set("speed", "-1");
		_progData.set("length", "30");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "1");
		break;
	case 3:
		_progData.set("progNr", "1");
		_progData.set("green", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		break;
	case 4:
		_progData.set("progNr", "1");
		_progData.set("blue", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		break;
	case 5:
		_progData.set("progNr", "4");
		_progData.set("red", "255");
		_progData.set("green", "255");
		_progData.set("blue", "255");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		break;
	case 6:
		_pieceArray.clear();
		break;
	case 7:
		_progData.set("progNr", "2");
		_progData.set("red", "255");
		_progData.set("blue", "255");
		_progData.set("speed", "1");
		_progData.set("length", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "3");
		break;
	case 8:
		_progData.set("progNr", "2");
		_progData.set("green", "50");
		_progData.set("blue", "255");
		_progData.set("speed", "-1");
		_progData.set("length", "50");
		_progData.set("startPos", _startPos);
		_progData.set("endPos", _endPos);
		_progData.set("timeDelay", "3");
		break;
	default:

		break;
	}
	_progDataArray.push_back(_progData);
	_progData.clear();

	for (size_t i = 0; i < _progDataArray.size(); i++)
	{
		Piece lightPiece = Piece(_lightsMgr);
		lightPiece.init(&_progDataArray[i]);
		_pieceArray.push_back(lightPiece);
	}
	_progDataArray.clear();
}


void ProgramMgr::addToProgram(DataStore* data) {

}

void ProgramMgr::process(DataStore* data) {
	if (data->hasData()) {
		if (data->getValue("cmd") == "pProg") {
			_playProgram(atoi(data->getValue("progNr").c_str()));
		}
		else if (data->getValue("cmd") == "pPiece") {
			_playSinglePiece(*data);
		}
		else if (data->getValue("cmd") == "iPiece") {
			_playSinglePiece(atoi(data->getValue("progNr").c_str()));
		}
		data->clear();
	}
	processPiceArray();
}

void ProgramMgr::processPiceArray() {
	_lightsMgr->clear(false);
	for (size_t i = 0; i < _pieceArray.size(); i++)
	{
		_pieceArray[i].process();
	}
	_lightsMgr->show();

	/*
	static unsigned long timeStamp = 0;
	if (millis() > timeStamp) {
		DataStoreFiller(0);
		loadProgram(dataArray);
		timeStamp = millis() + 20000;
	}
	*/
}