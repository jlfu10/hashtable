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
  node* next = NULL; 
};

node** add(int index, node** &table, student* newstudent, int &n);
void print(node** table, int n); 
void remove(node** &table, int id);

int main(){
  cout << "student list (again) (again). Commands: print, add, delete, quit" << endl;

  int n = 100; 
  node** table = new node*[n];
  for(int i = 0; i < n; i++){
    table[i] = NULL; 
  }
  
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
      table = add(newstudent->id%n, table, newstudent, n); 
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
      n += 100;
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
void remove(node** table, int id){
  cout << "remove it remove it!" << endl;
}
