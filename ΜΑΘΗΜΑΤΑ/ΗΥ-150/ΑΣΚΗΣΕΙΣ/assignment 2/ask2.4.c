#include <std_lib_facilities.h>

// transferring vector, the current position, the keyword, and the size of the vector
int recusrsiveLinearSearch(std::vector<int>& zugoi,int place,int key,int k){

    if (place>k || key%2!=0) {           // Checks whether or not we have gone through the whole vector or the keyword is a odd.
        return -1;                       // If so, the function stops and returns -1 because the keyword did not match with any
    }                                    // element in the vetor
    if (zugoi[place]==key){              // Compares one element of the vector with the keyword
        return place;
    }else{                               // is the keyword is not found variable place increases by one
        place++;                         // and function calls itself to compare the next element of the vector
        place=recusrsiveLinearSearch(zugoi,place,key,k); // if function finds the keyword in the vector, it returns it and place
    }                                    // is now correct in every previous function
    return place;
}


int main()
{
    int i,k,key,solution,place=0;
    
    std::cout << "Enter the integer search key:";
    std::cin >> key;
    
    std::vector <int> zugoi;
    k=0;
    for (i=0; i<201; i++) {            // making a loop that ends when i you reaches 201, because 200 is an even number
        if (i%2==0) {                  // checks whether or not all i is even
            zugoi.push_back(i);        // puts the current number which is even in the vector
            k++;                       // increases k by one so that in the end of the loop, k can represent the number of even
        }                              // numbers in the vector
    }
    
    solution = recusrsiveLinearSearch(zugoi,place,key,k);
    
    if (solution != -1) {
        std::cout << "Found value in element " << solution << std::endl;
    }else{
        std::cout << "Value not found" << std::endl;
    }
    return 0;
}

