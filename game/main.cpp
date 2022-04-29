#include <iostream>
#include <string>
#include "Player/Player.hpp"


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
    std::string a;
    Elements element;
   

   /* std::cout << "Please Enter a name: ";
    std::getline(std::cin, input);
    std::cout << "Please Select an Element: \n"
              << "-Fire\n"
              << "-Water\n"
              << "-Air\n"
     std::cin >> choice;*/
    
   // selectElement(choice, element);

    Player p1 = Player("Jacob",Elements::Earth);
    Wizard en1 = Wizard("Enemy",Elements::Air);
    Wizard en2 = Wizard("Enemy 2",Elements::Fire);

    Robes en2Robe = Robes("Magma Robe",ITEMTYPE::ROBE,100,Elements::Fire,5,3);
    en2.addToItemList(en2Robe);
    en2.equipRobe(en2Robe);

    p1.createSpell(new Spell("Earth Wave",Elements::Earth,30,SPELLTYPE::DMG));
    en2.gainExp(5000);

    p1.castSpell(en1,"Earth Wave");
    std::cout<<"\n";
    p1.castSpell(en2,"Earth Wave");
    std::cout <<"\n";
    en1.Info();    
    std::cout <<"\n";
    en2.Info();    

    return 0;
}