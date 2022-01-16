#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class User{

    private:
      string _name;
      string _username;
      string _password;
    public:
      string get_username(){
          return _username;
      }
      string get_name(){
          return _name;
      }
      /*void set_username(string userName){ username = userName;}void set_password(string pass){password = pass;}*/
      string get_password(){
        return _password;
      }
      void auth(){
      
        string input1;
        string input2;
        cout <<"Please enter your username: "<<endl;
        cin >> input1;
        cout << "Please enter your password: "<<endl;
        cin >> input2;
        if(input1 == _username && input2 == _password){
          cout<< "Welcome " << _username<<"!";
        }else{
          cout << "User not found."<< endl;
        }
      }
      User(string name,string username,string password);
};
User::User(string name,string username,string password){
  _name = name;
  _username = username;
  _password = password;
};