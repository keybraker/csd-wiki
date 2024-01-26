  #include <iostream>
#include "Simple_window.h"
#include "Graph.h"

using namespace std;
using std::cout;
using std::ostream;

class Vec2{ //This is the class which contains x,y
public:
    
    float x;
    float y;
    
};

Vec2 operator+(const Vec2& left,const Vec2& right) //Overloadind the + operator
{                                                  //to add classes of type Vec2
    Vec2 ret;
    ret.x = left.x + right.x;
    ret.y = left.y + right.y;
    return ret;
}

Vec2 operator-(const Vec2& left,const Vec2& right) //Overloadind the - operator
{                                                  //to substract classes of type Vec2
    Vec2 ret;
    ret.x = left.x - right.x;
    ret.y = left.y - right.y;
    return ret;
}

Vec2 operator*(const Vec2& one,const float x)     //Overloadind the * operator to multiply
{                                                 //classes of type Vec2 with a number
    Vec2 ret;
    ret.x = one.x * x;
    ret.y = one.y * x;
    return ret;
}

std::ostream& operator<<(std::ostream& os,const Vec2& v) //Overloadind the << operator
{                                                        //to print classes of type Vec2
    return os<< "(" << v.x << "," << v.y << ")" << std::endl ;
}

//End of part 1 of the exercise

int main()
{
    using namespace Graph_lib;
    
    Point tl(100,100);
    Simple_window win(tl,600,400,"Tsiakkas");    //Creating a window with the  dimentions 600x400
    //starting at point 100x100
    Mark p1(Point(300,50), 'x');                 //printing x at 300,50
    Mark p2(Point(100,300), 'x');                //printing x at 250,150
    Mark p3(Point(500,300), 'x');                //printing x at 350,150
    
    win.attach (p1);                             //attaching x to screen
    win.attach (p2);                             //attaching x to screen
    win.attach (p3);                             //attaching x to screen
    
    int tuxaio;  //The random number wich can get one of three numbers:0,1,2
    int i;
    
    Vec2 up;            //Creating the three points of type Vec2
    Vec2 left;          //for every corner of the triangle
    Vec2 right;         //up,left,right
    Vec2 p;
    Vec2 pointer;
    Vec2 q;
    Vec2  Table [5000]; //Table that includes every point that will eventually create the
    //Sierpinski triangle
    
    up.x = 300; left.x = 100; right.x = 500;
    up.y = 50; left.y = 300; right.y = 300;
    
    p.x = 250;
    p.y = 150;
    
    for (i=0; i<5000; ++i) {
        
        tuxaio = rand() % 3; //Giving tuxaio a random number betwen 0 and 2
        
        if(tuxaio == 0){        //Depending on what tuxaio is, pointer (of type Vec2) will get to be
            pointer.x = up.x;   //one of the three edges of the triangle
            pointer.y = up.y;
        }else if(tuxaio == 1){
            pointer.x = left.x;
            pointer.y = left.y;
        }else{
            pointer.x = right.x;
            pointer.y = right.y;
        }
        
        q.x = (pointer.x + p.x) * (0.5);  //Making q (of type Vec2) the point halfway between
        q.y = (pointer.y + p.y) * (0.5);  //p and pointer
        
        Table[i] = q ;  //Putting q in the array that contains all the point
        //that will eventually create the Sierpinski triangle
        
        //std::cout <<  Table[i] ;
        
        p = q;
        
    }
    
    Marks pp(".");
    
    for(i=0;i<5000;++i){                         //Eventually, after all the information is generated
        pp.add(Point (Table[i].x,Table[i].y));   //and every single one of the 5000 points found, the
    }                                            //the program starts printing all those point on screen
                                                 //to create the Sierpinski triangle
    win.attach (pp);
    win.wait_for_button();
    
}