#include <iostream>
#include "Address.hpp"

class Building{
    private:
    Address* BuildingAddress;
    std::string BuildingName;
    public: 
    Building(std::string name, Address* add){ BuildingName=name; BuildingAddress=add; }
    void getAddress(){
        BuildingAddress->ListAddress();
    }
   std::string getName(){
       return BuildingName;
    }
};