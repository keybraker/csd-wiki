//
//  JSONlang.h
//  JSON IN C++ (PROJECT) HY352
//
//  Created by Ioannis Tsiakkas on 12/6/16.
//  Copyright © 2016 Ioannis Tsiakkas. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
#include <map>

#define PROGRAM_BEGIN int main(){ string member = "MEMBERS"; string tmp; myType mytmp
#define PROGRAM_END ;return 0;}

#define PROGRAM_BEGIN_PRINT ;cout << "JSONprojectHY352 starting execution" << endl
#define PROGRAM_END_PRINT ;cout << "JSONprojectHY352 execution has ended" << endl

#define JSON(var) ;myType var
#define KEY(name) myType(tmp = #name) = 0 ? 0
#define STRING(name) myType(tmp = name)
#define NUMBER(name) myType(name)
#define OBJECT *new myType
#define ARRAY myType(member)
#define SET ;
#define ASSIGN *=
#define APPEND %=
#define ERASE ;mytmp /=
#define PRINT ;cout <<
#define TRUE myType(true)
#define FALSE myType(false)
#define MAX_INT_JSON 9999999

#define SIZE_OF(json) json.SIZE_OF_ME()
#define IS_EMPTY(json) json.IS_EMPTY_ME()
#define HAS_KEY(json,key) json.HAS_KEY_ME(key)
#define TYPE_OF(json) json.TYPE_OF_ME()

using namespace std;

#ifndef JSONlang_h
#define JSONlang_h

//#define printerino(what, this) cout << what  << " ->OVERLOADED TO-> " << this << endl;
#define printerino(what, this)

bool tr = true;
bool fl = false;

/**
 *  1.struct myType
 *  2.keeps all variables private
 *  3.gives access to edit varialbes via functions
 */

struct myType{
public:

    /*Printing JSON OBJECT*/
    friend ostream &operator<<(ostream &os, myType &js){

        if(js.hidden == true){return os;}
        if(js.willgeterased == true){
            js.willgeterased = false;

            for(int i = 0; i < js.headOFdata.size() ; i++){
                js.headOFdata[i].deleteMe = false;

                if(js.headOFdata[i].willgeterased == true){

                    if(js.headOFdata[i].which == 1){

                        cout << js.headOFdata[i].getSTRING();

                    }else if(js.headOFdata[i].which == 2 || js.headOFdata[i].which == 3){

                        cout << js.headOFdata[i].getINTEGER();

                    }else if(js.headOFdata[i].which == 4){

                        cout << js.headOFdata[i].getBOOLEAN();

                    }else if(js.headOFdata[i].which == 5){

                        for(int j = 0; j < js.headOFdata[i].array.size(); j++){
                            cout << j << ") " << js.headOFdata[i].array[j];
                        }

                    }else if(js.headOFdata[i].which == 6 || js.headOFdata[i].which == 7){
                        cout << js.headOFdata[i];
                        return os;
                        for( int j = 0; j < js.headOFdata[i].headOFdata.size(); j++ ){

                            cout << js.headOFdata[i].headOFdata[j].willgeterased;
                            if(js.headOFdata[i].headOFdata[j].willgeterased == true){

                                js.headOFdata[i].headOFdata[j].willgeterased = false;
                                cout << js.headOFdata[i].headOFdata[j];

                                return os;
                            }

                        }
                        cout << js.headOFdata[i];

                    }else{
                        js.headOFdata[i].willgeterased = false;
                        js.willgeterased = false;
                        return os;
                        cout << "NULL";
                    }
                    js.headOFdata[i].willgeterased = false;
                    cout << endl;
                    js.willgeterased = false;
                    return os;

                }
            }
        }

        ///////////////////////////////////////////

        if(js.which == 1){
            cout << js.getNAME() << ":\"" << js.getSTRING() << "\"";
        }else if(js.which == 2 || js.which == 3){
            cout << js.getNAME() << ":" << js.getINTEGER();
        }else if(js.which == 4){
            cout << js.getNAME() << ":";
            if(js.getBOOLEAN() == 1){
                cout << "TRUE";
            }else{
                cout << "FALSE";
            }
        }else if(js.which == 5){

            cout << "array[";
            for(int i = 0; i < js.getARRAY().size() ; i++){
                cout << js.getARRAY()[i] ;
                cout << ", ";
            }
            cout << "]" << endl;

        }else if(js.which == 6 || js.which == 7){

            if(js.getNAME() != ""){
                cout << js.getNAME() << ": { ";

                for(int i = 0; i < js.headOFdata.size(); i++){
                    if(js.headOFdata[i].which == 6 || js.headOFdata[i].which == 7){
                        for(int j = 0; j < js.headOFdata[i].headOFdata.size(); j++){
                            js.headOFdata[i].headOFdata[j].isMeme = true;
                        }
                    }else{
                        js.headOFdata[i].isMeme = true;
                    }
                }
            }
            for(int i = 0; i < js.headOFdata.size(); i++){
                cout << js.headOFdata[i];
            }

            if(js.getNAME() != ""){
                cout << "}" << endl;
            }

        }else{
            return os;
            cout << "NULL";
        }

        if(js.headOFdata.size() != 0){
            return os;
        }else if(js.isMeme == false && js.which < 8){
            cout << endl;
        }else{
            cout << ", ";
        }
        return os;
    
    }
    friend ostream &operator<<(ostream &os, myType *js){

        if(js->hidden == true){return os;}
        if(js->willgeterased == true){
            js->willgeterased = false;

            for(int i = 0; i < js->headOFdata.size() ; i++){
                js->headOFdata[i].deleteMe = false;

                if(js->headOFdata[i].willgeterased == true){

                    if(js->headOFdata[i].which == 1){

                        cout << js->headOFdata[i].getSTRING();

                    }else if(js->headOFdata[i].which == 2 || js->headOFdata[i].which == 3){

                        cout << js->headOFdata[i].getINTEGER();

                    }else if(js->headOFdata[i].which == 4){

                        cout << js->headOFdata[i].getBOOLEAN();

                    }else if(js->headOFdata[i].which == 5){

                        for(int j = 0; j < js->headOFdata[i].array.size(); j++){
                            cout << j << ") " << js->headOFdata[i].array[j];
                        }

                    }else if(js->headOFdata[i].which == 6 || js->headOFdata[i].which == 7){
                        cout << js->headOFdata[i];
                        return os;
                        for( int j = 0; j < js->headOFdata[i].headOFdata.size(); j++ ){

                            cout << js->headOFdata[i].headOFdata[j].willgeterased;
                            if(js->headOFdata[i].headOFdata[j].willgeterased == true){

                                js->headOFdata[i].headOFdata[j].willgeterased = false;
                                cout << js->headOFdata[i].headOFdata[j];

                                return os;
                            }

                        }
                        cout << js->headOFdata[i];

                    }else{
                        js->headOFdata[i].willgeterased = false;
                        js->willgeterased = false;
                        return os;
                        cout << "NULL";
                    }
                    js->headOFdata[i].willgeterased = false;
                    cout << endl;
                    js->willgeterased = false;
                    return os;

                }
            }
        }

        ///////////////////////////////////////////

        if(js->which == 1){
            cout << js->getNAME() << ":\"" << js->getSTRING() << "\"";
        }else if(js->which == 2 || js->which == 3){
            cout << js->getNAME() << ":" << js->getINTEGER();
        }else if(js->which == 4){
            cout << js->getNAME() << ":";
            if(js->getBOOLEAN() == 1){
                cout << "TRUE";
            }else{
                cout << "FALSE";
            }
        }else if(js->which == 5){

            cout << "array[";
            for(int i = 0; i < js->getARRAY().size() ; i++){
                cout << js->getARRAY()[i] ;
                cout << ", ";
            }
            cout << "]" << endl;

        }else if(js->which == 6 || js->which == 7){

            if(js->getNAME() != ""){
                cout << js->getNAME() << ": { ";

                for(int i = 0; i < js->headOFdata.size(); i++){
                    if(js->headOFdata[i].which == 6 || js->headOFdata[i].which == 7){
                        for(int j = 0; j < js->headOFdata[i].headOFdata.size(); j++){
                            js->headOFdata[i].headOFdata[j].isMeme = true;
                        }
                    }else{
                        js->headOFdata[i].isMeme = true;
                    }
                }
            }
            for(int i = 0; i < js->headOFdata.size(); i++){
                cout << js->headOFdata[i];
            }

            if(js->getNAME() != ""){
                cout << "}" << endl;
            }

        }else{
            return os;
            cout << "NULL";
        }

        if(js->headOFdata.size() != 0){
            return os;
        }else if(js->isMeme == false && js->which < 8){
            cout << endl;
        }else{
            cout << ", ";
        }
        return os;
    
    }

    /* CONSTRUCTORS */

    /* constructor for EMPTY */
    myType() : which(8) {};
    /* constructor for LIST OF MYTYPE */
    myType(initializer_list<myType> Head){

        vector<myType>::iterator head_iterator;
        head_iterator = this->headOFdata.begin();
        head_iterator = this->headOFdata.insert ( head_iterator , Head );
        this->setWHICH(7);

    };
    /* constructor for STRING */
    myType(const string &Str) : name(Str),which(1) {};
    /* constructor for INTEGER */
    myType(const int Integer) : integer(Integer),which(2) {};
    /* constructor for DOUBLE */
    myType(const double Integer) : integer(Integer),which(2) {};
    /* constructor for BOOLEAN */
    myType(const bool Boolean) : boolean(Boolean), which(4) {};

    /*OPERATOR OVERLOAD FOR STR,NUM,BOOL,OBJ*/
    myType &operator=( myType value){ printerino(value, this)

        this->setWHICH(value.which);
        if(this->getINTEGER() != MAX_INT_JSON && value.getINTEGER() != MAX_INT_JSON){
            this->getARRAY().push_back(this->getINTEGER());
            this->getARRAY().push_back(value.getINTEGER());
        }
        if(value.which == 1){
            this->setSTRING(value.name);
        }else if(value.which == 2){
            this->setINTEGER(value.integer);
        }else if(value.which == 3){
            this->setINTEGER(value.integer);
        }else if(value.which == 4){
            this->setBOOLEAN(value.boolean);
        }else if(value.which == 6 || value.which == 7){
            this->headOFdata.push_back(value);
        }else{
            for(int i = 0; i < value.getARRAY().size() ; i++){
                this->array.push_back(value.getARRAY()[i]);
            }
        }
        return *this;
    };

    myType &operator=( myType *value){ printerino(value, this)

        this->setWHICH(value->which);
        if(value->which == 1){
            this->setSTRING(value->name);
        }else if(value->which == 2 || value->which == 3){
            this->setINTEGER(value->integer);
        }else if(value->which == 4){
            this->setBOOLEAN(value->boolean);
        }else if(value->which == 6 || value->which == 7){
            this->headOFdata.push_back(value);
        }else{
            for(int i = 0; i < value->getARRAY().size(); i++){
                this->array.push_back(value->getARRAY()[i]);
            }
        }
        return *this;
    };

    myType &operator,(myType value){ printerino(value, this)

        if((value.which == 2 || value.which == 3) && value.name == "" ){
            //it is an array of intigers so goes to array

            if(this->isARRAYempty()){
                this->array.push_back(this->getINTEGER());
                this->edited = true;
            }

            //if(this->edited == true){
              //  this->array.push_back(this->getINTEGER());
            //}

            this->array.push_back(value.getINTEGER());
            this->setWHICH(5);

        }else if(this->getNAME() != "" ){
            //overloads this with itsels and value and returns

            myType joker = *this;

            this->clear();
            this->setWHICH(6);
            this->setMEMBER(true);

            this->headOFdata.push_back(joker);
            this->headOFdata.push_back(value);

        }else if(this->getNAME() == "" && value.getNAME() == ""){
            //overloads this with itsels and value and returns

            myType joker = *this;

            this->clear();
            this->setWHICH(6);
            this->setMEMBER(true);

            this->headOFdata.push_back(joker);
            this->headOFdata.push_back(value);
        }else{
            //it is an array of intigers so goes to array

            array.push_back(value.getINTEGER());
            this->setWHICH(5);

        }

        return *this;

    };
    myType &operator,(myType *value){ printerino(value, this)

        if((value->which == 2 || value->which == 3)){
            //it is an array of intigers so goes to array

            if(this->isARRAYempty()){
                this->array.push_back(this->getINTEGER());
            }
            this->array.push_back(value->getINTEGER());
            this->setWHICH(5);

        }else if(this->getNAME() != "" ){
            //overloads this with itsels and value and returns

            myType joker = *this;

            this->clear();
            this->setWHICH(6);
            this->setMEMBER(true);

            this->headOFdata.push_back(joker);
            this->headOFdata.push_back(value);

        }else{
            //it is an array of intigers so goes to array

            array.push_back(value->getINTEGER());
            this->setWHICH(5);

        }
        return *this;

    };

    myType operator[](myType Head){return Head;};
    myType operator[](myType *Head){return Head;};

    myType &operator*=(string namer){ printerino(namer, this)

        myType tmp;

        // ERASE
        if(this->willgeterased == false){
            this->deleteMe = false;

            for(int i = 0; i < this->headOFdata.size() ; i++){
                this->headOFdata[i].deleteMe = false;

                if(this->headOFdata[i].getNAME() == namer){
                    this->headOFdata[i].willgeterased = true;
                    this->willgeterased = true;

                    return *this;

                }
                this->headOFdata[i] *= namer;
            }

        }else if(this->willgeterased == true){

            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                this->headOFdata[i].deleteMe = false;

                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;

                    for(int j = 0 ; j < this->headOFdata[i].headOFdata.size() ; j++ ){
                        this->headOFdata[i].headOFdata[j].deleteMe = false;

                        if(this->headOFdata[i].headOFdata[j].getNAME() == namer){
                            this->headOFdata[i].headOFdata[j].willgeterased = true;
                            this->headOFdata[i].willgeterased = false;

                            return *this;

                        }

                        for(int l = 0 ; l < this->headOFdata[i].headOFdata[j].headOFdata.size() ; l++ ){
                            this->headOFdata[i].headOFdata[j].headOFdata[l].deleteMe = false;

                            if(this->headOFdata[i].headOFdata[j].headOFdata[l].getNAME() == namer){
                                this->headOFdata[i].headOFdata[j].headOFdata[l].willgeterased = true;
                                this->headOFdata[i].headOFdata[j].willgeterased = false;

                                return *this;

                            }

                        }

                    }
                    // taking the mark of because i dont want to delete
                    // the whole data just a certain one
                    this->willgeterased = false;
                }
                this->willgeterased = false;
            }
        }
        return *this;

    }

    myType &operator[](int what){ printerino(what, this)

        this->place = what;
        if(!this->isARRAYempty()){
            if(this->array.size() > what){
                this->array[what] = MAX_INT_JSON;
            }
        }else{
            myType NEW;
            NEW.hidden = true;

            if(this->headOFdata.size() >= what){

                if(what == 0){
                    this->headOFdata.push_back(NEW);
                }else{
                    this->headOFdata[what].headOFdata.push_back(NEW);
                }

            }else{ cout << "DID NOT INSERT NUMBER > SIZE" << endl; }
        }

        return *this;
    }
    myType &operator[](const char* what){ printerino(what, this)

        string namer = what;
        myType tmp;

        if(this->place != -1 && this->headOFdata.size() >= this->place){
            if(this->place == 0 && this->headOFdata.size() == 0){
                this->hidden = true;
                this->willgeterased = false;
                return *this;
            }
            for(int i = 0; i < this->headOFdata[place].headOFdata.size() ; i++){
                if(this->headOFdata[place].headOFdata[i].getNAME() == namer){
                    this->headOFdata[place].headOFdata[i].hidden = true;
                    //cout << "gotcha !\n";
                    this->willgeterased = false;
                    return *this;
                }
            }
        }
        bool check = false;
        for(int i = 0; i < this->headOFdata.size() ; i++){
            if(this->headOFdata[i].getNAME() == namer){
                this->willgeterased = false;
                check = true;
            }
        }

        // ERASE
        if(this->willgeterased == false){
            this->deleteMe = false;

            for(int i = 0; i < this->headOFdata.size() ; i++){
                this->headOFdata[i].deleteMe = false;

                if(this->headOFdata[i].getNAME() == namer){
                    this->headOFdata[i].willgeterased = true;
                    this->willgeterased = true;

                    return *this;

                }
                this->headOFdata[i] *= namer;
            }

        }else if(this->willgeterased == true){

            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                this->headOFdata[i].deleteMe = false;

                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;

                    for(int j = 0 ; j < this->headOFdata[i].headOFdata.size() ; j++ ){
                        this->headOFdata[i].headOFdata[j].deleteMe = false;

                        if(this->headOFdata[i].headOFdata[j].getNAME() == namer){
                            this->headOFdata[i].headOFdata[j].willgeterased = true;
                            this->headOFdata[i].willgeterased = false;

                            return *this;

                        }

                        for(int l = 0 ; l < this->headOFdata[i].headOFdata[j].headOFdata.size() ; l++ ){
                            this->headOFdata[i].headOFdata[j].headOFdata[l].deleteMe = false;

                            if(this->headOFdata[i].headOFdata[j].headOFdata[l].getNAME() == namer){
                                this->headOFdata[i].headOFdata[j].headOFdata[l].willgeterased = true;
                                this->headOFdata[i].headOFdata[j].willgeterased = false;

                                return *this;

                            }

                        }

                    }
                    // taking the mark of because i dont want to delete
                    // the whole data just a certain one
                    this->willgeterased = false;
                }
                this->willgeterased = false;
            }
            return *this;
        }

        // APPEND
        for(int i = 0; i < this->headOFdata.size() ; i++){

            if(this->headOFdata[i].hidden == true){

                string tmp;
                myType NEW =  myType(tmp = what);

                this->headOFdata[i].setNAME(tmp = what);
                this->headOFdata[i].setWHICH(1);

            }
            for(int j = 0; j < this->headOFdata[i].headOFdata.size() ; j++){

                if(this->headOFdata[i].headOFdata[j].hidden == true){

                    string tmp;
                    myType NEW =  myType(tmp = what);

                    this->headOFdata[i].headOFdata[j].setNAME(tmp = what);
                    this->headOFdata[i].headOFdata[j].setWHICH(1);

                }
            }
        }
        this->willgeterased = false;
        return *this;
    }

    //OPERATORS USED FOR EDITING
    myType &operator*=( myType value){ printerino(value, this)

        if(this->which == 5){
            for(int i = 0; i < this->getARRAY().size() ; i++){
                if(this->array[i] == MAX_INT_JSON){
                    this->array[i] = value.integer;
                    return *this;
                }
            }
        }
        // allagh tou uparxon
        for(int i = 0; i < this->headOFdata.size() ; i++){

            if(this->headOFdata[i].willgeterased == true){

                edit(this->headOFdata[i], value);
                if(this->headOFdata.back().getNAME() == ""){
                    this->headOFdata.pop_back();
                }
                cleanFROMflags(*this);
                return *this;

            }
            for(int j = 0; j < this->headOFdata[i].headOFdata.size() ; j++){

                if(this->headOFdata[i].headOFdata[j].willgeterased == true){

                    edit(this->headOFdata[i].headOFdata[j], value);
                    if(this->headOFdata.back().getNAME() == ""){
                    this->headOFdata.pop_back();
                }
                    cleanFROMflags(*this);
                    return *this;

                }
            }
        }

        // sunexia dimiourgias antikeimenou
        for(int i = 0; i < this->headOFdata.size() ; i++){

            if(this->headOFdata[i].hidden == true){

                //if(this->headOFdata[i].getNAME() != ""){
                    edit(this->headOFdata[i], value);
                    cleanFROMflags(*this);
                    return *this;
                //}else{
                //    break;
                //}
            }
            for(int j = 0; j < this->headOFdata[i].headOFdata.size() ; j++){

                if(this->headOFdata[i].headOFdata[j].hidden == true){

                    edit(this->headOFdata[i].headOFdata[j], value);
                    cleanFROMflags(*this);
                    return *this;

                }
            }
        }
        edit(*this, value);
        //PROBLEM
        //        if(this->headOFdata.back().getNAME() == ""){
        //            this->headOFdata.pop_back();
        //        }
        cleanFROMflags(*this);
        return *this;

    }
    myType &operator*=( myType *value ){ cout << "the other "; printerino(value, this)

        if(this->which == 5){
            for(int i = 0; i < this->getARRAY().size() ; i++){
                if(this->array[i] == MAX_INT_JSON){
                    this->array[i] = value->integer;
                    return *this;
                }
            }
        }

        // 8a allakso to uparxon
        for(int i = 0; i < this->headOFdata.size() ; i++){

            if(this->headOFdata[i].willgeterased == true){

                edit(this->headOFdata[i], *value);
                if(this->headOFdata.back().getNAME() == ""){
                    this->headOFdata.pop_back();
                }
                cleanFROMflags(*this);
                return *this;

            }
            for(int j = 0; j < this->headOFdata[i].headOFdata.size() ; j++){

                if(this->headOFdata[i].headOFdata[j].willgeterased == true){

                    edit(this->headOFdata[i].headOFdata[j], *value);
                    if(this->headOFdata.back().getNAME() == ""){
                        this->headOFdata.pop_back();
                    }
                    cleanFROMflags(*this);
                    return *this;

                }
            }
        }

        // sunexizo na dimiourgo to antikeimeno
        for(int i = 0; i < this->headOFdata.size() ; i++){

            if(this->headOFdata[i].hidden == true){

                //if(this->headOFdata[i].getNAME() != ""){
                    edit(this->headOFdata[i], *value);
                    cleanFROMflags(*this);
                    return *this;
                //}else{
                //    break;
                //}
            }
            for(int j = 0; j < this->headOFdata[i].headOFdata.size() ; j++){

                if(this->headOFdata[i].headOFdata[j].hidden == true){

                    edit(this->headOFdata[i].headOFdata[j], *value);
                    cleanFROMflags(*this);
                    return *this;

                }
            }
        }

        edit(*this, *value);
        if(this->headOFdata.back().getNAME() == ""){
            this->headOFdata.pop_back();
        }
        cleanFROMflags(*this);
        return *this;

    }

    myType &operator%=( myType value ){ printerino(value, this)

        if(this->which == 5){
            for(int i = 0; i < this->getARRAY().size() ; i++){
                if(this->array[i] == MAX_INT_JSON){

                    this->array[i] = value.integer;
                    return *this;

                }
            }
        }
        for(int i = 0; i < this->headOFdata.size() ; i++){
            for(int j = 0; j < this->headOFdata[i].headOFdata.size() ; j++){
                if(this->headOFdata[i].headOFdata[j].hidden == true){
                    this->headOFdata[i].headOFdata[j].hidden = false;

                    if(this->getINTEGER() != MAX_INT_JSON && value.getINTEGER() != MAX_INT_JSON){
                        this->headOFdata[i].headOFdata[j].getARRAY().push_back(this->getINTEGER());
                        this->headOFdata[i].headOFdata[j].getARRAY().push_back(value.getINTEGER());
                    }
                    if(value.which == 1){
                        if(value.getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);

                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value.getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setSTRING(value.getSTRING());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value.getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            if(value.getNAME() != ""){
                                // prepei na to valo epeidi einai object

                                this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            }else{
                                this->headOFdata[i].headOFdata[j].setSTRING(value.name);
                                this->headOFdata[i].headOFdata[j].setWHICH(value.which);
                            }
                        }
                    }else if(value.which == 2){
                        if(value.getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value.getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value.getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value.getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].setINTEGER(value.integer);
                            this->headOFdata[i].headOFdata[j].setWHICH(value.which);
                        }
                    }else if(value.which == 3){
                        if(value.getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value.getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value.getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value.getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].setINTEGER(value.integer);
                            this->headOFdata[i].headOFdata[j].setWHICH(value.which);
                        }
                    }else if(value.which == 4){
                        if(value.getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value.getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value.getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setBOOLEAN(value.getBOOLEAN());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].setBOOLEAN(value.boolean);
                            this->headOFdata[i].headOFdata[j].setWHICH(value.which);
                        }
                    }else if(value.which == 5){
                        for(int i = 0; i < this->headOFdata[i].headOFdata[j].getARRAY().size() ; i++){
                            if(this->headOFdata[i].headOFdata[j].array[i] == MAX_INT_JSON){
                                this->headOFdata[i].headOFdata[j].array[i] = value.integer;
                            }
                        }
                    }else if(value.which == 6 || value.which == 7){
                        if(value.getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value.getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value.getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value.getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].addHEADOFDATA(value);
                            this->headOFdata[i].headOFdata[j].setWHICH(value.which);
                        }
                    }else{
                        cout << "which = " << which << endl;
                    }
                    this->headOFdata.pop_back();
                    cleanFROMflags(*this);
                    return *this;
                }
            }
        }

        if(this->getINTEGER() != MAX_INT_JSON && value.getINTEGER() != MAX_INT_JSON){
            this->getARRAY().push_back(this->getINTEGER());
            this->getARRAY().push_back(value.getINTEGER());
        }
        if(value.which == 1){
            this->array.push_back(value.integer);
            this->setSTRING(value.name);
            this->setWHICH(value.which);
        }else if(value.which == 2){
            this->array.push_back(value.integer);
            //this->setINTEGER(value.integer);
            //this->setWHICH(value.which);
        }else if(value.which == 3){
            this->setINTEGER(value.integer);
            this->setWHICH(value.which);
        }else if(value.which == 4){
            this->setBOOLEAN(value.boolean);
            this->setWHICH(value.which);
        }else if(value.which == 6){
            this->addHEADOFDATA(value);
            this->setWHICH(value.which);
        }else if(value.which == 7){
            this->addHEADOFDATA(value);
            this->setWHICH(6);
        }else if(value.which == 5){

            for(int i = 0; i < this->getARRAY().size() ; i++){
                if(this->array[i] == MAX_INT_JSON){
                    this->array[i] = value.integer;
                }
            }

        }else{
            cout << "which = " << which << endl;
        }
        cleanFROMflags(*this);
        return *this;
    }
    myType &operator%=( myType *value ){ printerino(value, this)

        for(int i = 0; i < this->headOFdata.size() ; i++){
            for(int j = 0; j < this->headOFdata[i].headOFdata.size() ; j++){
                if(this->headOFdata[i].headOFdata[j].hidden == true){
                    this->headOFdata[i].headOFdata[j].hidden = false;

                    if(this->getINTEGER() != MAX_INT_JSON && value->getINTEGER() != MAX_INT_JSON){
                        this->headOFdata[i].headOFdata[j].getARRAY().push_back(this->getINTEGER());
                        this->headOFdata[i].headOFdata[j].getARRAY().push_back(value->getINTEGER());
                    }
                    if(value->which == 1){
                        if(value->getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);

                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value->getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setSTRING(value->getSTRING());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value->getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            if(value->getNAME() != ""){
                                // prepei na to valo epeidi einai object

                                this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            }else{
                                this->headOFdata[i].headOFdata[j].setSTRING(value->name);
                                this->headOFdata[i].headOFdata[j].setWHICH(value->which);
                            }
                        }
                    }else if(value->which == 2){
                        if(value->getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value->getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value->getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value->getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].setINTEGER(value->integer);
                            this->headOFdata[i].headOFdata[j].setWHICH(value->which);
                        }
                    }else if(value->which == 3){
                        if(value->getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value->getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value->getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value->getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].setINTEGER(value->integer);
                            this->headOFdata[i].headOFdata[j].setWHICH(value->which);
                        }
                    }else if(value->which == 4){
                        if(value->getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value->getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value->getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setBOOLEAN(value->getBOOLEAN());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].setBOOLEAN(value->boolean);
                            this->headOFdata[i].headOFdata[j].setWHICH(value->which);
                        }
                    }else if(value->which == 5){
                        for(int i = 0; i < this->headOFdata[i].headOFdata[j].getARRAY().size() ; i++){
                            if(this->headOFdata[i].headOFdata[j].array[i] == MAX_INT_JSON){
                                this->headOFdata[i].headOFdata[j].array[i] = value->integer;
                            }
                        }
                    }else if(value->which == 6 || value->which == 7){
                        if(value->getNAME() != ""){
                            // prepei na to valo epeidi einai object

                            this->headOFdata[i].headOFdata[j].headOFdata.push_back(value);
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setNAME(value->getNAME());
                            this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setINTEGER(value->getINTEGER());this->headOFdata[i].headOFdata[j].headOFdata[this->headOFdata[i].headOFdata[j].headOFdata.size()-1].setWHICH(value->getWHICH());
                            this->headOFdata[i].headOFdata[j].setWHICH(6);

                        }else{
                            this->headOFdata[i].headOFdata[j].addHEADOFDATA(value);
                            this->headOFdata[i].headOFdata[j].setWHICH(value->which);
                        }
                    }else{
                        cout << "which = " << which << endl;
                    }
                    this->headOFdata.pop_back();
                    cleanFROMflags(*this);
                    return *this;
                }
            }
        }
        if(this->getINTEGER() != MAX_INT_JSON && value->getINTEGER() != MAX_INT_JSON){
            this->getARRAY().push_back(this->getINTEGER());
            this->getARRAY().push_back(value->getINTEGER());
        }
        if(value->which == 1){
            this->setSTRING(value->name);
            this->setWHICH(value->which);
        }else if(value->which == 2){
            this->setINTEGER(value->integer);
            this->setWHICH(value->which);
        }else if(value->which == 3){
            this->setINTEGER(value->integer);
            this->setWHICH(value->which);
        }else if(value->which == 4){
            this->setBOOLEAN(value->boolean);
            this->setWHICH(value->which);
        }else if(value->which == 6){
            this->addHEADOFDATA(value);
            this->setWHICH(value->which);
        }else if(value->which == 7){
            this->addHEADOFDATA(value);
            this->setWHICH(6);
        }else if(value->which == 5){
            for(int i = 0; i < this->getARRAY().size() ; i++){
                if(this->array[i] == MAX_INT_JSON){
                    this->array[i] = value->integer;
                }
            }
        }else{
            cout << "which = " << which << endl;
        }

        cleanFROMflags(*this);
        return *this;
    }

    myType operator/=( myType &value ){ printerino(value, this) // ERASE

        myType tmp;

        if(value.deleteMe == true){ //Whole Erase
            value.clear();
        }else{ //Searching for flag

            for(int i = 0; i < value.headOFdata.size() ; i++ ){
                if(value.headOFdata[i].willgeterased == true){

                    value.headOFdata[i].clear();
                    cleanFROMflags(value);
                    return *this;

                }
                tmp /= value.headOFdata[i];
            }
        }

        cleanFROMflags(value);
        //cleanFROMflags(*this);
        return *this;

    }
    myType operator/=( myType *value ){ printerino(value, this)//ERASE

        myType tmp;

        if(value->willgeterased == true){ //Whole Erase
            value->clear();
        }else{ //Searching

            for(int i = 0; i < value->headOFdata.size() ; i++ ){
                if(value->headOFdata[i].willgeterased == true){

                    value->headOFdata[i].clear();
                    cleanFROMflags(*value);
                    return *this;

                }
                tmp /= value->headOFdata[i];
            }
        }

        cleanFROMflags(*value);
        //cleanFROMflags(*this);
        return *this;
    
    }

    //OPERATORS USED FOR ARITHMETIC CALCULATIONS
    myType &operator+( myType value ){ printerino(value, this)

        if(this->getNAME() != "" && this->getSTRING() != ""){ //objects of one variable

            myType created;

            if(this->getWHICH() == 1 && this->getSTRING() != ""){ //strings
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if(this->getWHICH() == 2 && this->getINTEGER() != MAX_INT_JSON){ //integer
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if(this->getWHICH() == 3 && this->getINTEGER() != MAX_INT_JSON){ //integer
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if(this->getWHICH() == 5 && !this->getARRAY().empty()){ //array
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if((this->getWHICH() == 6 || this->getWHICH() == 7) && !this->getHEAD().empty()){ //object array
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }

            return *this;

        }else if(this->getWHICH() == 1 && value.getWHICH() == 1){ //strings
            this->setSTRING(this->getNAME() + value.getNAME());
            this->setNAME(this->getNAME() + value.getNAME());
        }else if(this->getWHICH() == 2 && value.getWHICH() == 2){ //numbers
            this->setINTEGER(this->getINTEGER() + value.getINTEGER());
        }else if(this->getWHICH() == 4 && value.getWHICH() == 4){ //boolean
            this->setBOOLEAN(this->getBOOLEAN() + value.getBOOLEAN());
        }else if(this->getWHICH() == 5 && value.getWHICH() == 5){ //arrays

            for(int i = 0; i < value.getARRAY().size() ; i++){
                this->array.push_back(value.getARRAY()[i]);
            }

        }else if(this->getWHICH() == 6 && value.getWHICH() == 6){
            for(int i = 0; i < value.getHEAD().size() ; i++){
                this->addHEADOFDATA(value.getHEAD()[i]);
            }
        }else if(this->getWHICH() == 7 && value.getWHICH() == 7){

            for(int i = 0; i < value.getHEAD().size() ; i++){
                this->addHEADOFDATA(value.getHEAD()[i]);
            }

        }

        return *this;

    }
    myType &operator+( myType *value ){ printerino(value, this)

        if(this->getNAME() != "" && this->getSTRING() != ""){ //objects of one variable

            myType created;

            if(this->getWHICH() == 1 && this->getSTRING() != ""){ //strings
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if(this->getWHICH() == 2 && this->getINTEGER() != MAX_INT_JSON){ //integer
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if(this->getWHICH() == 3 && this->getINTEGER() != MAX_INT_JSON){ //integer
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if(this->getWHICH() == 5 && !this->getARRAY().empty()){//array of ints
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }else if((this->getWHICH() == 6 || this->getWHICH() == 7) && !this->getHEAD().empty()){ //array of objects
                created.addHEADOFDATA(*this);
                this->clear();
                this->addHEADOFDATA(created.getHEAD()[0]);
                this->addHEADOFDATA(value);
                this->setWHICH(6);
            }

            return *this;

        }else if(this->getWHICH() == 1 && value->getWHICH() == 1){ //strings
            this->setSTRING(this->getNAME() + value->getNAME());
            this->setNAME(this->getNAME() + value->getNAME());
        }else if(this->getWHICH() == 2 && value->getWHICH() == 2){ //numbers
            this->setINTEGER(this->getINTEGER() + value->getINTEGER());
        }else if(this->getWHICH() == 4 && value->getWHICH() == 4){ //boolean
            this->setBOOLEAN(this->getBOOLEAN() + value->getBOOLEAN());
        }else if(this->getWHICH() == 5 && value->getWHICH() == 5){ //arrays

            for(int i = 0; i < value->getARRAY().size() ; i++){
                this->array.push_back(value->getARRAY()[i]);
            }

        }else if(this->getWHICH() == 6 && value->getWHICH() == 6){
            for(int i = 0; i < value->getHEAD().size() ; i++){
                this->addHEADOFDATA(value->getHEAD()[i]);
            }
        }else if(this->getWHICH() == 7 && value->getWHICH() == 7){
            for(int i = 0; i < value->getHEAD().size() ; i++){
                this->addHEADOFDATA(value->getHEAD()[i]);
            }
        }

        return *this;
  
    }

    myType &operator-( myType value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER(this->getINTEGER() - value.getINTEGER());
        }

        return *this;
   
    }
    myType &operator-( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER(this->getINTEGER() - value->getINTEGER());
        }

        return *this;
   
    }

    myType &operator*( myType value ){ printerino(value, this)

       if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
          (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER(this->getINTEGER() * value.getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER(this->headOFdata[i].integer * value.integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }
    myType &operator*( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER(this->getINTEGER() * value->getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER(this->headOFdata[i].integer * value->integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }

    myType &operator/( myType value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER(this->getINTEGER() / value.getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER(this->headOFdata[i].integer / value.integer);
                    return *returner;
                }
            }
        }

        return *this;
   
    }
    myType &operator/( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER(this->getINTEGER() / value->getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER(this->headOFdata[i].integer / value->integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }

    myType &operator%( myType value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() % (int) value.getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer % (int) value.integer);
                    return *returner;
                }
            }
        }

        return *this;

    }
    myType &operator%( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() % (int) value->getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer % (int) value->integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }

    myType &operator>( myType value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() > (int) value.getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer > (int) value.integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }
    myType &operator>( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() > (int) value->getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer > (int) value->integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }

    myType &operator>=( myType value ){ printerino(value, this);

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() >= (int) value.getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer >= (int) value.integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }
    myType &operator>=( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() >= (int) value->getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer >= (int) value->integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }

    myType &operator<( myType value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() < (int) value.getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer < (int) value.integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }
    myType &operator<( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() < (int) value->getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer < (int) value->integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }

    myType &operator<=( myType value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() <= (int) value.getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer <= (int) value.integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }
    myType &operator<=( myType *value ){ printerino(value, this)

        if((this->getWHICH() == 2 || this->getWHICH() == 3) &&
           (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers
            this->setINTEGER((int) this->getINTEGER() <= (int) value->getINTEGER());
        }else{
            for(int i = 0; i < this->headOFdata.size() ; i++ ){
                if(this->headOFdata[i].willgeterased == true){
                    this->headOFdata[i].willgeterased = false;
                    myType *returner = new myType(5);
                    returner->setINTEGER((int) this->headOFdata[i].integer <= (int) value->integer);
                    return *returner;
                }
            }
        }

        return *this;
    
    }

    myType operator&&( myType value ){ printerino(value, this)

        if(this->getWHICH() == 4 && value.getWHICH() == 4){ //boolean
            if(this->getBOOLEAN() && value.getBOOLEAN()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    }
    myType operator&&( myType *value ){ printerino(value, this)

        if(this->getWHICH() == 4 && value->getWHICH() == 4){ //boolean
            if(this->getBOOLEAN() || value->getBOOLEAN()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    }

    myType operator||( myType value ){ printerino(value, this)

        if(this->getWHICH() == 4 && value.getWHICH() == 4){//boolean
            if(this->getBOOLEAN() || value.getBOOLEAN()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    }
    myType operator||( myType *value ){ printerino(value, this)

        if(this->getWHICH() == 4 && value->getWHICH() == 4){ //boolean
            if(this->getBOOLEAN() || value->getBOOLEAN()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    }

    myType operator!(  ){ printerino("EMPTY", this)

        if(this->getWHICH() == 4){ //boolean
            return !this->getBOOLEAN();
        }
        return false;

    }
    
    const bool &operator==( myType value ){ printerino(value, this)

        if(this->getNAME() != ""){ //objects of one variable

            myType created;

            if(this->getWHICH() == 1 && this->getSTRING() != ""){ //strings
                if(this->getNAME() == value.getNAME()){
                    if(this->getSTRING() == value.getSTRING()){
                        return tr;
                    }
                }
                return fl;
            }else if(this->getWHICH() == 2 && this->getINTEGER() != MAX_INT_JSON){ //number
                if(this->getNAME() == value.getNAME()){
                    if(this->getINTEGER() == value.getINTEGER()){
                        return tr;
                    }
                }
                return fl;
            }else if(this->getWHICH() == 3 && this->getINTEGER() != MAX_INT_JSON){ //number
                if(this->getNAME() == value.getNAME()){
                    if(this->getINTEGER() == value.getINTEGER()){
                        return tr;
                    }
                }
                return fl;
            }else if(this->getWHICH() == 5 && !this->getARRAY().empty()){ //array of ints
                if(this->array.size() == value.array.size()){
                    for(int i = 0; i < value.array.size() ; i++){
                        if(this->array[i] != value.array[i]){
                            return fl;
                        }
                    }
                    return tr;
                }else{
                    return fl;
                }
            }else if((this->getWHICH() == 6 || this->getWHICH() == 7) &&
                     !this->getHEAD().empty()){ // array of objects
                if(this->getHEAD().size() == value.getHEAD().size()){
                    for(int i = 0; i < value.getHEAD().size() ; i++){
                        if(this->getHEAD()[i] != value.getHEAD()[i]){
                            return fl;
                        }
                    }
                    return tr;
                }else{
                    return fl;
                }
            }

            return fl;

        }else if(this->getWHICH() == 1 && value.getWHICH() == 1){ //

            if(this->getNAME() == value.getNAME()){
                if(this->getSTRING() == value.getSTRING()){
                    return tr;
                }
            }
            return fl;

        }else if((this->getWHICH() == 2 || this->getWHICH() == 3)
                 && (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers

            if(this->getNAME() == value.getNAME()){
                if(this->getINTEGER() == value.getINTEGER()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 4 && value.getWHICH() == 4){ //boolean

            if(this->getNAME() == value.getNAME()){
                if(this->getBOOLEAN() == value.getBOOLEAN()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 5 && value.getWHICH() == 5){ //arrays

            if(this->array.size() == value.array.size()){
                for(int i = 0; i < value.array.size() ; i++){
                    if(this->array[i] != value.array[i]){
                        return fl;
                    }
                }
                return tr;
            }else{
                return fl;
            }

        }else if(this->getWHICH() == 6 && value.getWHICH() == 6){
            if(this->getHEAD().size() == value.getHEAD().size()){
                for(int i = 0; i < value.getHEAD().size() ; i++){
                    if(this->getHEAD()[i] != value.getHEAD()[i]){
                        return fl;
                    }
                }
                return tr;
            }else{
                return fl;
            }
        }else if(this->getWHICH() == 7 && value.getWHICH() == 7){
            if(this->getHEAD().size() == value.getHEAD().size()){
                for(int i = 0; i < value.getHEAD().size() ; i++){
                    if(this->getHEAD()[i] != value.getHEAD()[i]){
                        return fl;
                    }
                }
                return tr;
            }else{
                return fl;
            }
        }else{
            cout << "the values are diffrent" << endl;
            return fl;
        }

    }
    const bool &operator==( myType *value ){ printerino(value, this)

        if(this->getNAME() != ""){ //objects of one variable

            myType created;

            if(this->getWHICH() == 1 && this->getSTRING() != ""){ //strings
                if(this->getNAME() == value->getNAME()){
                    if(this->getSTRING() == value->getSTRING()){
                        return tr;
                    }
                }
                return fl;
            }else if(this->getWHICH() == 2 && this->getINTEGER() != MAX_INT_JSON){ //numbers
                if(this->getNAME() == value->getNAME()){
                    if(this->getINTEGER() == value->getINTEGER()){
                        return tr;
                    }
                }
                return fl;
            }else if(this->getWHICH() == 3 && this->getINTEGER() != MAX_INT_JSON){ //numbers
                if(this->getNAME() == value->getNAME()){
                    if(this->getINTEGER() == value->getINTEGER()){
                        return tr;
                    }
                }
                return fl;
            }else if(this->getWHICH() == 5 && !this->getARRAY().empty()){ //array if ints
                if(this->array.size() == value->array.size()){
                    for(int i = 0; i < value->array.size() ; i++){
                        if(this->array[i] != value->array[i]){
                            return fl;
                        }
                    }
                    return tr;
                }else{
                    return fl;
                }
            }else if((this->getWHICH() == 6 || this->getWHICH() == 7)
                     && !this->getHEAD().empty()){ // array of objects
                if(this->getHEAD().size() == value->getHEAD().size()){
                    for(int i = 0; i < value->getHEAD().size() ; i++){
                        if(this->getHEAD()[i] != value->getHEAD()[i]){
                            return fl;
                        }
                    }
                    return tr;
                }else{
                    return fl;
                }
            }

            return fl;

        }else if(this->getWHICH() == 1 && value->getWHICH() == 1){ //

            if(this->getNAME() == value->getNAME()){
                if(this->getSTRING() == value->getSTRING()){
                    return tr;
                }
            }
            return fl;

        }else if((this->getWHICH() == 2 || this->getWHICH() == 3)
                 && (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers

            if(this->getNAME() == value->getNAME()){
                if(this->getINTEGER() == value->getINTEGER()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 4 && value->getWHICH() == 4){ //boolean

            if(this->getNAME() == value->getNAME()){
                if(this->getBOOLEAN() == value->getBOOLEAN()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 5 && value->getWHICH() == 5){ //arrays

            if(this->array.size() == value->array.size()){
                for(int i = 0; i < value->array.size() ; i++){
                    if(this->array[i] != value->array[i]){
                        return fl;
                    }
                }
                return tr;
            }else{
                return fl;
            }

        }else if(this->getWHICH() == 6 && value->getWHICH() == 6){
            if(this->getHEAD().size() == value->getHEAD().size()){
                for(int i = 0; i < value->getHEAD().size() ; i++){
                    if(this->getHEAD()[i] != value->getHEAD()[i]){
                        return fl;
                    }
                }
                return tr;
            }else{
                return fl;
            }
        }else if(this->getWHICH() == 7 && value->getWHICH() == 7){
            if(this->getHEAD().size() == value->getHEAD().size()){
                for(int i = 0; i < value->getHEAD().size() ; i++){
                    if(this->getHEAD()[i] != value->getHEAD()[i]){
                        return fl;
                    }
                }
                return tr;
            }else{
                return fl;
            }
        }else{
            cout << "the values are diffrent" << endl;
            return fl;
        }

    }

    const bool &operator!=( myType value ){ printerino(value, this)

        if(this->getNAME() != ""){ //objects of one variable

            myType created;

            if(this->getWHICH() == 1 && this->getSTRING() != ""){  //strings
                if(this->getNAME() == value.getNAME()){
                    if(this->getSTRING() == value.getSTRING()){
                        return fl;
                    }
                }
                return tr;
            }else if(this->getWHICH() == 2 && this->getINTEGER() != MAX_INT_JSON){ //integers
                if(this->getNAME() == value.getNAME()){
                    if(this->getINTEGER() == value.getINTEGER()){
                        return fl;
                    }
                }
                return tr;
            }else if(this->getWHICH() == 3 && this->getINTEGER() != MAX_INT_JSON){ //integers
                if(this->getNAME() == value.getNAME()){
                    if(this->getINTEGER() == value.getINTEGER()){
                        return fl;
                    }
                }
                return tr;
            }else if(this->getWHICH() == 5 && !this->getARRAY().empty()){ //array of ints
                if(this->array.size() == value.array.size()){
                    for(int i = 0; i < value.array.size() ; i++){
                        if(this->array[i] != value.array[i]){
                            return tr;
                        }
                    }
                    return fl;
                }else{
                    return tr;
                }
            }else if((this->getWHICH() == 6 || this->getWHICH() == 7) &&
                     !this->getHEAD().empty()){ // array of objects
                if(this->getHEAD().size() == value.getHEAD().size()){
                    for(int i = 0; i < value.getHEAD().size() ; i++){
                        if(this->getHEAD()[i] != value.getHEAD()[i]){
                            return tr;
                        }
                    }
                    return fl;
                }else{
                    return tr;
                }
            }

            return fl;

        }else if(this->getWHICH() == 1 && value.getWHICH() == 1){ //strings

            if(this->getNAME() != value.getNAME()){
                if(this->getSTRING() != value.getSTRING()){
                    return tr;
                }
            }
            return fl;

        }else if((this->getWHICH() == 2 || this->getWHICH() == 3)
                 && (value.getWHICH() == 2 || value.getWHICH() == 3)){ //numbers

            if(this->getNAME() == value.getNAME()){
                if(this->getINTEGER() == value.getINTEGER()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 4 && value.getWHICH() == 4){ //boolean

            if(this->getNAME() == value.getNAME()){
                if(this->getBOOLEAN() == value.getBOOLEAN()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 5 && value.getWHICH() == 5){ //arrays

            if(this->array.size() == value.array.size()){
                for(int i = 0; i < value.array.size() ; i++){
                    if(this->array[i] != value.array[i]){
                        return tr;
                    }
                }
                return fl;
            }else{
                return tr;
            }

        }else if(this->getWHICH() == 6 && value.getWHICH() == 6){
            if(this->getHEAD().size() == value.getHEAD().size()){
                for(int i = 0; i < value.getHEAD().size() ; i++){
                    if(this->getHEAD()[i] == value.getHEAD()[i]){
                        return tr;
                    }
                }
                return fl;
            }else{
                return tr;
            }
        }else if(this->getWHICH() == 7 && value.getWHICH() == 7){
            if(this->getHEAD().size() == value.getHEAD().size()){
                for(int i = 0; i < value.getHEAD().size() ; i++){
                    if(this->getHEAD()[i] == value.getHEAD()[i]){
                        return tr;
                    }
                }
                return fl;
            }else{
                return tr;
            }
        }else{
            cout << "the values are diffrent" << endl;
            return fl;
        }

    }
    const bool &operator!=( myType *value ){ printerino(value, this)

        if(this->getNAME() != ""){ //objects of one variable

            myType created;

            if(this->getWHICH() == 1 && this->getSTRING() != ""){ //strings
                if(this->getNAME() == value->getNAME()){
                    if(this->getSTRING() == value->getSTRING()){
                        return fl;
                    }
                }
                return tr;
            }else if(this->getWHICH() == 2 && this->getINTEGER() != MAX_INT_JSON){ //integers
                if(this->getNAME() == value->getNAME()){
                    if(this->getINTEGER() == value->getINTEGER()){
                        return fl;
                    }
                }
                return tr;
            }else if(this->getWHICH() == 3 && this->getINTEGER() != MAX_INT_JSON){ //integers
                if(this->getNAME() == value->getNAME()){
                    if(this->getINTEGER() == value->getINTEGER()){
                        return fl;
                    }
                }
                return tr;
            }else if(this->getWHICH() == 5 && !this->getARRAY().empty()){ //array of ints
                if(this->array.size() == value->array.size()){
                    for(int i = 0; i < value->array.size() ; i++){
                        if(this->array[i] != value->array[i]){
                            return tr;
                        }
                    }
                    return fl;
                }else{
                    return tr;
                }
            }else if((this->getWHICH() == 6 || this->getWHICH() == 7) &&
                     !this->getHEAD().empty()){ // array of objects
                if(this->getHEAD().size() == value->getHEAD().size()){
                    for(int i = 0; i < value->getHEAD().size() ; i++){
                        if(this->getHEAD()[i] != value->getHEAD()[i]){
                            return tr;
                        }
                    }
                    return fl;
                }else{
                    return tr;
                }
            }

            return fl;

        }else if(this->getWHICH() == 1 && value->getWHICH() == 1){ //strings

            if(this->getNAME() != value->getNAME()){
                if(this->getSTRING() != value->getSTRING()){
                    return tr;
                }
            }
            return fl;

        }else if((this->getWHICH() == 2 || this->getWHICH() == 3)
                 && (value->getWHICH() == 2 || value->getWHICH() == 3)){ //numbers

            if(this->getNAME() == value->getNAME()){
                if(this->getINTEGER() == value->getINTEGER()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 4 && value->getWHICH() == 4){ // boolean

            if(this->getNAME() == value->getNAME()){
                if(this->getBOOLEAN() == value->getBOOLEAN()){
                    return tr;
                }
            }
            return fl;

        }else if(this->getWHICH() == 5 && value->getWHICH() == 5){ // array of integers

            if(this->array.size() == value->array.size()){
                for(int i = 0; i < value->array.size() ; i++){
                    if(this->array[i] != value->array[i]){
                        return tr;
                    }
                }
                return fl;
            }else{
                return tr;
            }

        }else if(this->getWHICH() == 6 && value->getWHICH() == 6){ // array of objects
            if(this->getHEAD().size() == value->getHEAD().size()){
                for(int i = 0; i < value->getHEAD().size() ; i++){
                    if(this->getHEAD()[i] == value->getHEAD()[i]){
                        return tr;
                    }
                }
                return fl;
            }else{
                return tr;
            }
        }else if(this->getWHICH() == 7 && value->getWHICH() == 7){ // array of objects
            if(this->getHEAD().size() == value->getHEAD().size()){
                for(int i = 0; i < value->getHEAD().size() ; i++){
                    if(this->getHEAD()[i] == value->getHEAD()[i]){
                        return tr;
                    }
                }
                return fl;
            }else{
                return tr;
            }
        }else{
            cout << "the values are diffrent" << endl;
            return fl;
        }

    }

    /* functions */
    void edit(myType &value, myType &input){

        if(input.getINTEGER() != MAX_INT_JSON && value.getINTEGER() != MAX_INT_JSON){
            value.getARRAY().push_back(value.getINTEGER());
            value.getARRAY().push_back(input.getINTEGER());
            return;
        }
        if(value.which == 8){
            value.addHEADOFDATA(input);
            value.setWHICH(7);
            return;
        }
        if(input.which == 1){
            value.setSTRING(input.name);
            value.setWHICH(input.which);
        }else if(input.which == 2){
            value.setINTEGER(input.integer);
            value.setWHICH(input.which);
        }else if(input.which == 3){
            value.setINTEGER(input.integer);
            value.setWHICH(input.which);
        }else if(input.which == 4){
            value.setBOOLEAN(input.boolean);
            value.setWHICH(input.which);
        }else if(input.which == 5){
            for(int i = 0; i < this->getARRAY().size() ; i++){
                if(value.array[i] == MAX_INT_JSON){
                    value.array[i] = input.integer;
                }
            }
        }else if(input.which == 6 || input.which == 7){
            value.addHEADOFDATA(input);
            value.setWHICH(input.which);
        }

    }
    void cleanFROMflags(myType &value){

        value.isMember = false;
        value.hidden = false;
        value.edited = false;
        value.willgeterased = false;
        value.deleteMe = true;

        for ( int i = 0 ; i < value.headOFdata.size() ; i++){
            cleanFROMflags(value.headOFdata[i]);
        }
    
    }

    int SIZE_OF_ME(){

        if(this->which == 5){
            return (int) this->array.size();
        }else if(this->which == 6 || this->which == 7){
            return (int) this->headOFdata.size();
        }else{
            return false;
        }
   
    }
    bool IS_EMPTY_ME(){
        if(this->which == 5){
            if(this->array.size() == 0){
                return true;
            }else{
                return false;
            }
        }else if(this->which == 6 || this->which == 7){
            if(this->headOFdata.size() == 0){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
 
    }
    bool HAS_KEY_ME(string key){

        if(this->name == key){
            return true;
        }else{
            for(int i = 0; i < this->headOFdata.size(); i++){

                if(this->headOFdata[i].name == key){
                    return true;
                }else{

                    if(this->headOFdata[i].which == 6 || this->headOFdata[i].which == 7){

                        for(int j = 0; j < this->headOFdata[i].headOFdata.size(); j++){

                            if( this->headOFdata[i].headOFdata[j].HAS_KEY_ME(key) ){
                                return this->headOFdata[i].headOFdata[j].HAS_KEY_ME(key);
                            }

                        }
                    }
                }
            }
        }
        return false;

    }
    string TYPE_OF_ME(){

        if(this->which == 1){
            return "string";
        }else if(this->which == 2 || this->which == 3){
            return "number";
        }else if(this->which == 4){
            return "boolean";
        }else if(this->which == 5){
            return "array";
        }else if(this->which == 6 || this->which == 7){
            return "object";
        }else{
            return "NULL";
        }

    }

        /* getCALLS */
    string getNAME(){
        return(this->name);
    }
    string getSTRING(){
        return(this->str);
    }
    float getINTEGER(){
        return(this->integer);
    }
    bool getBOOLEAN(){
        return(this->boolean);
    }
    int getWHICH(){
        return this->which;
    }
    int getMEMBER(){
        return this->isMember;
    }
    vector<float> getARRAY(){
        return this->array;
    }
    vector<myType> getHEAD(){
        return this->headOFdata;
    }

    /* setCALLS */
    void setNAME(string const Name){
        this->name = Name;
    }
    void setSTRING(string const String){
        this->str = String;
    }
    void setINTEGER(float const Integer){
        this->integer = Integer;
    }
    void setBOOLEAN(bool const Boolean){
        this->boolean = Boolean;
    }
    void setWHICH(int Which){
        this->which = Which;
    }
    void setMEMBER(bool Member){
        this->isMember = Member;
    }
    void setARRAY(vector<float> Array){
        array = Array;
    }
    void addHEADOFDATA(myType data){
        this->headOFdata.push_back(data);
    }
    void addHEADOFDATA(myType *data){
        this->headOFdata.push_back(data);
    }

    /* clearCALLS */
    void clearHEAD(){
        this->headOFdata.clear();
    }
    void clearARRAY(){
        this->array.clear();
    }
    void clear(){

        this->setNAME("");
        this->setSTRING("");
        this->setINTEGER(MAX_INT_JSON);
        this->setBOOLEAN(false);
        this->clearHEAD();
        this->clearARRAY();
        this->setWHICH(MAX_INT_JSON);

        isMember = false;
        hidden = false;
        edited = false;
        willgeterased = false;
        deleteMe = true;

    }

    /* isEMPTY */
    bool isALLempty(){
        if(this->getNAME() == ""){
            if(this->getSTRING() == ""){
                if(this->getINTEGER() == MAX_INT_JSON){
                    if(this->isARRAYempty()){
                        if(this->headOFdata.size() == 0){
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    
    }
    bool isARRAYempty(){
        if(this->getARRAY().size() == 0){
            return true;
        }else{
            return false;
        }
    
    }

private:

    int which           = MAX_INT_JSON;

    vector<myType>      headOFdata;
    vector<float>       array;

    string name         = "";
    string str          = "";
    float integer       = MAX_INT_JSON;
    bool boolean;

    bool isMember       = false;
    bool hidden         = false;
    bool edited         = false;
    bool willgeterased  = false;
    bool deleteMe       = true;
    bool isMeme         = false;
    int place           = -1;

};

#endif /* JSONlang_h */
