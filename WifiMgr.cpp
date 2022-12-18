#include "WifiMgr.h"

WifiMgr::WifiMgr(char ssid[], char password[], class LightsMgr *lightsMgr, class WiFiServer *server, DataStore *data) {

    _data = data;
    _ssid = ssid;
    _password = password;  
//    _lightsMgr = lightsMgr;
    _server = server;
    
    HasData = false;
}

WifiMgr::WifiMgr(char ssid[], char password[], class WiFiServer *server, DataStore *data) {
            
    _data = data;
    _ssid = ssid;
    _password = password;  
    _server = server;
    
    HasData = false;
}

void WifiMgr::Init() {

    //DataStore _wifiData = DataStore();

    Serial.println(_data->getLength());

    Serial.print("Connecting to ");    
    Serial.println(_ssid);
//    _lightsMgr->setOnePixel(255, 0, 0);

    WiFi.begin(_ssid, _password);

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
//        _lightsMgr->setOnePixel(0, 0, 255);
    }

    _server->begin();

    Serial.println("");
    Serial.println("WiFi connected.");
//    _lightsMgr->setOnePixel(0, 255, 0);
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void WifiMgr::Process() {

    WiFiClient client = _server->available();

    if (client) {
        string currentLine = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c != '\n' && c != '\r') {
                    currentLine += c;
                }else if (c == '\n'){
                    processInput(currentLine);
                    currentLine = "";
                    webPage01(client);
                    break;  // break out of the while loop:
                }
            }
        }
    }
}

void WifiMgr::post(string url, string content){

    
}

void WifiMgr::processInput(string currentLine) {

    size_t pos = currentLine.find("/data?");

    string httpString = "HTTP/1.1";
    string getString = "GET /data?";

    if (pos != string::npos)
    {
        HasData = true;

        pos = currentLine.find(httpString);

        if (pos != string::npos) {

            size_t sizeCL = currentLine.size();
            size_t sizeHT = httpString.size();
            size_t sizeGet = getString.size();

            sizeCL = sizeCL - sizeHT - sizeGet - 1;

            currentLine = currentLine.substr(sizeGet, sizeCL);
        }


    /*    Serial.print("currentLine: ");
        Serial.print(currentLine.c_str());
        Serial.println();
*/
        string text = currentLine;

        vector<string> array = split(text, "&");

        for (const auto& text : array) {

            vector<string> valueArray = split(text, "=");

            string paramName = valueArray.at(0);
            string paramValue = valueArray.at(1);

            //Serial.print("ParamName: "); Serial.println(paramName.c_str());

            _data->set(paramName, paramValue);
        }

        /*
        if(_data->getLength() > 0){
            for(int i = 0; i < _data->getLength(); i++){

                std::cout << "Wert: " + _data->getValue(i) + "\n";
            }
        }
        */
    }
}


void WifiMgr::webPage01(WiFiClient client) {

    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    // the content of the HTTP response follows the header:
    client.print("<a href=\"/data?cmd=pProg&progNr=1\"> <button>1</button></a>");
    client.print("<a href=\"/data?cmd=pProg&progNr=2\"> <button>2</button></a>");
    client.print("<a href=\"/data?cmd=pProg&progNr=3\"> <button>3</button></a>");

    client.print("<a href=\"/data?cmd=pPiece&progNr=2&green=255&length=30&speed=1&startPos=0&endPos=300&timeDelay=0\"> <button>Gr&uuml;n</button></a>");
    client.print("<a href=\"/data?cmd=pPiece&progNr=2&blue=255&length=30&speed=1&startPos=0&endPos=300&timeDelay=0\"> <button>Blau</button></a>");
    client.print("<a href=\"/data?cmd=iPiece&progNr=6\"> <button>Aus</button></a><br>");
    client.print("Hello, i'am an ESP click <a href=\"\/data?cmd=pProg&progNr=4\">here</a> to turn the strip white .<br>");
    client.print("Click <a href=\"/data?cmd=pProg&progNr=1\">here</a> to play program 1.<br>");
    client.print("Click <a href=\"/data?cmd=pProg&progNr=2\">here</a> to play program 2.<br>");
    client.print("Click <a href=\"/data?cmd=pProg&progNr=3\">here</a> to play program 3.<br>");
    client.print("Click <a href=\"/data?cmd=pPiece&progNr=2&red=255&length=30&speed=1&startPos=0&endPos=300&timeDelay=0\">here</a> to start a snake.<br>");
    client.print("Click <a href=\"/data?cmd=pPiece&progNr=4&red=255&blue=255&green=255&speed=1&startPos=0&endPos=300\">here</a> to start a strobo.<br>");
    client.print("Click <a href=\"/data?cmd=pPiece&progNr=3&startPos=0&endPos=300&timeDelay=0\">here</a> to start a rainbow.<br>");
    client.print("doku:<br>");
    client.print("to seee other efects, use the URL (chipsIP)/data?...  and seperate the parameters with &<br>");
    client.print("cmd: <br>");
    client.print("play a program = pProg <br>");
    client.print("play a piece = iPiece <br>");
    client.print("play a piece by Data = pPiece <br>");
    client.print("progNr: <br>");
    client.print("for pPiece <br>");
    client.print("1 = set the entire strip to <br>");
    client.print("2 = start a snake <br>");
    client.print("3 = do a rainbow efect <br>");
    client.print("4 = start a strobo <br>");
    client.print("5 = set a background color <br>");
    client.print("red: 0-255 <br>");
    client.print("green: 0-255 <br>");
    client.print("blue: 0-255 <br>");
    client.print("timeDelay: the time betwene the steps in ms (standard 100) <br>");
    client.print("startPos: the pixel were your Piece will start from <br>");
    client.print("endPos: the pixel were your Piece will end at <br>");
    client.print("lenght: the lenght of a snake <br>");
    client.print("fade: if or not your snake should fade at the end. <br>");
    client.print("example: /data?cmd=pPiece&progNr=2&red=255&blue=0&green=0&length=30&speed=-1&startPos=0&endPos=300&timeDelay=0 <br>");




















    //client.print("PixelAmound: <input type=PixelAmount>");
    //client.print("Programmnummer: <input type=ProgramNr >");
    // The HTTP response ends with another blank line:
    client.println();
}

vector<string> WifiMgr::split(string text, string delimiter) {

    string result = "";
    vector<string> words{};

    size_t pos;
    while ((pos = text.find(delimiter)) != string::npos) {
        words.push_back(text.substr(0, pos));
        text.erase(0, pos + delimiter.length());
    }
    words.push_back(text);

    return words;
}
