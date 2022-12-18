/*
 Name:		FinalLights.ino
 Created:	10.12.2022 21:28:37
 Author:	maily
*/

#include <Adafruit_NeoPixel.h>
#include "LightsMgr.h"
#include "DataStore.h"
#include "Piece.h"
#include "ProgramMgr.h"
#include <iostream>
#include "WifiMgr.h"
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>

#define LED_PIN     4
#define LED_COUNT  200

char SSID[] = "Angeldrive Studios 2,4";
char PSSWORD[] = "Garten123!";


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
LightsMgr lightsMgr(&strip, LED_PIN, LED_COUNT);

std::vector<Piece> pieceArray;
DataStore data = DataStore();
ProgramMgr progMgr = ProgramMgr(pieceArray, data, &lightsMgr);
ProgramMgr progMgr2 = ProgramMgr(pieceArray, data, &lightsMgr);


WiFiServer server(80);
WifiMgr wifiMgr = WifiMgr(SSID, PSSWORD, &server, &data);      //WifiMgr::WifiMgr(char ssid[], char password[], class WiFiServer *server, DataStore *data)


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	lightsMgr.Init();
	lightsMgr.setBackgroundColor(0, 0, 0);
	lightsMgr.clear();

	wifiMgr.Init();
	progMgr.Init("0", "200");


	Program(3);
}

// the loop function runs over and over again until power down or reset
void loop() {
	wifiMgr.Process();

	progMgr.process(&data);
}

void Program(int nr) {
	switch (nr)
	{
	case 1:
		data.set("cmd", "pProg");
		data.set("progNr", "1");
		break;
	case 2:
		data.set("cmd", "pProg");
		data.set("progNr", "2");
		break;
	case 3:
		data.set("cmd", "pProg");
		data.set("progNr", "3");
		break;
	case 4:
		data.set("cmd", "pProg");
		data.set("progNr", "4");
		break;

	default:
		break;
	}
}

int random(int min, int max) //range : [min, max]
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); //seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}
