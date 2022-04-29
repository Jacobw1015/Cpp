#pragma once
#include "Building.hpp"
#include <iostream>

#include "Employee.hpp"
#include <vector>
class Company: public Building{
    private:
    double CompanyValue;
    std::vector<Employee> Roster;
    int Employeecount = 0;
    
    public:
    
    Company(std::string name, Address* address, double compval): Building(name,address){
       this->CompanyValue = compval;
        ++Employeecount;

    }
        void addEmployee(Employee employ){
            std::cout << employ.Name <<" Added.\n";
            Roster.emplace_back(employ);
            ++Employeecount;
            
        }
    std::vector<Employee> getRoster(){
        return Roster;
    }       

    int getCompanyValue(){
        return CompanyValue;
    }

    void setPayment(){
        double SalaryToPay=((this->CompanyValue*0.25)/Roster.size());
        if(SalaryToPay <0) SalaryToPay =0;
        for(auto &i : Roster){
        i.setSalary(SalaryToPay);
    
        }
        
    }

  // Functions for displaying Employee info 

    void display(Employee* employ){
        std::cout << "Employee Name: " << employ->Name <<"\n"
        << "Employee Age: "<< employ->Age <<"\n"
        <<"Employee WID: "<< employ->ID<<"\n"
        <<"Employee Job Title: " << employ->JobTitle <<"\n"
        <<"Employee Salary: " << employ->getSalary()<<"\n";

    }
     
  void employeeCounter(){
        std::cout << "Number of Employees: " << Employeecount <<"\n";
    }

    
    void ShowRoster(){
        std::cout << "List of Employees: \n";
        
        for(auto i: Roster){
            this->display(&i);
            std:: cout<<"\n";
        }
    }

    Company()=delete;
    Company(const Company&)=delete;
    Company(const Company&&)=delete;

};