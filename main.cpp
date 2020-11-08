#include <iostream>
#include <cstring>

using namespace std;

struct student{
  char firstname[20];
  char lastname[20]; 
  int id;
  float gpa; 
};
struct node{
  student* std;
  node* next; 
};
void add(int index, node** &table, student* newstudent);
void print(node** table, int n); 
int main(){
  cout << "student list (again) (again). Commands: print, add, delete, quit" << endl;

  int n = 100; 
  node** table = new node*[n]; 
  
  char in[80]; 
  //until the user quits, keep on running
  while(true){
    cout << "input a command: " << endl;
    cin >> in;
    if(strcmp(in,"print") == 0){
      print(table, n);
    }
    else if(strcmp(in, "add") == 0){
      student* newstudent = new student();
      cout << "first name: " << endl;
      cin >> newstudent->firstname;
      cout << "last name: " << endl;
      cin >> newstudent->lastname;
      cout << "id: " << endl;
      cin >> newstudent->id;
      cout << "gpa: " << endl;
      cin >> newstudent->gpa;
      add(newstudent->id%n, table, newstudent); 
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
void add(int index, node** &table, student* newstudent){
  node* newnode= new node();
  newnode->std = newstudent;
  table[index] = newnode; 
}
void print(node** table, int n){
  for(int i = 0; i < n; i++){
    if(table[i] != NULL){
      cout << table[i]->std->firstname << " " << table[i]->std->lastname << endl;
      cout << "id: " << table[i]->std->id << endl;
      cout << "gpa: " << table[i]->std->gpa << endl;  
    }
  }
}

