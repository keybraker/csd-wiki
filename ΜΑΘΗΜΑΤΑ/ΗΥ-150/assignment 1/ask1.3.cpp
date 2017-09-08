#include <std_lib_facilities.h>

char multiple(int a,int b){
    if (a==b) {
        return true;
    }
    while (a<b) {
        a += a;
        if (a==b) {
            return true;
        }
    }
    return false;
}



int main()
{
    int a,b,i=1;
    char what;
    
    while (i==1){
        std::cout << "Enter two integers:";
        std::cin >> a;
        std::cin >> b;
        what = multiple(a,b);
        if (what==false) {
            std::cout << b << " is not a multiple of " << a << "\n\n";
        }else{
            std::cout << b << " is a multiple of " << a << "\n\n";
        }
    }
    return 0;
}


