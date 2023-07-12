//Anish Katragadda
// Lab 5 - Project 1

//Summary
//The purpose of this weeks lab is to set up a priority queue program 
//Which will be our method of organizing data so that we can then access it with
//Our Huffman tree which we will set up during the next lab

//Library Inclusions
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "pqueue.h"

//Definitions
#define STARTLENGTH 10
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)

//Creation of Struct 
//It keeps tracks of the number of elements it has, the array, the length of the array, 
struct pqueue{
    int count;
    int length;
    void **data;
    int (*compare)();
};

//createQueue
//This function creates our priority queue by allocating memeory and assigning the base values
PQ *createQueue(int (*compare)()){
    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq != NULL);

    pq -> count = 0;
    pq -> length = STARTLENGTH;
    pq -> data = malloc(sizeof(void*)*STARTLENGTH);
    pq -> compare = compare;
    assert(compare != NULL);
    return pq;
}

//destroyQueue
//This function goes one by one free all the data in the array then frees the aray itself, then it will
//free the pointer
void destroyQueue(PQ *pq){
    int i;
    for(i = 0; i < pq -> count; i++){
        free(pq -> data[i]);
    }
    free(pq -> data);
    free(pq);
}

//numEntries
//Returns the count value from the struct which is the number of elements it has
int numEntries(PQ *pq){
    return pq -> count;
}

//addEntry
//This functions adds an element to the end of our array
//But it will first check if adding the element will keep the min-heap
void addEntry(PQ *pq, void *entry){

    assert(pq != NULL && entry != NULL);
    if(pq -> count == pq -> length){
        pq -> data = realloc(pq -> data, sizeof(void*)*pq -> length * 2);
        pq -> length = pq -> length * 2;
    }
    pq -> data[pq -> count] = entry;
    int index = pq -> count;
	while (pq -> compare(pq -> data[index],pq -> data[p(index)]) < 0) {	
		void* temp = pq -> data[p(index)];
		pq -> data[p(index)] = pq -> data[index];					
		pq -> data[index] = temp;
		index=p(index);
	}

    pq -> count++;

}


//removeEntry
//This functions removes the first element in the array
//It will then shift all the other elements over, and will balance the heap
void *removeEntry(PQ *pq) {
	void* root = pq->data[0];									
	int index = 0, smallestIndex = 0;							
	pq->data[index]=pq->data[pq->count-1];						

	
	pq->count--;															
	while (l(index)<pq->count){												
		smallestIndex = l(index);
		if (r(index)<pq->count) {											
			if (pq->compare(pq->data[l(index)],pq->data[r(index)])<0){
				smallestIndex=l(index);
			} else {
				smallestIndex=r(index);
			}
		}
		
		if (pq->compare(pq->data[smallestIndex],pq->data[index])<0) {		
			void* temp = pq->data[smallestIndex];
			pq->data[smallestIndex] = pq->data[index];
			pq->data[index] = temp;
			index=smallestIndex;											
		}
		else {
			break;
		}
	}
	return root;															
}