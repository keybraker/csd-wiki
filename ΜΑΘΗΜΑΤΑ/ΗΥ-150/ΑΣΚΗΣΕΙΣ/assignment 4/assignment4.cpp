#include <iostream>
#include <fstream>
#include <string>
#include "std_lib_facilities.h"

using namespace std;

struct Reading1 { // struct for reading from file oldmast
    
    int number1;
    string name1,name2;
    double number2;
    
    Reading1(int n1,string na1,string na2,double n2):number1(n1),name1(na1),name2(na2),number2(n2){}
    
};

struct Reading2 { // struct for reading from file transaction
    
    int number3;
    double number4;
    
    Reading2(int n3,double n4):number3(n3),number4(n4){}
    
};


int main(){
    
    fstream f1; // opening file oldmast
    f1.open("oldmast.txt",ios_base::in);
    if (!f1)error ("no file found\n"); // checking for error
    
    
    vector<Reading1> data1; // vector which stores data from oldmast
    int number1;
    string name1,name2;
    double number2;
    while (f1 >> number1 >> name1 >> name2 >> number2){
        data1.push_back(Reading1(number1,name1,name2,number2));
    }
    
    f1.close();

    
    fstream f2;// opening file transaction
    f2.open("transaction.txt",ios_base::in);
    if (!f2)error ("no file found\n");// checking for error
    
    vector<Reading2> data2;// vector which stores data from transaction
    int number3;
    double number4;
    while (f2 >> number3 >> number4) {
        data2.push_back(Reading2(number3,number4));
    }
    
    f2.close();

    
    ofstream f3;
    f3.open("newmast.txt"); // create new file to store the data
    if (!f3)error ("file not created\n");// checking for error
    
    int k = 0;
    for (int i=0; i<6; ++i) {//loop for data from file oldmast
        for (int j=0; j<6; ++j) {//loop for data from file transaction
            if (data1[i].number1 == data2[j].number3) {
                
                f3 << data1[i].number1 << " " << data1[i].name1 <<" "<<data1[i].name2 <<" "<< data1[i].number2 + data2[j].number4 << "\n" ;//storing information in newmast
            
            }else{   // if the the program goes 6 times in the loop, which means it didn't find its match
                k++; //it means that there is no match
            }
        }
        if (k==6) {// printing the unedit data
            f3 << data1[i].number1 << " " << data1[i].name1 <<" "<<data1[i].name2 <<" "<< data1[i].number2 << "\n" ;
        }
        k=0;
        
        
        
    }
    
    
    f3.close();

    
    
return 0 ;

}