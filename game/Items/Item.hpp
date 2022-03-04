#pragma once
#include "../DataTypes/types.hpp"
#include "../HealthMana/HealthandMana.hpp"
#include "../Stats/Stats.hpp"
#include "../Elements/elements.hpp"
#include <sstream>
#include <string>

enum struct ITEMTYPE { POTION, WEAPON, ROBE, MISC};

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
            default: return "Misc"; break;

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
            ss << "Health Potion\nRestores: "<< this->getAmountOfHealth()<< " HP\n";
            return s=ss.str();
        }
        if(TypeOfPotion == POTIONTYPE::MANA){
            ss << "Mana Potion\nRestores: "<< this->getAmountOfMana()<< " MP\n";
            return s=ss.str();
        }
        return "Not a Potion";
     }
    
    std::string getType() { return this->getItemType();}

};
enum struct WeaponType { WAND, STAFF};
class Weapon: public Item{
    private:
    WeaponType TypeOfWeapon;
    stattype statToBoost; 
    stattype ElementToBoost;
    Elements Element;
    healthtype Damage;
    

    public:
    Weapon()=delete;
     Weapon(std::string name, ITEMTYPE itemtype, currencytype val,WeaponType weapontype, 
     Elements element, healthtype damage, stattype att, stattype elestat) : Item(name,itemtype, val) {
         TypeOfWeapon = weapontype;
         statToBoost = att;
         Element= element;
         Damage = damage;
         ElementToBoost = elestat;
     }
     std::string getWeaponType(){
         if(TypeOfWeapon == WeaponType::WAND){
             return "Wand";
         }
         if(TypeOfWeapon == WeaponType::STAFF){
             return "Staff";
         }
         return "Not a weapon";
     }
     stattype getBoostedStat(){ return statToBoost;}
     stattype getBoostedElement(){return ElementToBoost;}

    healthtype getDamage(){ return Damage;}

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

     void getWeaponInfo(){
         //std::stringstream ss;     std::string s;
     
         std::cout <<"Name of Weapon: " << this->getItemName() <<"\n"
           << "-Type of Weapon: " << this->getWeaponType() << "\n"
           << "Attack Stat: +" << this->getBoostedStat() <<"\n" 
           <<"Weapon Damage: " << this->getDamage() << "\n"
           << "Element of Weapon: "<< this->getElementName()<< "\n"
           << "Element Stat: +" << this->getBoostedElement() << "\n"
           << "Value: "<< this->getValue() <<" gold\n"; 
     }
     
};

class Robes: public Item{
    private: 
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
         Element= element;
ElementToBoost = elestat;
        BoostSpeed = spd;
        BoostDefense=def;
     }
    
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
        << "Element boost from Robe: " << this->getBoostedElement() << "\n"
        << 
    }

};