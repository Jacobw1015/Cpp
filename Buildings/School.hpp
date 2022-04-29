#pragma once
#include <iostream>
#include "Building.hpp"
#include "Student.hpp"
#include <vector>

using std::string;

class School: public Building{
    private:
   
    string SchoolName;
    std::vector<Student> Roster;
    
    public:
    School(string name, Address* add): Building(name,add){}
    // Getters
 


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
        this->getName();std::cout << " Enrolled: " << student.Name <<"\n";
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
