#include <iostream>

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

int main() {
    
    Vec2 v1;      //Creating 2 variables of type Vec2
    Vec2 v2;
    Vec2 result;  //Creating a variable that will store all the information
                  //from the proccessing of the two Vec2s
    
    v1.x = 2;
    v1.y = 3;
    
    v2.x = 1;
    v2.y = 4;
    
    std::cout << "Adding two variables of type Vec2: " ;
    result = v1 + v2;
    std::cout << result ;//Printing a variable of
    //type Vec2
    std::cout << "Subtracting two variables of type Vec2: " ;
    result = v1 - v2;
    std::cout << result ;
    
    std::cout << "Multiplying a variable of type Vec2 with an number: " ;
    result = v1 * 3;
    std::cout << result ;
    
    return 0;
    
}
