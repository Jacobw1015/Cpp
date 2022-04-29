#pragma once
#include <conio.h>
class Move
{
    private:
     int starting_x =0;
     int starting_y =0;
    public:
     int getX(){ return starting_x;}
     int getY(){ return starting_y;}

     void moveLoop()
     {
         char a;
         while (true)
         {
             a = _getch();
             if (a == 'q')
             {
                 break;
             }
             switch (a)
             {
             case 'w':
                 starting_y++; cout<< starting_y <<"\n";
                 break;
             case 'd':
                 starting_x++; cout<< starting_x <<"\n";
                 break;
             case 's':
                 starting_y--; cout<< starting_y <<"\n";
                 break;
             case 'a':
                 starting_x--; cout<< starting_x <<"\n";
                 break;
             }
         }
     }
};