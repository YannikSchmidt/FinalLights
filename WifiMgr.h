#ifndef WifiMgr_h
#define WifiMgr_h

//  Initialiesierung:
//  bei verwendung eines Esp32:
// #define useEsp32
//  zum anzeigen des verbindungsstatuses auf einer Lichterkette:
//#include "LightsMgr.h"


#ifdef useEsp32
#include "WiFi.h"
#else
#include "ESP8266WiFi.h"
#endif
#include "DataStore.h"




#include <iostream>
#include <string>
#include <vector>

using std::string; using std::vector;

/*
using std::cout; using std::cin;
using std::endl;
using std::istringstream;
*/

class WifiMgr {

private:

    char* _ssid;
    char* _password;
//    LightsMgr* _lightsMgr;
    DataStore* _data;
    WiFiServer* _server;
    vector<string> split(string text, string delimiter);

public:

    WifiMgr(char ssid[], char password[], class LightsMgr *strip, class WiFiServer *server, DataStore *data);
    WifiMgr(char ssid[], char password[], class WiFiServer *server, DataStore * data);

    boolean HasData;
    vector<string> ParamNames;
    vector<string> ParamValues;

    void Init();
    void Process();

    void get(string url, string content);
    void post(string url, string content);

    void webPage01(WiFiClient client);
    void processInput(string);

};
#endif
