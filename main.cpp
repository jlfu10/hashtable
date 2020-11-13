#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;
//structs for student and node
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
//function prototypes
node** add(int index, node** &table, student* newstudent, int &n);
void print(node** table, int n); 
void remove(node** &table, int id, int n);

//my hash function is just to hash the id of the student

int main(){
  cout << "student list (again) (again). Commands: print, add, delete, quit" << endl;

  int n = 100; 
  node** table = new node*[n];
  for(int i = 0; i < n; i++){
    table[i] = NULL; //set all to values to NULL 
  }
  ifstream first;
  first.open("firstname.txt"); //open the text file with students
  ifstream last;
  last.open("lastname.txt"); 
  int f = 0; //which line (first/last) to read on random
  int l = 0; 
  int id; //for which id to delete
  int increment = 0; 
  char in[80]; //for inputs in loops
  char fname[20]; //firstname of random student
  char lname[20]; //lastname of random student
  srand(time(NULL)); //for random
  
  //until the user quits, keep on running
  while(true){ 
    cout << "input a command: " << endl;
    
    cin >> in;
    if(strcmp(in,"print") == 0){
      print(table, n); //print
    }
    else if(strcmp(in, "add") == 0){
      cout << "random student (r) or manual input (m)?" << endl;
      cin >> in;
      if(strcmp(in, "r")==0){
	cout << "how many students would you like to add?" << endl;
	cin >> id;
	for(int a = 0; a < id; a++){
	  //random student
	  student* newstudent = new student();
	  //random line from text file
	  int f = rand()%12;
	  int l = rand()%12; 
	  //loop until we see the lines that have our first and last name
	  for(int i = 0; i < 12; i++){
	    if(i == f){
	      first >> fname; 
	    }
	    else{
	      first >> in; 
	    }
	    if(i == l){
	     last >> lname; 
	    }
	    else{
	      //otherwise, scan the next line so that we can keep on looping
	      last >> in;
	    }
	  }
	  //reopen file
	  first.close();
	  first.open("firstname.txt");
	  last.close();
	  last.open("lastname.txt"); 
	  //make the newstudent's attributes and add it to the table
	  strcpy(newstudent->firstname, fname);
	  strcpy(newstudent->lastname, lname);
	  newstudent->id = increment;
	  increment++;
	  newstudent->gpa = (float)(rand()%400)/(float)(100);
	  table = add(newstudent->id%n, table, newstudent, n);
	  cout << newstudent->firstname  << " added" << endl;
	}
      }
      else if(strcmp(in, "m")==0){
	//manual student, get inputs for student, add
	student* newstudent = new student();
	cout << "first name: " << endl;
	cin >> newstudent->firstname;
	cout << "last name: " << endl;
	cin >> newstudent->lastname;
	cout << "id: " << endl;
	cin >> newstudent->id;
	cout << "gpa: " << endl;
	cin >> newstudent->gpa;
	//set table to the table with new student
	table = add(newstudent->id%n, table, newstudent, n);
      }
    }
    else if(strcmp(in, "delete") == 0){
      cout << "id to delete: " << endl;
      cin >> id;
      remove(table, id, n); //remove 
    }
    else if(strcmp(in, "quit") == 0){
      return 0; //quit the program
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
    //loop through the linked list until we see the last node in the list
    //then, we set that node's next node to the new node
    while(current->next != NULL){
      current = current->next;
      count++; //for how many nodes are in the list
    }
    current->next = newnode;
    if(count == 3){ //if we see that there are three nodes in the list, rehash
      n *= 2;
      //make the rehashed table with double size
      node** newtable = new node*[n];
      for(int i = 0; i < n; i++){
	newtable[i] = NULL;
      }
      //loop through the original tasble
      for(int i = 0; i < n/2; i++){
	//if there is an element to be rehashed
	if(table[i] != NULL){
	  node* current = table[i]; //what node we are on (original)
	  while(current != NULL){
	    //make the new node with student, so that next is not carried over
	    node* placeholder = new node();
	    placeholder->std = current->std;
	    if(newtable[placeholder->std->id%n] == NULL){
	      //if the newtable index is empty, we can just replace
	      newtable[placeholder->std->id%n] = placeholder; 
	    }
	    else{
	      node* newcurrent = newtable[placeholder->std->id%n];
	      //otherwise loop until we get to the end of the linked list
	      while(newcurrent->next != NULL){
		newcurrent = newcurrent->next; 
	      }
	      //add the node
	      newcurrent->next = placeholder;
	    }
	    current = current->next; 
	  }
	}
      }
      //if we rehashed, return the new table
      cout << "rehashed" << endl;
      return newtable;
    }
  }
  else{
    table[index] = newnode; //if this is the first instance, set the index to the node
  }
  return table; 
}
void print(node** table, int n){
  //if it is not null, we print using linked list
  for(int i = 0; i < n; i++){
    if(table[i] != NULL){
      node* current = table[i];
      int count = 0; 
      while(current != NULL){
	cout << current->std->firstname << " " << current->std->lastname << endl;
	cout << "id: " << current->std->id << endl;
	cout << "gpa: " << current->std->gpa << endl;
	cout << endl;
	//loop through linked list with value at hash index
	current = current->next;
      }
    }
  }
}
void remove(node** & table, int id, int n){
  node* current = table[id%n];
  //the current node is the hash value we want
  while(current != NULL){
    //if we see the right id in the hash value linked list
    if(current->std->id == id){
      if(current->next == NULL){
	//if the next is null, we can just delete it and set table value to NULL
	cout << current->std->firstname << " deleted" << endl;
	delete current->std; 
	delete current;
	table[id%n] = NULL;
	return; 
      }
      else{
	//otherwise, just set the table value to the next in the list
	cout << current->std->firstname << " deleted" << endl;
	table[id%n] = current->next;
	delete current->std; 
	delete current;
	return; 
      }
    }
    //keep on looping
    current = current->next;
  }
  return;
}
