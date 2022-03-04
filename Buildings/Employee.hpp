#pragma once
#include <iostream>
#include <stdlib.h>
#include "Human.hpp"

class Employee
{
    private: 
   Identity* Id;
   
  
   
    public:
     
      static int NextId; 
      int EmployeeId; 
      std::string JobTitle; 
    Employee(std::string jobttl, Identity* id){
       this->EmployeeId = ++NextId;
        
        this->JobTitle = jobttl;
        this->Id= id;
      
    }
    
    Identity getId(){
        return *Id;
    }

    void display(){
        std::cout << "Employee Name: " << Id->Name <<"\n"
        << "Employee Age: "<< Id->Age <<"\n"
        <<"Employee WID: "<< this->EmployeeId <<"\n"
        <<"Employee Job Title: " << this->JobTitle <<"\n";

    }
   
     Employee() = delete;
   
};