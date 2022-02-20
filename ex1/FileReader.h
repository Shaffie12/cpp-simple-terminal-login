#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "Utility.h"

//to check if the file is readable and read its contents into a vector of strings

class FileReader{
   
    private:
        //filestream to read from file
        std::ifstream file;
     public:
        //static array holds the lines from the file, can be accessed from anywhere
        static std::vector<std::string> people; 

        //constructor
        FileReader(const char*filename);

        //reads file contents
        void inputArray();

        //static method to print a vector (mostly for testing)
        static void print(std::vector<std::string> list); 

        //returns how many delimiters(,) in a string
        static int getDelims(std::string); 

        //returns the text before the next delimiter in a string, also removes that text and the delimiter
        static std::string getNextStr(std::string &delimedStr, char delim);

        //returns the row in the people array at which a matching name and pw was found
        static int findMatch(std::string name, std::string pw);

        //same as above but returns where matching name was only
        static int findMatch(std::string name);

        //destructor
        ~FileReader();
     

};

#endif