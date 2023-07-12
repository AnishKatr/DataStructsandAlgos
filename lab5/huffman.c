//Anish Katragadda
// Lab 5 - Project 2

//Summary
//The purpose of this weeks lab is to apply a Huffman Tree
//The application of this tree is to compress files
//And we build this tree from bottom to top
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"


typedef struct node NODE;

//hopNumber function
//This function will start at the leaf of a tree and traverse up to the root
int hopNumber(struct node * leaf){
    int hops = 0;
    while(leaf -> parent != NULL){
        leaf = leaf -> parent;
        hops++;
    }
    return hops;
}

//Compare function
//Compares the data between two nodes
int compare(struct node *first, struct node *second){
    return ( first -> count < second -> count) ? -1 : (first -> count > second -> count);
}

//Main Function
int main(int argc, char *argv[]){

    FILE *fp = fopen(argv[1], "r"); // Checks if file opened correctly
    if(fp == NULL){
        return 0;
    }

    int occurences[257] = {0};
    int i;

	do {								// Will start by calling the fgetc function to count the occurences
	  int c;
	  
      c = fgetc(fp);
      if( feof(fp) )					
      {
         break;
      }
      occurences[c]++;
    } while(1);

    PQ *pqueue = createQueue(compare);// Creates the Priority Queue and will store the leaf nodes

    struct node* leaves [257] = {0};
    for(i = 0; i < 257; i++){
        leaves[i] = NULL;
    }
    
    for(i = 0; i < 256; i++){
        if(occurences[i] > 0){
            NODE * thenode = malloc(sizeof(struct node));
            thenode -> count = occurences[i];
            thenode -> parent = NULL;
            addEntry(pqueue, thenode);
            leaves[i] = thenode;
        }
    }

    NODE *zeroCountNode = malloc(sizeof(struct node)); //creates a tree with an empty count for the end of the file
    zeroCountNode -> count = 0;
    zeroCountNode -> parent = NULL;
    addEntry(pqueue, zeroCountNode);
    leaves[256] = zeroCountNode;

    while(numEntries(pqueue) > 1){ //Removes the two lowest priority trees, and then insert the new tree back into the priority queue
        NODE *first = removeEntry(pqueue);
        NODE *second = removeEntry(pqueue);
        NODE *third = malloc(sizeof(struct node));

        third -> count = first -> count + second -> count;
        third -> parent = NULL;
        first -> parent = third;
        second -> parent = third;
        addEntry(pqueue, third);
    
    }

    for (i = 0; i < 257; i++) { //Prints the stats of the character by checking the number of hops, and iterating through the leaf array
    	if (leaves[i]!=NULL) {
    		int numberOfHops;
    		numberOfHops = hopNumber(leaves[i]);
    		if (isprint(i))								
    		{
    			printf("%c: %d x %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
    		}
    		else {
    			printf("%03o: %d x %d bits = %d\n", i, occurences[i], numberOfHops, occurences[i]*numberOfHops);
    		}
    		
    	}
    }
    //Pack the input file using the provided function
    pack(argv[1], argv[2], leaves);
}
