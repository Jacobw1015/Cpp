#pragma once
#include "move.hpp"
#include <iostream>
#include <stdlib.h>

class Identity{
    
    public:
    std::string Name;
     int Age;
    Move walk;
    Identity(std::string name,int age){
        this->Name =name;
        this->Age = age;
       
    };
    

};