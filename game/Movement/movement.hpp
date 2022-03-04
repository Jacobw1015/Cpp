#include <iostream>

class Move{
   public:
     int m_x =0,m_y =0; 
  
   
        Move(){};
        void getCurrentLocation(){
          std::cout << "(" << m_x << ", " << m_y << ")\n";
        }

        void movePlayer(char c){
          
           
            if(c=='w'||c=='W'){
                m_y++;
            }else if(c=='s'||c=='S'){
                m_y--;
            }else if(c=='a'||c=='A'){
                m_x--;
            }else if(c=='d'||c=='D'){
                m_x++;
            }
         
           
        }
      
    
};