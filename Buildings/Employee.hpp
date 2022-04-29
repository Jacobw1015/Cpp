#pragma once
#include <iostream>
#include <stdlib.h>
#include "Human.hpp"

class Employee : public Identity
{
private:
    double EmployeeSalary;

public:
    std::string JobTitle;
    int ID = 0;

    Employee(std::string name, int age, std::string jobttl) : Identity(name, age)
    {
        this->JobTitle = jobttl;
        this->createID();
    }
    void createID()
    {
        int idnum;

        idnum = rand() % 100;
        this->ID = idnum;
    }
    double getSalary() { return this->EmployeeSalary; }
    void setSalary(double amt) { this->EmployeeSalary = amt; }
};