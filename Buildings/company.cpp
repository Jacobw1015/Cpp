#include <iostream>
#include "Company.hpp"
#include <cstdlib>




int main(){
     srand(time(NULL));// Seed random number generator for Employee ID

    Company united = Company("United",new Address("1012 Sub st.","Ellsworth", "ME","40645"),200000);
    Company delta = Company("Delta",new Address("1013 Sub st.","Ellsworth", "ME","40644"),200500);
    Company southwest = Company("Southwest",new Address("1014 Sub st.","Ellsworth", "ME","40644"),205000);


  




    return 0;
}