#include <std_lib_facilities.h>

int main()
{
    int i,k,r = 0,p = 1;
    for (k=0;k<8;k++){
        for (i=0;i<8;i++){
            std::cout << "* ";
        }
        std::cout << std::endl;
        r=r+p;
        if (r==2 || k==0){
            std::cout << " ";
            r=0;
        }
    }
    return 0;
}
