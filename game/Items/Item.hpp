#pragma once
#include "../DataTypes/types.hpp"
#include "../HealthMana/HealthandMana.hpp"
#include "../Stats/Stats.hpp"
#include "../Elements/elements.hpp"
#include <sstream>
#include <string>

using std::string, std::cout;

enum struct ITEMTYPE { POTION, WEAPON, ROBE, RING,MISC};

class Item{
    private:
    std::string ItemName;
    ITEMTYPE Itemtype;
    currencytype Value;

    public:
    Item() = delete;
    Item(std::string name, ITEMTYPE item, currencytype val):
    ItemName(name), Itemtype(item),Value(val) { };

    // Item Getters
    std::string getItemName(){ return ItemName;}
  
    currencytype getValue() { return Value;}
    
    std::string getItemType() {
          switch(Itemtype){
            case ITEMTYPE::POTION:
                return "Potion"; break;
            case ITEMTYPE::WEAPON : 
                return "Weapon"; break;
            case ITEMTYPE::ROBE : 
              return "Robe"; break;
            default: return "Ring"; break;

        }
    };

};
enum struct POTIONTYPE {HEALTH, MANA };
class Potion: public Item{
   private: 
   healthtype AmountOfHealth;
   manatype AmountOfMana;
   POTIONTYPE TypeOfPotion;
    
    public: 
    Potion() = delete;
    Potion(std::string name, ITEMTYPE itemtype, currencytype val, POTIONTYPE potiontype, int amount): Item(name,itemtype,val){
        switch (potiontype)
        {
        case POTIONTYPE::HEALTH:
            TypeOfPotion = POTIONTYPE::HEALTH;
            amount = (healthtype)amount;
            AmountOfHealth = amount;
            break;
        case POTIONTYPE::MANA:
            TypeOfPotion = POTIONTYPE::MANA;
            amount = (manatype)amount;
            AmountOfMana = amount;
            break;
        default:
            break;
        }
    };
    // Getters for Potion
     healthtype getAmountOfHealth() { return AmountOfHealth;}
     manatype getAmountOfMana() { return AmountOfMana;}

     std::string getPotionInfo(){
         std::stringstream ss;
         std::string s;
        if(TypeOfPotion == POTIONTYPE::HEALTH){
            ss << "Health Potion\n  Restores: "<< this->getAmountOfHealth()<< " HP\n";
            return s=ss.str();
        }
        if(TypeOfPotion == POTIONTYPE::MANA){
            ss << "Mana Potion\n  Restores: "<< this->getAmountOfMana()<< " MP\n";
            return s=ss.str();
        }
        return "Not a Potion";
     }
    

};
enum struct WeaponType { WAND, STAFF};
class Weapon : public Item
{
private:
    bool isEquiped =false;
    WeaponType TypeOfWeapon;
    stattype BoostAttack;
    stattype ElementToBoost;
    Elements Element;
    healthtype Damage;

public:
    Weapon() = delete;
    Weapon(std::string name, ITEMTYPE itemtype, currencytype val, WeaponType weapontype,
           Elements element, healthtype damage, stattype att, stattype elestat) : Item(name, itemtype, val)
    {
        TypeOfWeapon = weapontype;
        BoostAttack = att;
        Element = element;
        Damage = damage;
        ElementToBoost = elestat;
    }
    bool getEquipStatus() { return isEquiped; }
    void setEquip(bool value) { isEquiped = value; }

    std::string getWeaponType()
    {
        if (TypeOfWeapon == WeaponType::WAND)
        {
            return "Wand";
        }
        if (TypeOfWeapon == WeaponType::STAFF)
        {
            return "Staff";
        }
        return "Not a weapon";
    }
    stattype getBoostAttack() { return BoostAttack; }
    stattype getBoostedElement() { return ElementToBoost; }

    healthtype getDamage() { return Damage; }

    Elements getElementType()
    {
        switch (Element)
        {
        case Elements::Air:

            return Elements::Air;
            break;
        case Elements::Fire:

            return Elements::Fire;
            break;
        case Elements::Water:

            return Elements::Water;
            break;
        default:

            return Elements::Earth;
            break;
        }
    }

    std::string getElementName()
    {

        switch (Element)
        {
        case Elements::Air:

            return "Air";
            break;
        case Elements::Fire:

            return "Fire";
            break;
        case Elements::Water:

            return "Water";
            break;
        default:

            return "Earth";
            break;
        }
    }

    void getWeaponInfo()
    {

        std::cout << "Name of Weapon: " << this->getItemName() << "\n"
                  << "-Type of Weapon: " << this->getWeaponType() << "\n"
                  << "Attack Stat: +" << this->getBoostAttack() << "\n"
                  << "Weapon Damage: " << this->getDamage() << "\n"
                  << "Element of Weapon: " << this->getElementName() << "\n"
                  << "Element Stat: +" << this->getBoostedElement() << "\n"
                  << "Value: " << this->getValue() << " gold\n";
    }
};

class Robes: public Item{
    private: 
    bool isEquiped = false;
     Elements Element;
     stattype BoostDefense, BoostSpeed;
     healthtype BonusHealth;
     manatype BonusMana;
     stattype ElementToBoost;

     public: 
    // Getters
    Robes()=delete;
    Robes(std::string name, ITEMTYPE itemtype, currencytype val, 
     Elements element, stattype elestat, stattype def=0, stattype spd=0) : Item(name,itemtype, val){
        Element = element;
        ElementToBoost = elestat;
        BoostSpeed = spd;
        BoostDefense = def;
     }
    
    bool getEquipStatus() { return isEquiped; }
    void setEquip(bool value) { isEquiped = value; }
    stattype getBoostedElement(){return ElementToBoost;}
    stattype getBoostDefense(){return BoostDefense;}
    stattype getBoostSpeed(){return BoostSpeed;}
     
     std::string getElementName(){
         
         switch(Element){
             case Elements::Air : 
              
               return "Air"; break;
             case Elements::Fire : 
              
               return "Fire"; break;
             case Elements::Water : 
              
               return "Water"; break;
             default : 
              
             return "Earth"; break;
         }
     }
     Elements getElementType(){
        switch (Element)
        {
        case Elements::Air:

            return Elements::Air;
            break;
        case Elements::Fire:

            return Elements::Fire;
            break;
        case Elements::Water:

            return Elements::Water;
            break;
        default:

            return Elements::Earth;
            break;
        }
    }
    
    void getRobesInfo(){
        std::cout << "Name of Robe: " << this->getItemName() <<"\n"
        << "Element of Robe: " << this->getElementName() << "\n"
        << "Element boost from Robe: " << this->getBoostedElement() << "\n";
    }

};

class Ring : public Robes
{
private:
    Elements Element;
    stattype BoostDefense, BoostSpeed, BoostAttack;
    healthtype BonusHealth;
    manatype BonusMana;
    stattype ElementToBoost;

public:
    Ring() = delete;
    Ring(string name, ITEMTYPE itemtype, currencytype value,
         Elements element, stattype att, stattype def, stattype spd,
         healthtype heal, manatype mana, stattype elestat) : Robes(name, itemtype, value, element, elestat, def, spd)
    {
        BoostAttack = att;
        BonusHealth = heal;
        BonusMana = mana;
    }
    stattype getBootAttack() { return BoostAttack; }
    void getRingInfo()
    {
        std::cout << "Name of Ring: " << this->getItemName() << "\n"
                  << "Element of Ring: " << this->getElementName() << "\n"
                  << "Element boost from Ring: " << this->getBoostedElement() << "\n";
    }
};