#include <std_lib_facilities.h>

int main()
{
    int x, y;
    
    std::cout << "a:x=11,y=9:" << std::endl;
    
    x=11;
    y=9;
    if (x<10)
        if (y>10)
            std::cout << "*****" << std::endl;
        else
            std::cout << "#####" << std::endl;
    std::cout << "$$$$$" << std::endl;
    
    std::cout << "a:x=9,y=11:" << std::endl;
    
    x=9;
    y=11;
    if (x<10)
        if (y>10)
            std::cout << "*****" << std::endl;
        else
            std::cout << "#####" << std::endl;
    std::cout << "$$$$$" << std::endl;
    
    std::cout << "b:x=11,y=9:" << std::endl;
    
    x=11;
    y=9;
    if (x<10){
        if (y>10){
            std::cout << "*****" << std::endl;
        }else{
            std::cout << "#####" << std::endl;
            std::cout << "$$$$$" << std::endl;
        }
    }
    std::cout << "b:x=9,y=11:" << std::endl;
    
    x=9;
    y=11;
    if (x<10){
        if (y>10){
            std::cout << "*****" << std::endl;
        }else{
            std::cout << "#####" << std::endl;
            std::cout << "$$$$$" << std::endl;
        }
    }
    return 0;
}

