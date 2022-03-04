#pragma once
#include <iostream>

using std::string, std::cout;

class Address{
    public:
    string Addressline, City, State;
    string ZipCode;
    Address(string addressln,string city,string state ,string zip) {
        this->Addressline = addressln;
        this->City = city;
        this->State = state;
        this->ZipCode = zip;
    }

    void ListAddress(){
        cout << this->Addressline << ", "<<this->City << ", "<< this->State
<<". "<< this->ZipCode<< "\n";
    }

};