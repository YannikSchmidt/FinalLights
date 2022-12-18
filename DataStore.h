#ifndef DataStore_h
#define DataStore_h

#include "Arduino.h"
#include <string>
#include <iostream>


using std::string; using std::vector;

class DataStore{

private:

    vector<string> _dataNames;
    vector<string> _dataValues;

public:

    DataStore();

    void set(string paramName, string paramValue);
    string getValue(string paramName);
    string getName(int index);
    string getValue(int index);
    bool hasData();
    string hasThisData(string paramName);
    int getLength();
    void erase(string paramName);
    void clear();
    void serialPrint();

};
#endif