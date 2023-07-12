//Anish Katragadda
//COEN 12 - Spring 2023
//Term Project Application 2 - college.c

//The purpose of this program is a soultion to application 2 of the Term Project
//This program creates an array of studenRecord pointers which have the 
//ID number and age for it's respective student. Which is then inserting into our SET
//This set for each student has a age from 18 - 30 years old, and a ID number from 1-2000
//This application provided to us told us we need to create a program oriented towards frequent
//searches, which means our most effective method would be to using a form of a hash table to store
//our data  after insertion calling the searchID function which will look and find the ID which we have
//generated randomly If found it will return that it has been found, otherwise will return the not found
//After this is done
//It then will randomly generate an ID again it which it will search for then call our removeElements
//function to remove all of the ID's with the corresponsing age.
//Then it will free all the memory we have allocated to run the program, and end

//Function code is in dataset.c, college.c call our function through the main function


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <time.h>
# include "dataset.h"



struct record{
	int ID; //Student ID which is a unique Integer value from 1 - 2000
	int Age; //Age randomly generated for each student between 18 - 30
};



struct set{
	int count;//Number of Elements in our data structure
	int length;//The maximum students/records we can have in our SET

	RECORD** studentRecord; //Creates a pointer to the first pointer in the arrya of studentRecord pointers
	char *flag;//Points to the first flag in our rray of flags, which we need to implement a hash table
}; 

//Our main function
int main(){
	SET* dataSet;
	dataSet = createSet(3001); 
	printf("Data Set Created\n");
	srand ((int) time (NULL));
	int previousID = 0;
	int i = 0;
	for(i = 0; i < 1000; i++){
			int studentAge = rand()%(13) + 18;//random age generation
			int ID = rand() % 2 + 1;
			previousID = previousID + ID;
			addElement(dataSet,previousID,studentAge);
	}
	printf("All records successfully inserted into Data Set.\n");
	int testID = rand()%(1999) + 1;
	bool found = false;


	int removeID = rand()%(1999) + 1;
	removeElement(dataSet,removeID);
	printf("All operations complete, freeing memory of Data Set.\n");

	destroySet(dataSet);	
}