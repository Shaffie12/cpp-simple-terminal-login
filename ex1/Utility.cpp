#include "Utility.h"

//evaluate if username and password match with what was entered
bool Utility::authUser(std::string userName, std::string pw, std::string nameFromTxt, std::string pwFromTxt){
    return userName==nameFromTxt && pw==pwFromTxt;
}

//hash as detailed in brief
unsigned int Utility::RSHash(const char* str, unsigned int length){
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i= 0;

    for (i=0;i<length;str++, i++){
        hash = hash *a +(*str);
        a=a*b;
    }

    return hash;
}

