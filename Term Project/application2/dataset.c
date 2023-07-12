//Anish Katragadda
//COEN 12 - Spring 2023
//Term Project Application 2 - dataset.c

#define Empty 0
#define Filled 1
#define Removed 2


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"


//Definition of our record
struct record{	
	int ID; //Student ID which is a unique Integer value from 1 - 2000
	int Age; //Age randomly generated for each student between 18 - 30
};

    
struct set{
	int count; //Number of Elements in our data structure
	int length;//The maximum students/records we can have in our SET

	RECORD** studentRecord;//Creates a pointer to the first pointer in the arrya of studentRecord pointers
	char *flag;//Points to the first flag in our rray of flags, which we need to implement a hash table
}; 

//createSet
//this function's core purpose is to allocate memory for our Data structure and array of studentRecord pointer
//This allocation has a maximum size of maxElts. Once it is done allocating and setting our flags array to empty
//at each index it will then return a pointer to our SET
//Efficiency: O(n)
SET *createSet(int maxElts){

	SET*sp = malloc(sizeof(SET));
	assert(sp != NULL);

	sp -> count = 0;
	sp -> length = maxElts;
	sp -> studentRecord = malloc(sizeof(RECORD*)*maxElts);

	assert(sp -> studentRecord != NULL);
	sp -> flag = malloc(sizeof(char)*maxElts);
	assert(sp -> flag != NULL);
	int i = 0;
	for(i = 0; i < sp -> length; i++){
		sp -> flag[i] = Empty;
	}
	
	return sp;
}


//searchID
//The searchID Function will search through our set data structure to find pecific Student ID's
//If the specific student ID we are searching for is found it will set our boolean value to found
//The function will return the index at which the id is located otherwise will return -1 if not found
//Efficiency: O(n) with cases of O(1) possible 

int searchID(SET *sp, int studentID, bool *found){
	assert(found != NULL);
	*found = false;
	assert(sp != NULL);
	if(sp -> count == 0){
		printf("No records in the Data Set, cannot execute search.\n");
		return -1;
	}
	printf("Searching for record with ID %d in the Data Set.\n",studentID);
	int position = studentID % sp->length;
	int i = 0;
	for (i = 0; i < sp -> length; i++){	
		int newPosition = (position + i) % sp->length;
		if(sp -> flag[newPosition] == Filled){
			if(sp -> studentRecord[newPosition] -> ID == studentID){
				*found = true;
				printf("Record with ID %d was found in Data Set.\n", sp->studentRecord[newPosition]->ID);
				return newPosition;
			}
		}
	}
	printf("Record with ID %d was not found in Data Set.\n", studentID);
	return -1;
}


//destroySet
//This function will go one by one freeing each element in our array of studentRecord,
//then free the flag, then free the studentRecord array itself. Then finally will free the
//pointer which performed these operations
//Efficiency: O(n)
void destroySet(SET *sp){
	assert(sp != NULL);
	int i = 0;

	for(i=0; i < sp->count; i++){
		free(sp -> studentRecord[i]);
	}
	free(sp -> flag);
	free(sp -> studentRecord);

	free(sp);	
}

//addElement
//This Function will allocate memory to insert a new element, which is pointed to by a pointer, within our SET
//It does this by utilizing the has function to find a "home" location, if this spot is empty it will then be 
//Filled by this element otherwise we will utilize linear probing to iterate through and find a location for the function
//It will do this till the first empty or removed spot , be inserted, then change the value in flags to be recorded as filled. 
//Efficiency: O(1) unless probing is utilized where then it will be O(n)

void addElement(SET *sp, int studentID, int studentAge){		
	assert(sp != NULL);
	assert(sp -> count < sp -> length);
	int position = studentID % sp -> length;
	int i = 0;
	for (i = 0; i < sp -> length; i++){	
		int newPosition = (position + i) % sp -> length;
		if (sp -> flag[newPosition] == Removed){	
			RECORD* newRecord = malloc(sizeof(RECORD));
			newRecord -> Age = studentAge;
			newRecord -> ID = studentID;
			sp -> studentRecord[newPosition] = newRecord;
			sp -> flag[newPosition] = Filled;
			sp -> count++;
			return;
		}else if (sp -> flag[newPosition] == Empty){
			RECORD* newRecord = malloc(sizeof(RECORD));
			newRecord -> Age = studentAge;
			newRecord -> ID = studentID;
			sp -> studentRecord[newPosition] = newRecord;
			sp -> flag[newPosition] = Filled;
			sp -> count++;
			return;
		}	
	}	
}


//removeElement
//This function first will call the search function to identify all the ID's that have an age matching to the age
//that we selected to be the one we delete. Which then passes the ID to the next part of the function which then removes
//the element and sets the flag array to removed at that index and derements the count. Depending on whether the record
//was found or not the function will print a respective statement saying eith it couldn't be removed or it has been removed
//Efficiency: O(n)

void removeElement(SET *sp, int studentID){
	assert(sp != NULL);
	bool found = false;
	int position = searchID(sp,studentID,&found);
	if(found == false){
		printf("Record with ID %d could not be removed from the Data Set.\n\n",studentID);
	}else{
		free(sp -> studentRecord[position]);
		sp -> studentRecord[position] = NULL;
		sp -> flag[position] = Removed;
		sp -> count--;
		printf("Record with ID %d has been removed from the Data Set.\n\n",studentID);
	}		
}