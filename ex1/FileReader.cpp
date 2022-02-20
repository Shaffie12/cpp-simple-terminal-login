#include "FileReader.h"

//default initialisation for people array
std::vector<std::string> FileReader::people ={""};

//opens the ofstream with specified filename, exits program if file could not be opened.
FileReader::FileReader(const char*filename){
    file.open(filename);
    if(!file){
        std::cout<<"Could not open file "<<filename<<std::endl;
        exit(1);
    } 
}

//reads from the file while there are lines in the file, pushes each line into vector of strings, closes file.
void FileReader::inputArray(){
    std::string line;
    while(!file.eof()){
        std::getline(file,line);
        FileReader::people.push_back(line);
    }
    file.close();
}

//prints a vector of strings
void FileReader::print(std::vector<std::string> list){
    for(int i=0; i<list.size(); i++){
        std::cout<<"- "<< list.at(i) << std::endl;
    }
}

//finds number of delimiters in a string by looping through the string and check each char value
int FileReader::getDelims(std::string str){
    int delims =0;
    for(int i=0;i<str.length();i++){
        if (str.at(i)==','){
            delims++;
        }
    }
    return delims;
}

//gets the next string before a delimiter - define the delimiter to be used, and create substring from start of the string to where that delim was found.
//then erases start of string to where delim was found +1 (to include the delim)
std::string FileReader::getNextStr(std::string &delimedStr, char delim){
    char delimiter = delim;

    std::string data = delimedStr.substr(0,delimedStr.find(delimiter)); 
    delimedStr.erase(0,delimedStr.find(delimiter)+1);
    return data;
}

/*
    *takes a user entered username and password
    *initialises var to hold the row which match is found
    *loops through a copy of the people vector and records the row its on.
    *grabs username and password from vector by using delimiters
    *calls authUser which compares the usernames and passwords, if this passes then the row is returned as we know it was  a match.  If no match, returns -1
*/
int FileReader::findMatch(std::string name, std::string pw){
    int record;
    std::vector<std::string> peopleCopy = FileReader::people; //have to make a copy else original array from txt will be modified and other methods that use the array will not work.
    for(int i=1;i<peopleCopy.size();i++){
        record=i;
        std::string user_name = FileReader::getNextStr(peopleCopy.at(i),',');
        FileReader::getNextStr(peopleCopy.at(i),',');
        FileReader::getNextStr(peopleCopy.at(i),',');
        std::string pass=FileReader::getNextStr(peopleCopy.at(i),','); //use char arr instead??
        if(Utility::authUser(name, pw, user_name,pass)){
            return record;
        }
    }
    return -1;

}

//same as above but only needs a name
int FileReader::findMatch(std::string name){
    int record;
    std::vector<std::string> peopleCopy = FileReader::people;
    for(int i=0;i<peopleCopy.size();i++){
        record=i;
        std::string user_name = FileReader::getNextStr(peopleCopy[i],',');
        if(user_name==name){
            return record;
        }
    }
    return -1;

}



