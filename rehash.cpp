n *= 2;
      node** newtable = new node*[n];
      for(int i = 0; i < n; i++){
        newtable[i] = NULL;
      }
      //make the new table
      for(int i = 0; i < n/2; i++){ //loop through original
        if(table[i] != NULL){ //if there's something there in the original
          node* current = table[i]; //the current node (for looping in original linked list)
          node* newcurrent; //current node for newtable
          while(current != NULL){ //loop through the linked list
            if(newtable[current->std->id%n] == NULL){
              node* placeholder = new node();
              placeholder->std = current->std;
              //set the new spot to placeholder
              newtable[current->std->id%n] = placeholder;
            }
            else{
              newcurrent = newtable[current->std->id%n];
              while(newcurrent != NULL){
                newcurrent = newcurrent->next; //we loop through the new linked list
              }//until we get to where the next is empyy
              node* placeholder = new node();
              placeholder->std = current->std;
              newcurrent = placeholder; //set next to the current

            }
            current = current->next; //continue looping
          }
        }
      }
      return newtable;
