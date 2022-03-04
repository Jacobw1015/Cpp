#include <iostream>
#include <vector>
#include <stdlib.h>
#include <regex>

using std::cout, std::cin, std::endl,std::string;

int main(){
    
    string password;
    srand(time(NULL));

    char letters; 

    for(int i = 0; i< 15;i++){
       letters = 'a'+ rand()%28;
        password += letters;
        
    }
    cout<< password;
};