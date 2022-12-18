#ifndef ProgramMgr_h
#define ProgramMgr_h

#include "DataStore.h"
#include "Piece.h"
#include "LightsMgr.h"
#include "Arduino.h"

class ProgramMgr{

private:
	std::vector<Piece> _pieceArray;
	std::vector<DataStore> _progDataArray;
	DataStore _progData;
	LightsMgr* _lightsMgr;

	std::string _startPos = "0";
	std::string _endPos = "300";

	void _playProgram(int progNr);
	void _playSinglePiece(DataStore data);
	void _playSinglePiece(int pNr);
	void processPiceArray();

public:
	ProgramMgr();
	ProgramMgr(std::vector<Piece> pieceArray, DataStore data, LightsMgr *lightsMgr);
	
	void Init(std::string _endPos);
	void Init(std::string _startPos, std::string _endPos);


	void addToProgram(DataStore* data);

	void process(DataStore* data);

};
#endif
 