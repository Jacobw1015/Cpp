#include <iostream>
#include "Wizards/wizards.hpp"

int main(){
    Wizards wiz1= Wizards("Jacob");
    
    std::cout << "Welcome: "
    << wiz1.getName() << "\n"
    << "Stats: \n"
    << "-Attack: " <<wiz1.getAttack() << "\n"
    << "-Defense: " <<wiz1.getDefense() << "\n"
    << "-Speed: " <<wiz1.getSpeed() << "\n";
      

    return 0;
}