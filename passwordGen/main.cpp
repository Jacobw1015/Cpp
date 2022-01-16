#include <iostream>
#include <vector>
#include <stdlib.h>
#include <regex>

using std::cout, std::cin, std::endl,std::string;

int main(){
    int passlength;
    string password;
    srand(time(NULL));

    passlength = rand() % 10+3;
    char letters; 

    for(int i = 0; i< passlength;i++){
        password += letters;
        letters = 'a'+ rand()%26;
    }
    cout<< password;
};