#pragma once
#include "../DataTypes/types.hpp"
#include <iostream>
class HealthBlock
{
private:
    healthtype Health =100;
    healthtype MaxHealth =100;
    

public:
    // Health functions
    healthtype getCurrentHealth(){
        return Health;
    }
    healthtype getMaxHealth(){
        return MaxHealth;
    }

    void increaseMaxHealth(healthtype amount){
        MaxHealth += amount;
    }

    void takeDamage(healthtype damage){
        Health -= damage;
        if(Health <=0){
            std::cout <<"Game Over!";
        }
    }

    void heal(healthtype amount){
        Health += amount;
        if(Health > MaxHealth){
            Health = MaxHealth;
        }
    }

};

class ManaBlock{
    private:
    manatype Mana =100,MaxMana = 100;

    public:

    
    // Mana functions
    manatype getCurrentMana(){
        return Mana;
    }
    manatype getMaxMana(){
        return MaxMana;
    }
    
    void increaseMaxMana(manatype amount){
        MaxMana += amount;
    }

    void useMana(manatype amount){
        Mana -= amount;
        if(Mana < 0){
            Mana = 0;
        }
    }
    void restoreMana(manatype amount){
        Mana += amount; 
        if(Mana > MaxMana){
            Mana = MaxMana;
        }
    }

};

