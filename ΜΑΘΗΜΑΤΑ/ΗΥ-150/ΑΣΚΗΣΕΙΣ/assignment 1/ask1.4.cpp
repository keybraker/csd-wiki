#include <std_lib_facilities.h>

int isPerfect(int k){
    
    int i,sum;
    i=1;
    sum=0;
    while(i<k){
        if(k%i==0){
            if (i!=1) {
                std::cout << " + " ;
            }
            sum=sum+i;
            std::cout << i ;
        }
        i++;
    }
    return 0;
}


int main()
{
        int k,i,sum;
        std::cout << "Perfect integers between 1 and 1000 are:" << std::endl ;
        for(k=1;k<=1000;k++){
            i=1;
            sum=0;
            while(i<k){
                if(k%i==0){
                    sum=sum+i;
                }
                i++;
            }
            
            if(sum==k){
                std::cout << k << " = " ;
                isPerfect(k);
                std::cout << std::endl ;
            }
        }
        return 0;
}

