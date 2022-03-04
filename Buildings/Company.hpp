#pragma once
#include <iostream>
#include "Employee.hpp"
#include <vector>
class Company{
    private:
    std::string CompanyName;
    Employee* employees;
    std::vector<Employee> Roster;
    protected:
    static int employeecount;
    public:
    Company(std::string name){
        this->CompanyName = name;
        ++employeecount;

    }
        void addEmployee(Employee employ){
            std::cout << employ.getId().Name <<" Added.\n";
            Roster.emplace_back(employ);
            ++employeecount;
        }
    std::vector<Employee> getRoster(){
        return Roster;
    }       

       std::string getCompanyName(){
           return CompanyName;
       } 
 static void employeeCounter(){
        std::cout << "Number of Employees: " << employeecount <<"\n";
    }

    
    void ShowRoster(){
        std::cout << "List of Employees: \n";
        
        for(auto i: getRoster()){
            i.display();
            std:: cout<<"\n";
        }
    }

    Company()=delete;
    Company(const Company&)=delete;
    Company(const Company&&)=delete;

};