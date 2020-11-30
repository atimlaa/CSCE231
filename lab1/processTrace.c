/*
Name : Aryan Timla
Precess Trace
Lab 1
Checked off by Aaron
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
  int count;
  int address;
  struct Node *nextNode;
}Node;

int main(int argc, char **argv) {

  //open files
  FILE *inputFile = fopen(argv[1], "r");
  FILE *outputFile = fopen(argv[2], "w");
  //Error checking
  if(inputFile == NULL){
    fprintf(stderr, "Can't open input file!\n");
    exit(1);
  }

  int numberOfAccess;
  int address;
  //Initialize head
  Node *head = (Node *) malloc(sizeof(Node));
  // point current to the head
  Node *current = head;

  //Looping through the file and if the addresss match increment the counter
  while (fscanf(inputFile, "%d %d\n", &numberOfAccess , &address) != EOF) {
    if (address == current->address){
      current->count++;
    } else {
      Node *new = (Node *) malloc(sizeof(Node));
      current->nextNode = new;
      current = current->nextNode;
      current->count = 1;
      current->address = address;
      }
    }

    head = head->nextNode;
    current = head;

 // writing the addresses into output file
  while (current != NULL) {
    fprintf(outputFile, "%4d %d\n", current->count , current->address);
    current = current->nextNode;
  }

  //closing the open files
  fclose(inputFile);
  fclose(outputFile);
}
