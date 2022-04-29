#pragma once
#include "../DataTypes/types.hpp"
#include "../Elements/elements.hpp"
#include "../HealthMana/HealthandMana.hpp"

#include <string>


enum class SPELLTYPE { DMG, BURN, STUN , HEAL, BUFF };

class Spell
{
private:
  manatype ManaUse;
  Elements Element;
  std::string SpellName;
  SPELLTYPE SpellType;

public:
  Spell();
  Spell(std::string name, Elements element, manatype amtOfMana, SPELLTYPE modi);

  manatype getManaUse() { return ManaUse; };
  Elements getElements() { return Element; }
  std::string getSpellName() { return SpellName; };
  SPELLTYPE getSpellType() { return SpellType; };
};
Spell::Spell() {}
Spell::Spell(std::string name, Elements element, manatype amtOfMana, SPELLTYPE modi) : SpellName(name), Element(element), ManaUse(amtOfMana), SpellType(modi) {}
