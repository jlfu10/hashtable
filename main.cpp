#include <iostream>
#include <cstring>

//TO DO:
//implement hash table
//add to hash table
//print from hash table
//delete from hash table
//make and get (random) from file
//comments
using namespace std;
//void add()
//void delete()
//void print()
struct student{
  char firstname[20];
  char lastname[20]; 
  int id;
  float gpa; 
};
int main(){
  cout << "student list (again) (again). Commands: print, add, delete, quit" << endl;
  char in[80]; 
  //until the user quits, keep on running
  while(true){
    cout << "input a command: " << endl;
    cin >> in;
    if(strcmp(in,"print") == 0){
      //print
    }
    else if(strcmp(in, "add") == 0){
      //add
    }
    else if(strcmp(in, "delete") == 0){
      //delete
    }
    else if(strcmp(in, "quit") == 0){
      return 0;
    }
    else{
      cout << "unknown input, please try again." << endl;
    }
  }
  return 0; 
}
