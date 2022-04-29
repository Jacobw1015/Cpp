#pragma once
#include "../DataTypes/types.hpp"
#include "../Stats/Stats.hpp"
#include "../HealthMana/HealthandMana.hpp"
#include "../Elements/elements.hpp"
#include "../Spells/spells.hpp"
#include "../Movement/movement.hpp"
#include "../Levelup/Levelup.hpp"
#include "../Items/Item.hpp"
#include "../Currency/Currency.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

class Wizard: public Move{
    private: 
    std::string Name;
    Elements Element;
    CoreStats Stats;
    ElementStats EleStats;
    HealthBlock Health;
    ManaBlock Mana;
    Levels Level;
    Spell spell;
    std::unique_ptr<Currency> Mptr;
    public:
    Wizard();
    Wizard(std::string name,Elements element);
  
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
    leveltype getLevel() { return Level.getLevel();}
    void gainExp(exptype amt) { 
      Level.gainExp(amt);
      while(this->Level.getCurrentExp() >= this->Level.getExpToLevelUp()&& this->Level.getLevel()<50){
          //if(this->Level.getCurrentExp() < this->Level.getCurrentExp()){break;}
          this->StatIncrease(1);
          this->EleStatBoostOnLvlUp(this->getElementType());
          this->Level.LevelUp();
          this->Health.increaseMaxHealth(10);
          this->Health.heal(this->Health.getMaxHealth());
          this->Mana.increaseMaxMana(10);
          this->Mana.restoreMana(this->Mana.getMaxMana());
        
      }
    }

    // Elemental Stats for Wizard
    stattype getFireStat(){return EleStats.Fire;}
    stattype getAirStat(){return EleStats.Air;}
    stattype getEarthStat(){return EleStats.Earth;}
    stattype getWaterStat(){return EleStats.Water;}

    // Spells
    std::vector<Spell*> SpellList;
    manatype getManaUse(){ return spell.getManaUse();};
    Elements getSpellElement(){ return spell.getElements();}
    std::string getSpellName(){ return spell.getSpellName();};
    SPELLTYPE getSpellType(){ return spell.getSpellType();};

    void castSpell(Wizard &target, std::string spName)
    {
      int timer = 5;
      for (auto i : SpellList)
      {
        if (i->getSpellName() == spName)
        {
          switch (i->getSpellType())
          {
          case SPELLTYPE::BURN:

            while (timer != 0)
            {
              target.decreaseHP(2);
              timer--;
            }

            break;
          case SPELLTYPE::DMG:
           { healthtype dmgFactor = (i->getManaUse()-target.getDefense());
            if(dmgFactor<1) dmgFactor =1;
            target.decreaseHP(dmgFactor);}
            break;
          case SPELLTYPE::HEAL:
            {healthtype healAmt = (healthtype)i->getManaUse();
            target.increaseHP(healAmt);}
            break;
          case SPELLTYPE::STUN:
            {target.DecreaseSpeed(2);}
            break;
          }
          this->decreaseMP(i->getManaUse());
        }
        else
          break;
      }
    }

    void createSpell(Spell* spell){
      
        SpellList.emplace_back(spell);
      }
    void listSpells(){
      std::cout << "-List of Spells:\n";
      for(auto i : SpellList){
        std::cout <<"- " <<i->getSpellName() <<"\n";
      }
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

    // Stat Functions    
    
    // For multiple stats
    void ElementBoost(){ EleStats.elementboost(Element);}
    void Elementincrease(stattype value){ EleStats+=value;}
    void StatIncrease(stattype value){ Stats += value; }
    void StatDecrease(stattype value) { Stats -= value;}

    // For single Stat
    /* Increase */
    void IncreaseAttack(stattype val) { Stats.increaseAttack(val);}
    void IncreaseDefense(stattype val) { Stats.increaseDefense(val);}
    void IncreaseSpeed(stattype val) { Stats.increaseSpeed(val);}
    /* Decrease */
    void DecreaseAttack(stattype val) { Stats.decreaseAttack(val);}
    void DecreaseDefense(stattype val){ Stats.decreaseDefense(val);}
    void DecreaseSpeed(stattype val) {  Stats.decreaseSpeed(val);}
     
    void EleStatBoostOnLvlUp(Elements element)
    {
       // When Wizard Levels up, Boosts elements based on Wizard's element
      switch (element)
      {
      case Elements::Fire:
        this->EleStats.Fire += 2;
        this->EleStats.Air += 1;
        this->EleStats.Water += 1;
        this->EleStats.Earth += 1;
        break;
      case Elements::Air:
        this->EleStats.Fire += 1;
        this->EleStats.Air += 2;
        this->EleStats.Water += 1;
        this->EleStats.Earth += 1;
        break;
      case Elements::Water:
        this->EleStats.Fire += 1;
        this->EleStats.Air += 1;
        this->EleStats.Water += 2;
        this->EleStats.Earth += 1;
        break;
      default:
        this->EleStats.Fire += 1;
        this->EleStats.Air += 1;
        this->EleStats.Water += 1;
        this->EleStats.Earth += 2;
        break;
      }
    }

    void Info(){
    std::cout 
      << "Hello, " << this->getElementName() << " Wizard: " <<this->getName() <<"\n"
      <<"Stats: \n"
      <<"-Level: " << this->getLevel() <<"\n"
      << "-Exp: " << this->Level.getCurrentExp() << "/" << this->Level.getExpToLevelUp()<<"\n"
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
    //Money Functions
    currencytype getCurrentMoney(){ return this->Mptr->getMoney();}
    currencytype gainMoney(currencytype amt){ return this->Mptr->gainMoney(amt);}
    currencytype spendMoney(currencytype amt) { return this->Mptr->spendMoney(amt);}

    // Item functions
    std::vector<Weapon> WeaponList;
    std::vector<Robes> RobesList;
    std::vector<Ring> RingList;
    std::vector<Potion> Potions;

    void addToItemList(Weapon& wpn){

        WeaponList.emplace_back(wpn);
    }
    void addToItemList(Robes& robe){

        RobesList.emplace_back(robe);
    }
    void addToItemList(Ring& ring){

        RingList.emplace_back(ring);
    }
    void addToItemList(Potion& potion){

        Potions.emplace_back(potion);
    }

    void ListAllItems(){
      this->listWeapons();
      std::cout <<"\n";
      this->listRobes();
      std::cout <<"\n";
      this->listRings();
      std::cout <<"\n";
      this->listPotions();
      std::cout <<"\n";
    }

    void listPotions(){
      std::cout <<"-List of Potions:\n";
      for(auto i : Potions){
        std::cout << "- "<< i.getPotionInfo() <<"\n";
      }
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
     void listRings(){
      std::cout << "-List of Rings:\n";
      for(auto i : RingList){
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
      if(!wpn.getEquipStatus()){
      stattype weaponAttackStat = wpn.getBoostAttack();
        Stats.increaseAttack(weaponAttackStat);
      EleStats.setElementBoostFromItem(wpn.getElementType(),wpn);
      wpn.setEquip(true);
      }else{
       std::cout << "A "+ wpn.getItemType() +" is already equiped!\n";
       }
    }
    void equipRobe(Robes& robe){
     if(!robe.getEquipStatus()){
      Stats.increaseDefense(robe.getBoostDefense());
      Stats.increaseSpeed(robe.getBoostSpeed());
      EleStats.setElementBoostFromItem(robe.getElementType(),robe);
      robe.setEquip(true);
      }else{
       std::cout << "A "+ robe.getItemType() +" is already equiped!\n";
       }
    }
    void equipRing(Ring& ring){
      
     if(!ring.getEquipStatus()){
      Stats.increaseAttack(ring.getBootAttack());
      Stats.increaseDefense(ring.getBoostDefense());
      Stats.increaseSpeed(ring.getBoostSpeed());
      EleStats.setElementBoostFromItem(ring.getElementType(),ring);
      ring.setEquip(true);
     
      }else{
       std::cout << "A "+ ring.getItemType() +" is already equiped!\n";
       }
    }

};
Wizard::Wizard(){};

Wizard::Wizard(std::string name,Elements element):Move(){
      Name = name;
      Element = element;
      this->ElementBoost();
    };