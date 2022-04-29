#pragma once
#include <iostream>

#include "Human.hpp"
using std::string;

class Student: public Identity{
    private:
 string Major; 
     double GPA;
    protected:
     static int SchoolID;

    public: 
    
    int ID;
    Student(string name, int age, string major, double gpa ): Identity(name,age), Major(major), GPA(gpa){
      this->ID =++SchoolID;
    }
    
    void StudentInfo(){
        std::cout <<"Student Name: "<< this->Name<<" Age: "<< this->Age << " Major: "<< this->Major <<" GPA: "<< this->GPA << " School ID: " << this->ID <<"\n";
    }
    
    
};