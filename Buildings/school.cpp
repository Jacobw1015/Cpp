#include <iostream>
#include "School.hpp"
#include <vector>

int Student::SchoolID =0;

int main(){
    School school =School("Pemetic",new Address("101 Main st.", "Bar Harbor", "ME", "04661"));
    School school1 = School("MDI",new Address("102 Main st.","Bar Harbor", "ME", "04661"));

    std::vector<Student> Students;

    

    Student std =  Student("Jake", 25,"Cooking",3.1);
    Student std1 = Student("Colby",18, "Diving",2.0);
    Students.emplace_back(std);
    Students.emplace_back(std1);
    std::cout << school.getSchoolName()<<"\n";
    school.getAddress();
  
    std::cout << school1.getSchoolName()<<"\n";
    school1.getAddress();
    
    for(auto i: Students){
        school1.addStudent(i);

    }
    std::cout  << "\n";
    school1.ListRoster();


    return 0;
}