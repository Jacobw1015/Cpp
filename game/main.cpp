#include <iostream>
#include <string>
#include "Wizards/wizards.hpp"
#include "DataTypes/types.hpp"
#include "Elements/elements.hpp"
#include "Items/Item.hpp"
#include <conio.h>


    void selectElement(std::string &choice, Elements &element){
        
    if(choice =="Fire"||choice == "fire")
    {  element = Elements::Fire;

    }
     else if(choice =="Water"||choice == "water"){
        element = Elements::Water;

     }  
    else if(choice =="Earth"||choice == "earth"){
        element = Elements::Earth;

     } 
     else if(choice =="Air"||choice == "air"){
         element = Elements::Air;

     } 
     else{
         std::cout <<"Invalid Element";
     }
}




int main()
{
    std::string input,choice;
    char a;
    Elements element;
   

   /* std::cout << "Please Enter a name: ";
    std::getline(std::cin, input);
    std::cout << "Please Select an Element: \n"
              << "-Fire\n"
              << "-Water\n"
              << "-Air\n"
     std::cin >> choice;*/
    
   // selectElement(choice, element);

    Player wiz = Player("Jacob",Elements::Fire);
   wiz.Info();
  Potion healthPotion= Potion("Mass Heal",ITEMTYPE::POTION,100,POTIONTYPE::MANA,100);
    std::cout << "\n" << healthPotion.getItemName() <<"\n"
    << "Type of Item: " << healthPotion.getType() << "\n"
    << "Type of Potion: " << healthPotion.getPotionInfo() <<"\n";
    //Weapons
Weapon wand = Weapon("Storm-Bringer",ITEMTYPE::WEAPON,100,WeaponType::WAND,Elements::Air,10,5,3);
Weapon staff =  Weapon("Magmarok",ITEMTYPE::WEAPON,150,WeaponType::STAFF,wiz.getElementType(),15,8,5); 
Weapon waterStaff = Weapon("Posiden's Rage", ITEMTYPE::WEAPON,175, WeaponType::STAFF,Elements::Water,25,10,15 );
Weapon EarthWand = Weapon("Terra Hammer", ITEMTYPE::WEAPON,180, WeaponType::WAND,Elements::Earth,15,6,10 );
   
   wiz.addToItemList(wand);
   wiz.addToItemList(staff);
   wiz.addToItemList(waterStaff);
   wiz.addToItemList(EarthWand);
   
    wiz.listWeapons();
   wiz.WeaponsInfo();
    wiz.equipWeapon(EarthWand);
std::cout<<"\n";
//Robe
Robes test = Robes("Test",ITEMTYPE::ROBE,50,wiz.getElementType(),10,0,15);
Robes test2 = Robes("Test2",ITEMTYPE::ROBE,90,Elements::Water,10,15);

wiz.addToItemList(test);
wiz.addToItemList(test2);
wiz.listRobes();
wiz.equipRobe(test2);
wiz.Info();
    

    return 0;
}