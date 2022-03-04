#pragma once 
#include "../DataTypes/types.hpp"
#include "../Elements/elements.hpp"
#include "../Items/Item.hpp"

struct  CoreStats
{
    stattype Attack =1;
    stattype Speed  =1;
    stattype Defense=1;


    // Setters
    void setAttack(stattype val){ Attack += val;}
    void setSpeed(stattype val){ Speed += val;}
    void setDefense(stattype val){ Defense += val;}



    CoreStats();
    CoreStats(stattype att,stattype speed,stattype defense): Attack(att), Speed(speed),
    Defense(defense)
    {

    }

    CoreStats& operator+=(const stattype& rhs){
        this->Attack += rhs;
        this->Defense += rhs;
        this->Speed += rhs;
        return *this;
    }
};
CoreStats::CoreStats(){};

struct ElementStats
{   
    
    stattype Fire =1;
    stattype Water =1;
    stattype Air    =1;
    stattype Earth  =1;

    ElementStats();

    // Setters
void setElementBoostFromItem(Elements element,Weapon wpn){
    stattype amt = wpn.getBoostedElement();
    switch(element){
        case Elements::Fire:
          Fire+=amt; break;
        case Elements::Water:
          Water+=amt; break;
        case Elements::Air:
          Air+=amt; break;
        
        default: Earth +=amt; break;

    }

}
void setElementBoostFromItem(Elements element,Robes wpn){
    stattype amt = wpn.getBoostedElement();
    switch(element){
        case Elements::Fire:
          Fire+=amt; break;
        case Elements::Water:
          Water+=amt; break;
        case Elements::Air:
          Air+=amt; break;
        
        default: Earth +=amt; break;

    }

}


    void elementboost(Elements ChosenElement){
        if(ChosenElement == Elements::Fire){ Fire+=5;}
        if(ChosenElement == Elements::Water ){ Water+=5;}
        if(ChosenElement == Elements::Air ){ Air+=5;}
        if(ChosenElement == Elements::Earth ){ Earth+=5;}

    }
  
    ElementStats& operator+=(const stattype& rhs){
        this->Fire += rhs;
        this->Air += rhs;
        this->Water += rhs;
        this->Earth += rhs;
        return *this;
    }; 
    
    
};
ElementStats::ElementStats(){}