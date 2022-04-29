#pragma once
#include "../Wizards/wizards.hpp"
#include "../DataTypes/types.hpp"
#include "../Elements/elements.hpp"
#include "../Items/Item.hpp"
#include "../Location/Location.hpp"
#include <conio.h>


class Player: public Wizard,Location{
  private:
  

  public:
  Player(std::string name, Elements ele) : Wizard(name,ele),Location(){};


};