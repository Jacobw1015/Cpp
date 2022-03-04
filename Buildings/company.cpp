#include <iostream>
#include "Company.hpp"

int Company::employeecount=0;
int Employee::NextId = 0;

int main(){
    Company united = Company("United");

    Identity id3= Identity("Eddy Graddy",15);
    Identity id1= Identity("Jacob",25);
    Identity id2= Identity("Jakub",30);
    
    Employee e1 = Employee( "IT Associate",&id1);
   Employee e2 = Employee( "IT HelpDesk",  &id2 );
    Employee e3 = Employee ("FM Operator", &id3);
    
    united.addEmployee(e1);
    united.addEmployee(e2);
    united.addEmployee(e3);

    Company::employeeCounter();
    std::cout <<"\n";
    united.ShowRoster();

    return 0;
}