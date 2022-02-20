#include "Person.h"

//default constructor
Person::Person(){};

//constructor takes all person members and initialises them
Person::Person(std::string name, int age, std::string pob, char pw[10],int num_friends,std::vector<std::string> &frns){
    this->name=name;
    this->age=age;
    this->place_of_birth=pob;
    for(int i=0;i<10;i++){
        this->password[i]=pw[i];
    }
    this->num_friends=num_friends;
    this->friends=frns;
};


//takes string argument (row from file) and creates person obj
Person Person::extractPeople(std::string s){
    //initialises variables in memory to store data extracted from the row
    std::string name,pob;
    int age,num_friends;
    char password[12];
    std::vector<std::string> list_of_friends;
    //grab data from the row using next string before delimiter
    name=FileReader::getNextStr(s,',');
    
    age = stoi(FileReader::getNextStr(s,','));
    
    pob = FileReader::getNextStr(s,',');
  
    strcpy(password,FileReader::getNextStr(s,',').c_str());

    //once first 4 pieces of information are taken out of the file, all that would be left is friends, if there are any.
    int delims=FileReader::getDelims(s);
    if(delims!=0){ //checks for amount of delimiters left, and begins loop to grab each friends name based on how many delimiters are left in string
        while(delims>0){
            std::string next= FileReader::getNextStr(s,',');
            list_of_friends.push_back(next);
            delims=FileReader::getDelims(s);
        }
        list_of_friends.push_back(s); //if no delimiters left then push the rest of the string into friend list (since there is no delimiter on the last friend).
        
    }
    num_friends=list_of_friends.size(); //get the number of friends based on size of the array we just pushed friend names into 
    
    Person p(name,age,pob,password,num_friends,list_of_friends);
    return p;
}


std::string Person::getName(){
    return this->name;
}

int Person::getAge(){
    return this->age;
}

std::string Person::getPob(){
    return this->place_of_birth;
}

char* Person::getPassword(){
    return this->password;
}

int Person::getNum_Friends(){
    return this->num_friends;
}

//getter (testing)
std::vector<std::string> Person::getFriendList(){
    return this->friends;
}

//ostream operator to print a person from the people array.
std::ostream& operator<<(std::ostream &out,Person &p){
    std::string friendsList;
    std::vector<std::string> peopleCopy = FileReader::people; //take a copy of the people array 
    for(int i=0;i<p.friends.size();i++){ //get the list of friends from the person passed as argument
        std::string aFriend = p.friends.at(i); //take 1 friend at a time and search for match in people array from file
        int rowFound =FileReader::findMatch(aFriend); 
        if(rowFound>=0){
            FileReader::getNextStr(peopleCopy.at(rowFound),',');
            std::string age = FileReader::getNextStr(peopleCopy.at(rowFound),',');
            std::string pob = FileReader::getNextStr(peopleCopy.at(rowFound),',');
            friendsList+="- "+aFriend+" "+age+" "+pob+"\n";
        } //if a row is found , this persons details will be added to a string which will be appended at the end and printed.
        else{
            friendsList+=aFriend+" "+ "NOT REGISTERED"+ "\n";
            
        }
        
    }

    return out <<std::endl
           << "Name: " << p.name<<std::endl
           << "Age: " << p.age <<std::endl 
           << "Born in: " <<p.place_of_birth <<std::endl
           << "Has " << p.num_friends << " friend(s), they are:" <<std::endl
           <<friendsList;
}

//get input from user and store in variables for person
std::istream& operator>>(std::istream &input, Person &p){
    int num_friends;
    std::string strPw;
    char pw [11];

    std::cout<<"Please enter name"<<std::endl;
    std::getline(input,p.name);

    std::cout<<"Please enter age"<<std::endl;
    while(true){
        input>> p.age;
        if(!input){ 
            std::cout<<"please enter a number"<<std::endl;
            input.clear();
            input.ignore();
            continue;
        }
        else {break;}
    }
    
    std::cout<<"Please enter place of birth"<<std::endl;
    input.ignore();
    std::getline(input,p.place_of_birth);
    
    std::cout<<"Please enter a password (max 10 characters)"<<std::endl;
    while(true){ //includes checks for the password size
        std::cin>>strPw;
        if(strPw.size()>10){
            std::cout<<"please enter only 10 characters"<<std::endl;
        }
        else{break;}
        
    }
    //to write into char arr loop through it and make sure the last char is \0.  if array is not full then make it full with 0, this ensures hash is always the same
    for(int i=0;i<strPw.size();i++){
        pw[i]=strPw.at(i);
    }
    
    for(int i=strPw.size();i<sizeof(pw);i++){
        pw[i]=0;
    }
    //password should now be whatever is entered and empty spaces filled with 0.
    int hash =Utility::RSHash(pw,10);
    strcpy(p.password,std::to_string(hash).c_str());

    std::cout<<"Please enter how my friends you have"<<std::endl;
    while(true){ //error checking
        input>>num_friends;
        if(!input){ 
            std::cout<<"please enter a number"<<std::endl;
            input.clear();
            input.ignore();
            continue;
        }
        else {break;}
    }
    
    p.num_friends=num_friends;
    input.ignore();
    std::cout<<"Please enter the names of your friends "<<std::endl;
    for(int i=0;i<num_friends;i++){
        std::string frn;
        std::getline(input,frn);
        p.friends.push_back(frn);
    }
    return input;

}

//write a person to the file in specific format
void Person::serialize(std::ostream & out){
    //writes in a single line with delimiters.  If the last piece of info in the row, no delimiter.  newline at end
    out <<this->name<<","<<this->age<<","<<this->place_of_birth<<","<<this->password;
    if(this->num_friends!=0){
        out<<",";
    }
    for(int i=0;i<this->num_friends;i++){
        if(i==num_friends-1){
            out<<this->friends.at(i);
        }
        else{out<<this->friends.at(i)<<",";}
    }
    out<<"\n";

}