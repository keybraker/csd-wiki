#include <std_lib_facilities.h>

int main()
{
    
    int i,k;
    for (k=0;k<8;k++){
        for (i=0;i<8;i++){
            std::cout << "* ";
        }
        std::cout << std::endl;
        if (k%2==0){std::cout << " ";}
    }
    return 0;
    
}

