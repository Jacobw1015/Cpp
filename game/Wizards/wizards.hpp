#pragma once 
#include "../Elements/elements.hpp"
#include "../Stats/Stats.hpp"
#include <string>
class Wizards: public Stats
{
private:
    std::string Name; 
    Stats WizStats;

public:
    
    
    Wizards(std::string name ="Wizard");
    ~Wizards();

    eletype setEle(eletype ele){return WizStats.Element=ele;}
    eletype getEle(){ return WizStats.Element}
    std::string getName(){ return Name;}
    stattype getAttack(){ return WizStats.Attack; }
    stattype getDefense(){ return WizStats.Defense; }
    stattype getSpeed(){ return WizStats.Speed; }
};

Wizards::Wizards(std::string name):Name(name)
{
}

Wizards::~Wizards()
{
}
