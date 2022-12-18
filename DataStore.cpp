#include "DataStore.h"

DataStore::DataStore(){
}


void DataStore::set(string paramName, string paramValue){

    _dataNames.push_back(paramName); 
    _dataValues.push_back(paramValue);

}
    
string DataStore::getValue(string paramName){

    string result;

    int length = _dataNames.size();

    for(int i = 0; i < length; i++){
        if(_dataNames[i] == paramName){
            result = _dataValues[i];
            break;
        }
    }

    return result;
}


string DataStore::getName(int index){

    return _dataNames.at(index);
}



string DataStore::getValue(int index){

    return _dataValues.at(index);
}

bool DataStore::hasData(){
    return getLength() > 0;
}

string DataStore::hasThisData(string paramName){
    int length = _dataNames.size();


    for(int i = 0; i < length; i++){
        if(_dataNames[i] == paramName){
            string out = std::to_string(i);
            return out;
        }
    }
    return "NODATA";
}



int DataStore::getLength(){

    return _dataValues.size();
}

void DataStore::erase(string paramName){
    auto toErase = std::find(_dataNames.begin(), _dataNames.end(), paramName);
    if (toErase != _dataNames.end()){
        _dataNames.erase(toErase); 
        _dataValues.erase(toErase);
    } 
}

void DataStore::clear(){

    _dataNames.clear();
    _dataValues.clear();
}

void DataStore::serialPrint(){
    if(hasData()){
        for(int i=0; i<getLength();i++){
        Serial.print(getName(i).c_str());
        Serial.print(i);
        Serial.print(":");
        Serial.println(getValue(i).c_str());
        }
    }
    else Serial.println("no Data");
}
