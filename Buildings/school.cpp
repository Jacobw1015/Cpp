#include <iostream>
#include "School.hpp"
#include <vector>

int Student::SchoolID =0;

int main(){
    School school =School("Pemetic",new Address("101 Main st.", "Bar Harbor", "ME", "04661"));
    School school1 = School("MDI",new Address("102 Main st.","Bar Harbor", "ME", "04661"));

    std::vector<Student> Students;

    

    Student std =  Student("Jake", 25,"Cooking",3.1);
    Student std1 = Student("Colby",18, "Diving",2.2);
    Student std2 = Student("Steve",21, "Business",3.2);
    Student std3 = Student("Greg",32, "Marketing",4.0);
    Students.emplace_back(std);
    Students.emplace_back(std1);
    Students.emplace_back(std2);
    Students.emplace_back(std3);
    school.getName();
    school.getAddress();
  
    school1.getName();
    school1.getAddress();
    
    for(auto i: Students){
        school1.addStudent(i);

    }
    std::cout  << "\n";
    school1.ListRoster();
    std1.walk.moveLoop();

    return 0;
}