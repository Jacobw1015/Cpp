#pragma once
#include "../DataTypes/types.hpp"
#include "../Stats/Stats.hpp"
#include "../HealthMana/HealthandMana.hpp"
#include "../Elements/elements.hpp"
#include "../Spells/spells.hpp"
#include "../Movement/movement.hpp"
#include "../Items/Item.hpp"
#include <vector>
#include <string>
#include <iostream>

class Wizard: public Move{
    private: 
    std::string Name;
    Elements Element;
    CoreStats Stats;
    ElementStats EleStats;
    HealthBlock Health;
    ManaBlock Mana;
    leveltype Level =1;
    Spells Spell;
  

    public:
    Wizard(std::string name,Elements element):Move(){
      Name = name;
      Element = element;
    };
  
  // Gets Stats for Wizard
    std::string getElementName(){ 
      switch (Element)
      {
      case Elements::Fire :
        return "Fire";
        break;
      case Elements::Air :
        return "Air";
        break;
      case Elements::Water :
        return "Water";
        break;
      
      default: return "Earth";
        break;
      }
     
      }
      Elements getElementType(){ return Element;}



    stattype getAttack(){ return Stats.Attack;}
    stattype getDefense(){ return Stats.Defense;}
    stattype getSpeed(){ return Stats.Speed;}
    healthtype currentHP(){return Health.getCurrentHealth();}
    healthtype getMaxHP(){ return Health.getMaxHealth();}
    manatype currentMP(){ return Mana.getCurrentMana();} 
    manatype getMaxMP(){ return Mana.getMaxMana();}
    leveltype getLevel() { return Level;}


    // Elemental Stats for Wizard
    stattype getFireStat(){return EleStats.Fire;}
    stattype getAirStat(){return EleStats.Air;}
    stattype getEarthStat(){return EleStats.Earth;}
    stattype getWaterStat(){return EleStats.Water;}

    // Spells
    std::vector<Spells> SpellList;
    manatype getManaUse(){ return Spell.getManaUse();};
    Elements getSpellElement(){ return Spell.getElements();}
    std::string getSpellName(){ return Spell.getSpellName();};
    SPELLTYPE getSpellType(){ return Spell.getSpellType();};

   
      bool setSpellType(std::string &type, SPELLTYPE &spelltype){
    if(type == "Damage" || type=="damage"){
        spelltype= SPELLTYPE::DMG;
        return true;
    }else if(type == "Heal" || type=="heal"){
        spelltype= SPELLTYPE::HEAL;
        return true;
    }else if(type == "Buff" || type=="buff"){
        spelltype= SPELLTYPE::BUFF;
        return true;
    }else if(type == "Effect" || type=="effect"){
        spelltype= SPELLTYPE::EFF;
        return true;
    }else{
      return false;
    }
};

    void createSpell(){
       std::string spellInput,spellName;
       SPELLTYPE spelltype;
       manatype amount;

       std::cout <<"Create Spell: ";
            std::getline(std::cin,spellName);
            
        std::cout << "Spell type: \n"
          << "-Damage\n"
          << "-Heal\n"
          << "-Effect\n"
          << "-Buff\n";
            std::cin >> spellInput;
            setSpellType(spellInput,spelltype);
        std::cout << "Mana cost: \n";
         std::cin >> amount;
      
Spells Spell(spellName,this->getElementType(),amount,spelltype);
        SpellList.emplace_back(Spell);
       
      }
    void listSpells(){
      std::cout << "-List of Spells:\n";
      for(auto i : SpellList){
        std::cout <<"- " <<i.getSpellName() <<"\n";
      }
    }

    bool castSpell(std::string spell){
      std::string input;
      for(auto i: SpellList){
        if( i.getSpellName()==spell){

           if(currentMP() < i.getManaUse()){
             std::cout << "Not Enough Mana!\n" 
           << "Restore mana?\n";
                 std::cin >> input;
                 if(input == "yes"){
                     this->increaseMP(this->getMaxMP());
                 }
             return false;
           }
           std::cout <<"Casting: "<< i.getSpellName()<<"\n";
            decreaseMP(i.getManaUse());
            std::cout << "-Mana: " << this->currentMP() << "/" << this->getMaxMP()<<"\n";
          return true;
        }
      }
      return false;
    }

    // Movement
    void getLocation(){ return this->getCurrentLocation();}
    void move(char c){ this->movePlayer(c);}
   

    
    std::string getName(){ return Name;}
    // Mana functions
    void increaseMP(manatype amount){ Mana.restoreMana(amount); }
    void decreaseMP(manatype amount){ Mana.useMana(amount);}
    void setMaxMP(manatype amount) { Mana.increaseMaxMana(amount);}
    
    // Health Functions
    void increaseHP(healthtype amount){ Health.heal(amount); }
    void decreaseHP(healthtype amount){ Health.takeDamage(amount);}
    void setMaxHP(healthtype amount) { Health.increaseMaxHealth(amount);}

    
    void ElementBoost(){ EleStats.elementboost(Element);}

    void Elementincrease(stattype value){ EleStats+=value;}
    void StatIncrease(stattype value){ Stats += value; }
    void Info(){
    std::cout 
      << "Hello, " << this->getElementName() << " Wizard: " <<this->getName() <<"\n"
      <<"Stats: \n"
      <<"-Level: " << this->getLevel() <<"\n"
      <<"-Health: "<< this->currentHP() << "/" << this->getMaxHP()<<"\n"
      <<"-Mana: "<< this->currentMP() << "/" << this->getMaxMP()<<"\n"
      <<"-Attack: " <<this->getAttack()<<"\n"
      <<"-Defense: "<< this->getDefense()<< "\n"
      <<"-Speed: "<< this->getSpeed()<< "\n"
      << "Element Stats: \n"
      <<"-Fire: "<< this->getFireStat()<< "\n"
      <<"-Air: "<< this->getAirStat()<< "\n"
      <<"-Water: "<< this->getWaterStat()<< "\n"
      <<"-Earth: "<< this->getEarthStat()<< "\n";

    }

    // Weapon functions
    std::vector<Weapon> WeaponList;
    std::vector<Robes> RobesList;

    void addToItemList(Weapon& wpn){

        WeaponList.emplace_back(wpn);
    }
    void addToItemList(Robes& robe){

        RobesList.emplace_back(robe);
    }

     void listWeapons(){
      std::cout << "-List of Weapons:\n";
      for(auto i : WeaponList){
        std::cout <<"- " <<i.getItemName() <<"\n";
      }
    }

     void listRobes(){
      std::cout << "-List of Robes:\n";
      for(auto i : RobesList){
        std::cout <<"- " <<i.getItemName() <<"\n";
      }
    }

  

  void WeaponsInfo(){
    for(auto i : WeaponList){
      std::cout << "\n";
      i.getWeaponInfo();
    }
  }

    void equipWeapon(Weapon& wpn){
      // Want to gain attack boost
      stattype weaponAttackStat = wpn.getBoostedStat();
        Stats.setAttack(weaponAttackStat);
      EleStats.setElementBoostFromItem(wpn.getElementType(),wpn);
    }
    void equipRobe(Robes& robe){
      Stats.setDefense(robe.getBoostDefense());
      Stats.setSpeed(robe.getBoostSpeed());
      EleStats.setElementBoostFromItem(robe.getElementType(),robe);
      
    }

};


class Player: public Wizard{
  private:

  public:
  Player(std::string name, Elements ele) : Wizard(name,ele){};
};