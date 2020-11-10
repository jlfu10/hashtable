#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;
//to do:
//fix rehashing
//delete function
//comments

struct student{
  char firstname[20];
  char lastname[20]; 
  int id;
  float gpa; 
};
struct node{
  student* std;
  node* next = NULL; 
};

node** add(int index, node** &table, student* newstudent, int &n);
void print(node** table, int n); 
void remove(node** &table, int id, int n);

int main(){
  cout << "student list (again) (again). Commands: print, add, delete, quit" << endl;

  int n = 100; 
  node** table = new node*[n];
  for(int i = 0; i < n; i++){
    table[i] = NULL; 
  }
  ifstream file;
  file.open("students.txt");
  int line = 0;
  int count = 0;
  int id; 
  char in[80];
  char fname[20];
  char lname[20];
  srand(time(NULL));
  //until the user quits, keep on running
  while(true){
    cout << "input a command: " << endl;
    cin >> in;
    if(strcmp(in,"print") == 0){
      print(table, n);
    }
    else if(strcmp(in, "add") == 0){
      cout << "random student (r) or manual input (m)?" << endl;
      cin >> in;
      if(strcmp(in, "r")==0){
	student* newstudent = new student();
	int line = rand()%12; //students
	for(int i = 0; i < 24; i++){ //students times 2
	  if(i == (line*2)-2){
	    file >> fname; 
	  }
	  else if(i == (line*2)-1){
	    file >> lname; 
	  }
	  else{
	    file >> in;
	  }
	}
	file.close();
	file.open("students.txt");
	strcpy(newstudent->firstname, fname);
	strcpy(newstudent->lastname, lname);
	newstudent->id = rand()%n;
	newstudent->gpa = (float)(rand()%400)/(float)(100);
	table = add(newstudent->id%n, table, newstudent, n);
	cout << newstudent->firstname  << " added" << endl;
      }
      else if(strcmp(in, "m")==0){
	student* newstudent = new student();
	cout << "first name: " << endl;
	cin >> newstudent->firstname;
	cout << "last name: " << endl;
	cin >> newstudent->lastname;
	cout << "id: " << endl;
	cin >> newstudent->id;
	cout << "gpa: " << endl;
	cin >> newstudent->gpa;
	table = add(newstudent->id%n, table, newstudent, n);
      }
    }
    else if(strcmp(in, "delete") == 0){
      cout << "id to delete: " << endl;
      cin >> id;
      remove(table, id, n); 
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
node** add(int index, node** &table, student* newstudent, int&n){
  node* newnode= new node();
  newnode->std = newstudent;
  node* current = table[index];
  int count = 1; 
  if(current != NULL){
    while(current->next != NULL){
      current = current->next;
      count++; 
    }
    current->next = newnode;
    if(count == 3){ 
      n = n*2;
      node** newtable = new node*[n]; 
      for(int i = 0; i < (n-100); i++){
	if(table[i] != NULL){
	  node* current = table[i];
	  while(current != NULL){
	    newtable[current->std->id%n] = current;
	    current = current->next;

	  }
	}
      }
      return newtable; 
    }
  }
  else{
    table[index] = newnode;
  }
  return table; 
}
void print(node** table, int n){
  for(int i = 0; i < n; i++){
    if(table[i] != NULL){
      node* current = table[i];
      int count = 0; 
      while(current != NULL){
	cout << current->std->firstname << " " << current->std->lastname << endl;
	cout << "id: " << current->std->id << endl;
	cout << "gpa: " << current->std->gpa << endl;
	cout << endl;
	current = current->next;
      }
    }
  }
}
void remove(node** & table, int id, int n){
  node* current = table[id%n];
  while(current != NULL){
    if(current->std->id == id){
      if(current->next == NULL){
	cout << current->std->firstname << " deleted" << endl;
	delete current->std; 
	delete current;
	table[id%n] = NULL;
	return; 
      }
      else{
	cout << current->std->firstname << " deleted" << endl;
	table[id%n] = current->next;
	delete current->std; 
	delete current;
	return; 
      }
    }
    current = current->next;
  }
  return;
}
