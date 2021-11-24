#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//to run the program, type: 
//    1)    ./main linked_list 
//    2)    ./main binary_tree

//how to implement struct data in the program
//*next is used for linked_list method
//*left and *right is used for binary_tree method 
struct data
  {
    char name[40];
    int uniqueID;
    int place[40];
    struct data *next;
    struct data *left;
    struct data *right;
  };

//the list of all functions that will be implemented in this program
//function for linked_list method
void insertList(struct data **head, char name[40], int id);
void removeList(struct data **head, char name[40]);
int searchList(struct data *head, char inputName[40]);
void updateList(struct data **head, char name[40], int code);
void printList(struct data *head);
void checkList(struct data *head, int code);
int idGeneratorList(struct data *head);
void saveList(struct data *head, char fileName[40]);
struct data *retrieveDataFromList(struct data *head, FILE *pFile);
struct data *retrieveList(struct data *head, char fileName[40]);
///////////////////////////////////////////
//function for binary_tree method
struct data *insertBinary(struct data *root, char name[40], int id);
struct data *removeBinary(struct data *root, char targetName[40]);
struct data *getMin(struct data *root);
int searchBinary(struct data *root, char inputName[40]);
struct data *updateBinary(struct data *root, char name[40], int code);
void printBinary(struct data *root);
void printBinaryData(struct data *root);
void checkBinary(struct data *root, int code);
void checkBinaryData(struct data *root, int code);
void treeToRightVine(struct data **root);
void rightVineToTree(struct data **vine, int nodeCount);
void compress(struct data **root, int times);
void _compress(struct data **root, int times);
int getNumNodes(struct data *vine);
void rightRotate(struct data **root);
void leftRotate(struct data **root);
int idGeneratorBinary(struct data *root);
void saveBinary(struct data *root, char fileName[40]);
void saveBinaryData(FILE *pFile, struct data *root);
struct data *retrieveBinary(struct data *root, char fileName[40]);
struct data *retrieveDataFromBinary(struct data *root, FILE *pFile);
///////////////////////////////////////////
void leaveSection();


//argv: linked_list or binary_tree
//METHOD 0:linked_list
//METHOD 1:binary_tree
int main(int argc, char *argv[]){
  struct data *head = NULL;
  struct data *root = NULL;
  int METHOD, option, id, uniqueID, verify, exist, y, code;
  char fileName[20];
  char inputName[40];

  //give information to the user on which method the program will be running based on the argv() input by the user
  if(strcmp(argv[1], "linked_list")==0) {
    printf("Linked List method\n");
    METHOD = 0;
  } else if(strcmp(argv[1], "binary_tree")==0) {
    printf("Binary Tree method\nREMINDER:\n- You can balance the tree by using option 11\n- Option 5(save) and 6(retrieve) are still not available\n");
    METHOD = 1;
  } else {
    printf("Error entering the program.");
    return 1;
  }

  do{
    //Main Menu. Welcoming notes from the App and prompt user to choose available options (1-4).
    printf("\nCOVID Contact Tracing App @ UCL (CCTA@UCL)\n\n");
    if(METHOD==0)
      printf("Welcome to the App.\nPlease choose one of the available options (1-7)\n");
    if(METHOD==1)
      printf("Welcome to the App.\nPlease choose one of the available options (1-7,11)\n");
    printf("1: Registration of new user\n");
    printf("2: Check-in to a place\n");
    printf("3: Remove user\n");
    printf("4: Show record\n");
    printf("5: Save to file\n");
    printf("6: Retrieve data\n");
    printf("7: Exit\n");
    if(METHOD==1)
      printf("11:Balance Binary\n");
    scanf("%d", &option);
    
    //switch statement that direct the program to the required functionality input by user 
    switch(option)
    {
      //introduce user
      case 1:
        //prompt user to input their name
        printf("Insert Your Name(no spaces): ");
        scanf("%s", inputName);

        //Generate 4-digit unique ID and insert the data by using either linked list or binary tree
        if(METHOD==0){
          uniqueID = idGeneratorList(head);
          insertList(&head, inputName, uniqueID);
        } else if(METHOD==1) {
          uniqueID = idGeneratorBinary(root);
          root = insertBinary(root, inputName, uniqueID);
        } 

        //Message indicating the registration is successful
        printf("\nHello %s! This is your generated ID.\n", inputName);
        printf("%d\n", uniqueID);
          
        break;


      //check in to a place
      case 2:
        //prompt requiring user to input their name
        printf("Insert your name: ");
        scanf("%s", inputName);

        //check whether the name is in the database or not, if YES, exist=1, if NO, exist=0
        if(METHOD==0) 
          exist = searchList(head, inputName);
        else if(METHOD==1)
          exist = searchBinary(root, inputName);

        //message telling the user that the name entered by the user is not in the database
        if(exist==0)
        {
          printf("Your record is not in the database. Sorry.\n");
          break;
        }     
        
        //if the name is in database, proceed to the check-in section
        if(exist==1) {
          printf("\n\nHello %s!!!\n", inputName);
          printf("Insert the code of the place you are going\n");
          printf("[1] - School\n");
          printf("[2] - Hospital\n");
          printf("[3] - Cafeteria\n");
          printf("[4] - Field\n");
          printf("[5] - Park\n");
          printf("[6] - Laboratory\n");
          printf("[7] - Supermarket\n");
          printf("Code: ");

          //User will input the code of the place they have been and it will then be updated in the database
          scanf("%d", &code);

          //if the code input by the user between 1 and 7, update the list using either linked_list or binary_tree
          if(code <=7 && code >=1)
          {
            if(METHOD==0)
              updateList(&head, inputName, code);
            if(METHOD==1)
              root = updateBinary(root, inputName, code);
            printf("Record updated.You have been to %d\nThanks for cooperation\n", code);
          } else {
          printf("The place is not in the list. \n");
          } 
        }        
        break;
            

      //remove user
      case 3:
        //prompt user to enter their name
        printf("Insert your name: ");
        scanf("%s", inputName);

        //check whether the name entered is in database or not
        if(METHOD==0) 
          exist = searchList(head, inputName);
        else if(METHOD==1)
          exist = searchBinary(root, inputName);

        //if the name is not in database, print a message
        if(exist==0)
        {
          printf("Your record is not in the database. Sorry.\n");
          break;
        }     
        
        //if the name is in database, proceed to the delete section
        if(exist==1) {
          //user will be asked to verify their action to delete all of the record
          printf("Hello %s. Your record is in the database. Are you sure to delete all your record?(Press '1' for Yes and '0' for No)\n", inputName);
          scanf("%d", &verify);

          //if the user has confirmed to remove their data, removeList function will be executed
          if(verify==1)
          {
            if(METHOD==0)
              removeList(&head, inputName);
            if(METHOD==1)
              root = removeBinary(root, inputName);

            printf("Data has been deleted\n");
          }
        }
        break;


      //print record
      case 4:
        option=0; //initialize the variable option to '0'
        code = 0; 

        //User need to choose between two options, either to see all the records in database or to see which person have been to a particular place  
        printf("\nChoose between following options:\n");
        printf("1: Print all data\n");
        printf("2: Check which user have been to a particular place\n");
        scanf("%d", &option);

        if(option==1)
        {
          printf("Records in the database:\n");
          printf("ID\t\tName\n");

          //print all the information in the database based on the METHOD chosen by the user earlier
          if(METHOD==0)
            printList(head);
          else if(METHOD==1)
            printBinary(root);
        } 
        else if (option == 2)
        {
          printf("Type the code of the place you want to check(1-7): ");
          scanf("%d", &code);
          if(code>=1 && code<=7) 
          {
            printf("\nList of person who has been to %d:\n", code);
            
            //print the name of person who has been to "code"
            if(METHOD==0)
            checkList(head, code);
            else if(METHOD==1) 
            checkBinary(root, code);
          } else {
            printf("Sorry. The code is not in database.\n");
          }
        }

        leaveSection(); 
        break;
        


      //save data
      case 5:
        //prompt user for the name of the file they want to save to
        printf("File Name: \n");
        scanf("%s", fileName);
        if(METHOD==0)
          saveList(head, fileName);
        else if(METHOD==1)
          saveBinary(root, fileName);
        break;


      //retrieve data
      case 6:
        //prompt user for the name of the file they want to retrieve data from
        printf("File Name: \n");
        scanf("%s", fileName);
        if(METHOD==0)
          head = retrieveList(head, fileName);
        else if(METHOD==1)
          root = retrieveBinary(root, fileName);
        
        break;


      case 7:
        //Thank you notes for using the app
        printf("\n\nThank you for using CCTA@UCL.\nPlease maintain social distancing and wear a mask when necessary. Your health is our priority.\nAnd do not forget to get your coursework done.\nHave a good day\n");


      //if using binary_tree METHOD, the user can opt to balance the binary tree
      if(METHOD==1) 
      {
      case 11:
        //balance the binary tree using dsw algorithm
        treeToRightVine(&root);     //create the backbone of binary tree
        int nodeCount = getNumNodes(root);
        printf("Total number of nodes: %d\n", nodeCount);
        rightVineToTree(&root, nodeCount);
        printf("Balance Successful");
        break;
      }
    }  
  }
  while(option!=7);
  return 0;
}

//function that will generate a unique ID for each user
int idGeneratorList(struct data *head)
{
  srand(time(NULL));
  int num;
  struct data *traverse;
  traverse = head;

  //Generate some random number
  do
  {
    num = rand()%10000;
  }
  while(num<1000);

  //Check whether the number generated is unique or not
  while(traverse!=0)
  {
    if(num==traverse->uniqueID)
    {
      //if the number generated match with some id in database, generate a new number and start checking from head again
      do
      {
        num = rand()%10000;
      }
      while(num<1000);
      traverse = head;      
    }
    else
      traverse = traverse->next;
  }

  return num;
}

//function to insert a new data into a linked list
void insertList(struct data **head, char name[20], int id)
{ 
  int index=0;
  struct data *traverse;
  traverse = *head;

  //temp is created as a temporary struct to store the user's information before being linked to the main linked list chain
  struct data *temp;
  temp = (struct data*) malloc(sizeof(struct data));
  strcpy(temp->name, name);
  temp->uniqueID = id;
  for(index=0; index<40; index++)
    temp->place[index]=0;

  //check if there is no element in the linked list
  if(traverse==0)
  {
    temp->next = *head;
    *head = temp;
  } 
  else 
  { 
    //check if the linked list have second element
    if(traverse->next==NULL)
    {
      //if there is no second element, compare temp->name 
      //with  the first element in the linked list
      if(strcmp(temp->name, traverse->name)>0)
      {
        //if temp->name comes after first element(traverse->name), insert at tail
        temp->next = traverse->next;
        traverse->next = temp;
      } else {
        //if temp->name comes before first element(traverse->name), insert at head 
        temp->next = *head;
        *head = temp;
      }
    } else {
      //the linked list have more than two elements
      
      //if it is the first element
      //insertion at head
      if(strcmp(temp->name, traverse->name)<0)
      {
        temp->next = traverse;
        *head = temp;
      }
      else
      {
        //traverse the linked list if temp->name comes after traverse->next->name
        //the reason we need to apply 'look-ahead' method is because once we have go to nth position in the linked list, we cannot go back to the (n-1)th position. This prevent us to link (n-1)th position to the new cell
        while(strcmp(temp->name, traverse->next->name)>0)
        {
          traverse = traverse->next;
          //if it is the last element
          //insertion at tail
          if(traverse->next==NULL)
            break;
        }

        //insertion in the middle; between traverse and traverse->next
        temp->next = traverse->next;
        traverse->next = temp;
      }
    }
  }
}

//remove user's record from the database
void removeList(struct data **head, char name[40])
{
  struct data *traverse;
  struct data *temp;
  traverse = *head;
  //check if the cell that want to be deleted is the first element of linked list
  if(strcmp(traverse->name, name)==0)
  {
    *head=traverse->next;
    free(traverse);
  }
  else
  {
    //if the node that want to be deleted in the database is not the first element, traverse the linked list until the matching node is found
    while(strcmp(traverse->next->name, name)!=0)
    {
      traverse = traverse->next;
    }
    //store the address of (traverse->next)->next in temp variable, else the data will be lost when removing traverse->next 
    temp = (traverse->next)->next;
    free(traverse->next);
    traverse->next = temp;
  }
}

//function checking whether the name input by user match any node in the database 
int searchList(struct data *head, char inputName[40])
{
  struct data *traverse;
  traverse = head;

  //traverse the linked list until the inputName is equal to the traverse->name
  //if there is a match, return 1   
  while(traverse!=NULL)
  {
    if(strcmp(inputName,traverse->name)==0)
    {
      return 1;
      break;
    }
    traverse = traverse->next;
  }
  //if there is no match, it will return 0
  return 0; 
}

//update the place that user's have been to 
void updateList(struct data **head, char name[40], int code)
{
  int y=0;
  struct data *traverse;
  traverse = *head;
        
  //traverse the list until the correct node is found
  while(strcmp(traverse->name,name)!=0)
  {
    traverse = traverse->next;
  }
  
  //Check for an empty 'place' element in the struct 
  while(traverse->place[y]!=0)
  {
    y++;  
  }
  
  //update the place entered by user
  traverse->place[y] = code;
}

//function used to print all the node in the linked list
void printList(struct data *head)
{
  int idx=0;
  struct data *traverse;
  traverse = head;

  //traverse the linked list and print all the information contained in the cell until traverse==NULL
  while(traverse!=NULL)
  {  
    //read->next = head->next;
    printf("%d\t%s\n", traverse->uniqueID, traverse->name);
    printf("Place:\t");
    //print the code of place the user have been to until the end
    while(traverse->place[idx]!=0)
    {
      printf("[%d] ", traverse->place[idx]);
      idx++;
    }
    printf("\n\n");
    traverse = traverse->next;
    idx = 0;
  }
}

//function to check which person has been to a particular place
void checkList(struct data *head, int code)
{
  struct data *traverse;
  traverse = head;
  int idx=0;
  int available = 0;

  //check each person whether they have been to the assigned place(code) or not; if YES, print his/her name
  while(traverse!=NULL)
  {
    while(traverse->place[idx]!=0) 
    {
      if(traverse->place[idx]==code)
        {
        printf("%s\n", traverse->name);
        available = 1;  
        break;
        }
      idx++;
    }
    traverse = traverse->next;
    idx=0;
  }

  if(available==0)
    printf("No one has been to this place.\n");
}

//function to save all the information in the linked list into a file
void saveList(struct data *head, char fileName[30])
{
  FILE *pFile;
  pFile = fopen(fileName, "wb");
  
  //check if the file is accessible or not
  if(pFile!=NULL)
  {
    //create two struct data, currentList to store all the information in the current node, holdNext to hold all the linked list chain after the current node
    struct data *currentList = head;
    struct data *holdNext = NULL;

    while(currentList!=NULL)
    {
      holdNext = currentList->next;
      currentList->next = NULL;

      //write the content of currentList into the file
      fseek(pFile, 0, SEEK_END);
      fwrite(currentList, sizeof(struct data), 1, pFile);

      //traverse the list until there is nothing in currentList
      currentList->next = holdNext;
      holdNext = NULL;
      currentList = currentList->next;
    }

    printf("Data has been saved in %s\n", fileName);
    fclose(pFile);
  } else {
    printf("Error opening the file\n");
  }
}

//function that is responsible to retrieve current entry's information into main program
struct data *retrieveDataFromList(struct data *head, FILE *pFile)
{
  size_t returnValue;
  //check if the main program has retrieved the first entry in the file, if NO, create the head of our linked list using that entry
  if(head == NULL)
  {
    head = malloc(sizeof(struct data));
    returnValue = fread(head, sizeof(struct data), 1, pFile);
    head->next = NULL;
  } else {
    //create two new struct data 
    //indexList is used to traverse the linked list in our main program until we find an empty node
    //newList will store the information retrieve from file
    struct data *indexList = head;
    struct data *newList = malloc(sizeof (struct data));
    while(indexList->next != NULL)
    {
      indexList = indexList->next;
    }
    
    returnValue = fread(newList, sizeof(struct data), 1, pFile);
    indexList->next = newList;
    newList->next = NULL;
  }
  return head;
}

//function to retrieve all the information in the file to the program
struct data *retrieveList(struct data *head, char fileName[30])
{
  FILE *pFile; 
  pFile = fopen(fileName, "rb");

  //check if there is any data inside the FILE
  if(pFile!=NULL)
  {
    //start from a clean database
    head=NULL;
    //point to pFile pointer to the end of the file
    fseek(pFile, 0, SEEK_END);
    //tell the program how many position it has moved to reach the end of the file and store it in fileSize
    long fileSize = ftell(pFile);
    //point the pFile pointer back to the first part of file
    rewind(pFile);

    //calculate how many entries are there in the file
    int numEntries = (int)(fileSize / (sizeof(struct data)));
    printf("numEntries %d\n", numEntries);

    //for each entry, execute retrieveDataFromList function that is responsible to retrieve the information in current entry into our main program
    int loop = 0;
    for(loop=0; loop<numEntries; loop++) {
      fseek(pFile, (sizeof(struct data))*loop, SEEK_SET);
      head = retrieveDataFromList(head, pFile);
    }
    printf("Data has been successfully retrieved.\n");

  } else {
    printf("Error accessing the File.\n");
  }
  return head;
}

//function to generate a uniqueID to user
int idGeneratorBinary(struct data *root)
{
  srand(time(NULL));
  int num, index=0, id[10000];
  struct data *traverse;
  traverse = root;

  //Generate some random number
  do
  {
    num = rand()%10000;
  } 
  while(num<1000);

  //This while statement will create a separate list that stores all the id that has been used so that we can use it for the checking purposes to identify whether the random number generated earlier is unique or not. This method is much easier to implement than traversing all the element in binary tree.
  while(id[index]!=0)
  {
    if(num == id[index]) 
    {
      do
      {
        num = rand()%10000;
      } 
      while(num<1000);
      index=-1; //set index to -1 so that we can check once again from the first element of the array if there is any repetition of the generated id
    }
    index = index+1;
  }
  id[index] = num;

  return num;
}

//function on inserting data using binary tree
struct data *insertBinary(struct data *root, char name[40], int id)
{
  //if the current root is empty, we will insert the data input by user, otherwise traverse the binary tree until we find an empty root
  if(root==NULL)
  {
    //create temp structure to store all the user's information
    struct data *temp;
    int index = 0;
    temp = (struct data *) malloc(sizeof(struct data));

    strcpy(temp->name, name);
    temp->uniqueID = id;
    for(index=0; index<40; index++)
      {
        temp->place[index]=0;
      }
    temp->left = NULL;
    temp->right = NULL;
    //copy all the information to the root
    root = temp;
  } else {
    if(strcmp(name, root->name)<0)
    {
      //if the current name comes before the root's name, go to the left child
      //printf("Left\n");   //keep track of the location of insertion
      root->left = insertBinary(root->left, name, id);
    } else {
      //if the current name comes after the root's name, go to the right child
      //printf("Right\n");  //keep track of the location of insertion
      root->right = insertBinary(root->right, name, id);
    }
  }
  
  return root;
}

//function on removing data from a binary tree
struct data *removeBinary(struct data *root, char targetName[40])
{
  int idx=0;
  struct data* temp; 
  if(root==NULL)
    return NULL;
  else
  {
    //if targetName comes before the name of current element, move the root to the current element's left child  
    if(strcmp(targetName, root->name)<0)
      root->left = removeBinary(root->left, targetName);
    
    //if targetName comes before the name of current element, move the root to the current element's left child  
    else if(strcmp(targetName, root->name)>0)
      root->right = removeBinary(root->right, targetName);
    
    //node is found
    else {
        //Case 1: targetElement is a leaf node
        if(root->left==NULL && root->right==NULL)
        {
          free(root); 
          root = NULL;
          return root;
        }
        //Case 2a: node has only one child(right)
        else if(root->left==NULL) {
          temp = root->right;  
          free(root);
          root = temp;
          return root;
        } 
        //Case 2b: node has only one child(left)
        else if(root->right==NULL) {
          temp = root->left;   
          free(root);
          root = temp;
          return root;
        } 
        //Case 3: node has two child
        else { 
          //find the nearest name(minimum value) to the targetName alphabetically from the right sub-tree
          temp = getMin(root->right);
          //copy the content of temp into the node to be deleted
          strcpy(root->name,temp->name);
          root->uniqueID = temp->uniqueID;
          while(root->place[idx]!=0) {
            root->place[idx] = temp->place[idx];
            idx++;
          }
          while(temp->place[idx]!=0) {
            root->place[idx] = temp->place[idx];
            idx++;
          }
          //delete the node that is copied from
          root->right = removeBinary(root->right, temp->name);
          return root;
        }
    }
  }
  return root;
}

//function to get to an entry that comes first alphabetically 
struct data *getMin(struct data *root)
{
  struct data *temp;
  temp = root;
  
  //find the most left data in binary tree
  while(temp->left!=NULL)
    temp = temp->left;
  
  return temp;
}

//function to search whether the name entered by the user exist in the binary tree or not
int searchBinary(struct data *root, char inputName[40])
{
  int result=0;
  if(root!=NULL)
  {
    if(strcmp(inputName, root->name)<0)
      result = searchBinary(root->left, inputName);
    else if(strcmp(inputName, root->name)==0) {
      //if we found a matching cell, result=1
      result = 1;
    } 
    else if(strcmp(inputName, root->name)>0)
      result = searchBinary(root->right, inputName);
  }

  //if result==1, indicating a matching cell exist, we return an integer 1 to the main program, and if we didn't find any matching cell(result==0), we return a 0 to the main program
  if(result == 1)
    return 1;
  else 
    return 0;
}

//update places in the list using binary tree
struct data *updateBinary(struct data *root, char name[40], int code)
{
  int idx = 0;

  //check that the root of the program is not empty
  if(root!=NULL)
  {
    //if the user's name comes before root's name, go to the left child
    if(strcmp(name, root->name)<0)
      updateBinary(root->left, name, code);
    
    //if we found a matching cell, find an empty element in root->place and store the code of visited place there
    else if(strcmp(name, root->name)==0) {
      while(root->place[idx]!=0)
        idx = idx+1;
      root->place[idx] = code;
      return root;
    } 

    //if the user's name comes after root's name, go to the right child
    else if(strcmp(name, root->name)>0)
      updateBinary(root->right, name, code);
  }
  return root;

}

//function that is used to print all the information contained in binary tree
void printBinary(struct data *root) 
{
  if(root!=NULL)
  {
    printBinary(root->left);
    printBinaryData(root);
    printBinary(root->right);
  } 
}

//function that is used to print the current entry of binary tree
void printBinaryData(struct data *root) 
{
  int idx = 0;
  printf("%d\t%s\n", root->uniqueID, root->name);
  printf("Place:\t");
  while(root->place[idx]!=0)
  {
    printf("[%d] ", root->place[idx]);
    idx++;
  }
    printf("\n\n");
}

//function to check which person has been to a particular place
void checkBinary(struct data *root, int code) 
{
  if(root!=NULL)
  {
    checkBinary(root->left, code);
    checkBinaryData(root, code);
    checkBinary(root->right, code);
  }
}

//function to check all the places a person has been to and print his/her name if the person has been to the place(code) 
void checkBinaryData(struct data *root, int code)
{
  int idx=0;

  while(root->place[idx]!=0) 
    {
      if(root->place[idx]==code)
        {
        printf("%s\n", root->name);
        break;
        }
      idx++;
    }
}

//create the backbone of the binary tree
void treeToRightVine(struct data **root){
  struct data *traverse = *root;
 
  if(traverse == NULL)
    return;
  
  while(traverse->left !=NULL){
    rightRotate(&traverse);
  }
  
  if(traverse->right != NULL){
    treeToRightVine(&(traverse->right));
  }
  
  *root = traverse;
}

//create a balanced tree from the backbone with multiple times of left rotations
//It basically goes like this: 
// 1. Left rotates on x odd nodes in the backbone, where x is the number of nodes in the lowest level.
// 2. Do a left rotate on every odd node in the backbone (root = 1).
//Keep doing that until it's balanced.
void rightVineToTree(struct data **vine, int nodeCount){
  struct data *root = *vine;
  int m = pow(2, floor(log2(nodeCount+1)))- 1 ;
  int expected = nodeCount - m;     //find the expected number of node at the lowest level

  //1. Do left rotates for every node on bottom level of finished tree.
  compress( &root, expected );
  
  //2. Do a left rotate on every odd node in the backbone (root = 1).
  while( m>1 ){
    m = floor( m/2 );
    compress( &root, m );
  }
  *vine = root;
}

void compress(struct data **root, int times){
  int i;
 
  for(i=0; i<times; i++)
    _compress( &(*root), i ); 
}  

void _compress(struct data **root, int times){
 
  if(times == 0)    
    //times=0 meaning the rotation will happen at the root (top of binary tree)
    leftRotate(&(*root));
  else
    //rotation will happen elsewhere (other than the top of binary tree) 
    _compress( &((*root)->right), times-1);  
}  

//get the number of nodes in the backbone
int getNumNodes(struct data *vine){
  int nodeCount =0;
  
  while( vine != NULL){
    nodeCount ++;
    vine = vine->right; 
  }
  
  return nodeCount; 
}

//do right rotation on the desired node
void rightRotate(struct data **root){
	struct data *node1, *node2, *childNode;

	childNode = *root;								//assign the 1st pointer to childNode
	node1 = childNode->left;
	node2 = childNode->left->right;			//assign the granChildNode (left->right)  to node2
  node1->right = childNode;						//pass the 1st pointer node to node1 right side
  node1->right->left = node2;					//pass the node2 to node1 (right->left)
  *root = node1;										//let the node1 become the root
}

//do left rotation on the desired node
void leftRotate(struct data **root){
	struct data *node1, *node2, *childNode;

	childNode = *root;								//assign the 1st pointer to childNode
	node1 = childNode->right;
	node2 = childNode->right->left;			//assign the granChildNode (right->left)  to node2
  node1->left = childNode;						//pass the 1st pointer node to node1 left  side
  node1->left->right = node2;					//pass the node2 to node1 (left->>right)
  *root = node1;										//let the node1 become the root
}

//function to save current list into a file
void saveBinaryData(FILE *pFile, struct data *root)
{
  if(root!=NULL)
  {
    saveBinaryData(pFile, root->left);

    struct data *currentList = root;
    //currentList = (struct data*)malloc(sizeof(struct data));
    currentList->left = NULL;
    currentList->right = NULL;
    fwrite(currentList, sizeof(struct data), 1, pFile);
    fprintf(pFile, "%s", "recorded\n");
    
    saveBinaryData(pFile, root->right);
  }
}

//function that save all the information in the binary tree into a file
void saveBinary(struct data *root, char fileName[40])
{
  printf("Sorry. This functionality is not available for now. \n");
  /*FILE *pFile;
  pFile = fopen(fileName, "wb");

  //check if the pFile is accessible or not
  if(pFile!=NULL)
  {
    saveBinaryData(pFile, root);
    printf("Data has been saved in %s\n", fileName);
    fclose(pFile);
  } else {
    printf("Error opening the file.\n");
  }*/
}

//function that is responsible to retrieve binary tree stored in a file
struct data *retrieveBinary(struct data *root, char fileName[40])
{
  printf("Sorry. This functionality is not available for now. \n");
  return 0;
}

//function to informing the user that the application will return to Menu
void leaveSection()
{
  int leave;
  printf("\nType any number to return to Menu: ");
  scanf("%d", &leave);
}