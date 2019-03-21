//
//  main.cpp
//  JSON IN C++ (PROJECT) HY352
//
//  Created by Ioannis Tsiakkas on 12/5/16.
//  Copyright © 2016 Ioannis Tsiakkas. All rights reserved.
//
#include "json_library.h"

PROGRAM_BEGIN
PROGRAM_BEGIN_PRINT

//define emptyObj json with empty OBJECT
JSON(emptyObj) = OBJECT{}
//define emptyArray json with empty array
JSON(emptyArray) = ARRAY
//define book json with an OBJECT containing data for a book
JSON(book) = OBJECT {
    KEY(title) : STRING("Gone Girl"),
    KEY(published) : NUMBER(2012),
    KEY(type) : STRING("Thriller"),
    KEY(author) : OBJECT{
        KEY(firstname) : STRING("GILLIAN"),
        KEY(sirname) : STRING("FLYNN"),
        KEY(age) : NUMBER(45)
    }
}
//define week_temperatures json with an array of numbers
JSON(week_temperatures) = ARRAY [
    NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
    NUMBER(19), NUMBER(18.5), NUMBER(19)
]
//define students json with an array of OBJECTs representing students
JSON(students) = ARRAY [
    OBJECT{
        KEY(name)   : STRING("Nikos Nikolaou"),
        KEY(id)     : NUMBER(4444),
        KEY(grades) : ARRAY[
            OBJECT { KEY(hy100) : NUMBER(7.5) },
            OBJECT { KEY(hy150) : NUMBER(8) }
        ]
    },
    OBJECT{
    KEY(name)   : STRING("Ioannis Tsiakkas"),
    KEY(csd)     : NUMBER(3213),
    KEY(grades) : ARRAY[
        OBJECT { KEY(hy225) : NUMBER(8) },
        OBJECT { KEY(hy352) : NUMBER(10) }
    ]
    }
]

// PRINTING ALL THE DATA
PRINT endl PRINT "emptyObj: "
PRINT emptyObj
PRINT endl PRINT "emptyArray: "
PRINT emptyArray
PRINT endl PRINT endl PRINT "book: " PRINT endl
PRINT book
PRINT endl PRINT "week_temperatures: "
PRINT week_temperatures
PRINT endl PRINT "students: " PRINT endl
PRINT students

//change 3rd day temperature from 19 to 22
SET week_temperatures[2] ASSIGN NUMBER(22)
//add email address for 1st student
SET students[0]["email"] ASSIGN STRING("csd444@csd.uoc.gr") //assign new OBJECT in emptyObj json
SET emptyObj ASSIGN OBJECT {
    KEY(a) : STRING("alpha")
}

PRINT endl PRINT "====================================================" PRINT endl

// PRINTING ALL THE DATA
PRINT endl PRINT "emptyObj: "
PRINT emptyObj
PRINT endl PRINT "week_temperatures: "
PRINT week_temperatures
PRINT endl PRINT "students: " PRINT endl
PRINT students PRINT endl
PRINT endl

//appends values 23, 22, 20 to the end of the temperature array
SET week_temperatures APPEND NUMBER(23), NUMBER(22), NUMBER(20)
//appends a grade for course hy255
SET students[0]["grades"] APPEND OBJECT { KEY(hy255) : NUMBER(9) }

PRINT endl PRINT "====================================================" PRINT endl

// PRINTING ALL THE DATA
PRINT endl PRINT "week_temperatures: "
PRINT week_temperatures
PRINT endl PRINT "students: " PRINT endl
PRINT students PRINT endl
PRINT endl PRINT "book: " PRINT endl
PRINT book
PRINT endl

ERASE book["author"]["age"] //removes age from author object of book
ERASE book["type"] //removes type of book

PRINT endl PRINT "====================================================" PRINT endl

PRINT endl PRINT endl PRINT "book: " PRINT endl
PRINT book
PRINT endl

ERASE book //removes all book data, now book is an empty object

PRINT endl PRINT "====================================================" PRINT endl

PRINT endl PRINT endl PRINT "book: " PRINT endl
PRINT book
PRINT endl

PRINT endl PRINT "====================================================" PRINT endl

JSON(hy352_nik) = OBJECT{ KEY(exam):NUMBER(7), KEY(project):NUMBER(8) }

JSON(newstudents) = ARRAY [
    OBJECT{
        KEY(name) : STRING("Nikos ") + STRING("Nikolaou"),
        KEY(id) : NUMBER(4444),
        KEY(grades) : ARRAY[
            OBJECT {
                KEY(hy352): hy352_nik["exam"] * NUMBER(0.75) + hy352_nik["project"] * NUMBER(0.25),
                KEY(hy352): hy352_nik["exam"] * NUMBER(30) + hy352_nik["project"] * NUMBER(1.98)
            }
        ]
    }
]
                        
PRINT endl PRINT "newstudents: " PRINT endl
PRINT newstudents
PRINT endl

PRINT endl PRINT "====================================================" PRINT endl PRINT endl

PRINT "newstudents size is: " PRINT SIZE_OF(newstudents) PRINT endl
PRINT "is newstudents empty: " PRINT IS_EMPTY(newstudents) PRINT endl
PRINT "Does newstudents have value id: " PRINT HAS_KEY(newstudents, "id") PRINT endl
PRINT "Does newstudents have value surname: " PRINT HAS_KEY(newstudents, "surname") PRINT endl
PRINT "newstudents is of type: " PRINT TYPE_OF(newstudents) PRINT endl PRINT endl

JSON(newbook) = OBJECT {
    KEY(title) : STRING("Gone Girl"),
    KEY(published) : NUMBER(2012),
    KEY(type) : STRING("Thriller"),
    KEY(author) : OBJECT{
        KEY(firstname) : STRING("GILLIAN"),
        KEY(sirname) : STRING("FLYNN"),
        KEY(age) : NUMBER(45)
    }
}
//prints:Gone Girl
PRINT "title in newbook is: " PRINT newbook["title"]
//prints:{firstname:”Gillian”,sirname:“Flynn”,age: 45}
PRINT "author in newbook is: " PRINT newbook["author"]
//prints: the whole json for book
PRINT "whole newbook is: " PRINT endl PRINT newbook
//prints: Book has key author? True //prints: true
PRINT "Does newstudents have value author: " PRINT HAS_KEY(newbook, "author")
//Doesn't work and I dont think it can work with this way of data flow
//PRINT myType(tmp = "Book has key author? "), HAS_KEY(newbook, "author")
PRINT endl PRINT endl

JSON(WATER) = OBJECT {
    KEY(WATER) : TRUE
}
JSON(FIRE) = OBJECT {
    KEY(FIRE) : FALSE
}

PRINT WATER
PRINT FIRE

JSON(STEAM) = OBJECT {
    KEY(STEAM) : FIRE || WATER
}
PRINT STEAM

SET STEAM["STEAM"] ASSIGN FIRE && WATER
PRINT STEAM

SET STEAM["STEAM"] ASSIGN !FIRE
PRINT STEAM

SET STEAM["STEAM"] ASSIGN FIRE == WATER
PRINT "GAMO  = " PRINT STEAM

SET STEAM["STEAM"] ASSIGN week_temperatures == week_temperatures
PRINT "GAMO2 = " PRINT STEAM PRINT ", "
PRINT (week_temperatures == week_temperatures)

PRINT "STEAM IS OF TYPE: " PRINT TYPE_OF(STEAM) PRINT endl PRINT endl  

PROGRAM_END_PRINT
PROGRAM_END
/////////////////////////

