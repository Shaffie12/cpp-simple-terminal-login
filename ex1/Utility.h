//class for static or program related methods
#ifndef _UTILITY_H_
#define _UTILITY_H_
#include<string>
#include <cstring>
#include <iostream>

//class to do program operations that dont fit into other classes.
class Utility{

    private:

    public:
        //check if username and password matches with those from file
        static bool authUser(std::string userName, std::string pw, std::string nameFromTxt, std::string pwFromTxt);
        //hash function as provided in brief
        static unsigned int RSHash(const char* str, unsigned int length);





};

#endif