#include "Person.h"
#include "FileReader.h"
#include "Utility.h"

int main(){
    //open file and read contents to static array
    FileReader* fr = new FileReader("users.txt");
    fr->inputArray();

    //user choice initialised in heap
    int* input= new int(0);
    while (true){
        //print menu and get user input
        std::cout<<"Please select a number option: " <<std::endl;
        std::cout<<"1-Login"<<std::endl;
        std::cout<<"2-Register"<<std::endl;
        std::cin>>*input;
        std::cin.ignore(); //flush cin

         //in case of login  
        if(*input==1){
            //get user name and pw
            std::string username,pw;
            char* pwArr = new char[11];
            std::cout<<"enter username and pw"<<std::endl;
            std::getline(std::cin,username);
            std::cin>>pw;
            //error check and write entered pw string to char array so it can be passed into hash function
            if(pw.size()>10)
                std::cout<<"Password is too long to be valid.";
            else{
                 for(int i=0;i<pw.size();i++){
                    pwArr[i]=pw.at(i);
                 }
                //fill the empty places with 0
                for(int i=pw.size();i<11;i++){
                    if(i==10){
                        pwArr[i]='\0';
                    }
                    else{
                        pwArr[i]=0;
                    }
                }
                int hash = Utility::RSHash(pwArr,10);
                delete pwArr; //free memory
                std::string strHash = std::to_string(hash);
                int foundResult = fr->findMatch(username,strHash);
                if(foundResult>=0){ //creates and prints a person obj if matching credentials found
                    Person p = Person::extractPeople(FileReader::people.at(foundResult));
                    std::cout<<p;
                }
                else{
                    std::cout<<"No match found for username and password."<<std::endl;
                }
                
            }
        }
        //in case of register
        else if(*input==2){
            //open file again with output stream, create a new person and write variables to them, then write to the file.
            std::ofstream out;
            out.open("users.txt",std::ios_base::app); 
            Person *p = new Person();
            std::cin>>*p;
            std::cout<<*p<<std::endl;
            p->serialize(out);
            delete p; //free memory
            out.close(); //close the output filestream
            //open the file reader ifstream to update the people array, read updated file contents into static array.
            fr = new FileReader("users.txt");
            fr->inputArray();
            
        
        }
        else{
            std::cout<<"invalid option"<<std::endl;
        }


    }

    delete input; //free mem for input

    
    return 0;
}
