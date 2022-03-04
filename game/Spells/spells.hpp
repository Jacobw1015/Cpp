#pragma once
#include "../DataTypes/types.hpp"
#include "../Elements/elements.hpp"
#include "../HealthMana/HealthandMana.hpp"
#include <string>

enum class SPELLTYPE { DMG, EFF, HEAL, FORM, BUFF };

class Spells{
    private:
     manatype ManaUse;
     Elements Element;
     std::string SpellName;
     SPELLTYPE SpellType;
      
    public:
      Spells();
      Spells(std::string name, Elements element, manatype amtOfMana, SPELLTYPE modi);
      
     manatype getManaUse(){ return ManaUse ;};
     Elements getElements(){ return Element;}
     std::string getSpellName(){ return SpellName;};
     SPELLTYPE getSpellType(){ return SpellType;};


};
Spells::Spells(){}
Spells::Spells(std::string name, Elements element, manatype amtOfMana, SPELLTYPE modi):
SpellName(name), Element(element), ManaUse(amtOfMana), SpellType(modi){}
