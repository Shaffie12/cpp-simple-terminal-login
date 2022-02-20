#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "FileReader.h"
#include <stdio.h>
#include <string.h>


//person class to hold info about person
class Person{
    private: 
        std::string name; //name of the person
        int age; //age of the person
        std::string place_of_birth; //where they were born
        char password[11]; //password of the person limited to 10chars, last one is \0
        int num_friends; //number of friends they have
        std::vector<std::string> friends; //list of friends names
     
    public:
        //make a person object from a string
        static Person extractPeople(std::string s);
        
        //getters (mostly for testing)
        std::string getName();
        int getAge();
        std::string getPob();
        char* getPassword(); 
        int getNum_Friends();
        std::vector<std::string> getFriendList();

        //constructors
        Person();
        Person(std::string name, int age, std::string pob, char pw[10],int num_friends,std::vector<std::string> &frns);

        //friend functions to print a person object and make a person from input stream
        friend std::ostream& operator<<(std::ostream& out,Person &p);
        friend std::istream& operator>>(std::istream& input,Person &p);
        
        //write a person object to a file
        void serialize(std::ostream & out);
    
       

};

#endif