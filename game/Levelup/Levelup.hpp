#include <iostream>
#include "../DataTypes/types.hpp"
#include "../Wizards/wizards.hpp"
using std::string, std::cout;

class Levels{
private:
   
    
    exptype ExpToLevelUp = 100;
    exptype CurrentExp =0;
    leveltype Level = 1;
    leveltype LevelCap = 50;

public:
    // Getters
    exptype getExpToLevelUp() { return ExpToLevelUp; }
    void setNextExpToLVL() { ExpToLevelUp +=100;}
    exptype getCurrentExp() { return CurrentExp; }
    leveltype getLevel() { return Level; }
    leveltype getLevelCap() { return LevelCap; }
    void LevelUp() { 
        
        Level++; 
        this->setNextExpToLVL();
        if(Level == LevelCap){
            this->CurrentExp = this->ExpToLevelUp;
        }
    
    }

    // Exp functions
    void gainExp(exptype amt){ 
        CurrentExp += amt;
    
    }
 

};