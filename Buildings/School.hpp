#pragma once
#include <iostream>
#include "Address.hpp"
#include "Student.hpp"
#include <vector>

using std::string;

class School{
    private:
    Address* address;
    string SchoolName;
    std::vector<Student> Roster;
    
    public:
    School(string name, Address* add){
        this->SchoolName = name;
        this->address = add;
    }
    // Getters
    string getSchoolName(){return SchoolName; }

    void getAddress(){
        address->ListAddress();
    }

    std::vector<Student> getRoster(){
        return Roster;
    }
    void ListRoster(){
        std::cout << "Students: \n";
        for(auto i: getRoster()){
           i.StudentInfo();
           std::cout <<"\n";
        }
    }
   void addStudent(Student student){
       std::cout << this->getSchoolName()<< " Added: " << student.Name <<"\n";
    Roster.emplace_back(student);
    
   }

   void getStudentById(Student std){
       for(auto i : Roster){
           if( i.ID == std.ID){
               std.StudentInfo();
           }
       }
   } 

    School() = delete;
    School(const School&) = delete;
    School(const School&&) = delete;
};
