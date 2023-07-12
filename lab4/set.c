//Anish Katragadda
//Coen 12 Lab - 4
//Labe 4 Part 2 - Sets and Hash Table Chaining
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
#include "set.h"
#define AVG 20

//This defines what the set for this program will includes
//Which is a count for the number of elements
//The length of the array
//and array of strings
// a compare function
//and a hashing function
typedef struct set{
    int count;
    int length;
    LIST **lists;
    int(*compare)();
    unsigned(*hash)();
}; 

//createSet Function
//This function creates a set, by allocating the memory, then establishes a counter, the length of the array, and lists
SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)()){

    SET *lp;
    lp = malloc(sizeof(SET));
    assert(lp != NULL);
    int i;

    lp -> count = 0;
    lp -> length = maxElts/AVG;
    lp -> lists = malloc(sizeof(void*)*lp -> length);
    lp -> compare = compare;
    lp -> hash = hash;
    for ( i = 0; i < lp -> length; i++){
        lp -> lists[i] = createList(compare);
    }    

    assert(lp -> lists != NULL);
    return lp;

}

//The destroySet Function
//This function will free the pointer pointing to the lists
//then the pointer will be freed
void destroySet(SET *lp){
    free(lp -> lists);
    free(lp);
}

//NumElements functions
//Will return the count of the number of elements that are a part of the set
int numElements(SET *lp){
    assert(lp != NULL);
    return lp -> count;
}

//addElement Function
//The function will first establish our hashing location
//Then it will call the findItem function to check if there is space in the array at that location
//If there is it will add to the list and increment the counter
void addElement(SET *lp, void *elt){
    assert(lp != NULL && elt != NULL);
    int index = (*lp -> hash)(elt) % lp -> length;
    if(findItem(lp -> lists[index], elt) == NULL){
        addFirst(lp -> lists[index], elt);
        lp -> count++;
    }
}

//removeElement Function
//The function will first establish our hashing location
//Then it will call the findItem function to check if there is a specific element
//If there is it will remove from the list and decrement the counter
void removeElement(SET *lp, void *elt){

    assert(lp != NULL && elt != NULL);
    int index = (*lp -> hash)(elt) % lp -> length;
    if(findItem(lp -> lists[index], elt) != NULL){
        removeItem(lp -> lists[index], elt);
        lp -> count--;
    }

}

//findElement Function
//This function will return the element if it is found otherwise it will return null
void *findElement(SET *lp, void *elt){
    assert(lp != NULL && elt != NULL);
    int index = (*lp -> hash)(elt) % lp -> length;
    return findItem(lp -> lists[index], elt);
}


//getElements Function
//This function will return a copy of the array for the user
void *getElements(SET *lp){

	assert(lp!=NULL);
	int i,j=0;
	void **array=malloc(sizeof(void*)*(lp->count));
	for(i=0;i<lp->length;i++)
	{
		memcpy(array+j,getItems(lp->lists[i]),sizeof(void*)*numItems(lp->lists[i]));
		j+=numItems(lp->lists[i]);
	}
	return array;


}