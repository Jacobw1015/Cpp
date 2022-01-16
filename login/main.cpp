#include <iostream>
#include <cmath>
#include "main_functions.hpp"
#include <vector>
#include <string>
using std::cout;
using std::cin;
using std::string;
using std::endl;


User create_user(){
    string name,userName, pass;
    cout << "Creating a new user\n"<<"Pleaser enter a name: "<<endl;
     cin >> name;
    cout << "Please enter a username: " << endl;
     cin >> userName;
    cout << "Now enter a password: \n";
     cin >> pass;
    cout << "Account created!\n";
    User new_user(name,userName,pass);
    return new_user;
}


int main(){
   
create_user().auth();

    return 0;
}