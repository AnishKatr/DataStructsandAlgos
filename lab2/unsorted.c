//Anish Katragadda
//Coen 12 Lab 2 Part 1 - Unsorted
//April 2023


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "set.h"


//Defining a Set for the program, which hold the number of elements, Length of the Array, and the array for strings

typedef struct sets{

    int count;
    int length;
    char **data;

}SET;


//The CreateSet Function; This function has a time complexity of O(1)
// This function starts by allocation memory, and records the number of elements, length of the array, and the array itself
SET *createSet(int maxElts){

    SET *p;

    p = malloc(sizeof(SET));
    assert(p != NULL);

    p -> count = 0;
    p -> length = maxElts;
    p -> data = malloc(sizeof(char*)*(p -> length));

    assert(p -> data != NULL);
    p -> count = 0;
    return p;



}



//the search function; This function has a time complexity of O(n)
//This function will linearly searches through the index and return the index where it is
//If the element is not found it will return negative 2
// It must return any negative number since any number 0 and greater would unintentionally return an inded even if the element isnt found
static int search(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);
    int i = 0;

    for(i = 0; i < p -> count; i++){
        if(strcmp(p -> data[i], elt)==0){
            return i;
        }

    }

    return -2;
}



//The Function destroySet; This function has a time compeltexity of O(n)
//This function starts by clearing the memory at each index of the array using the free function - emptying the array
// Then it will clear the array itself, then before it returns out of the function will clear the set
void destroySet(SET *p){

    assert(p!= NULL);
    int i;
    for(i = 0; i < p -> count; i++){

        free(p-> data[i]);

    }

    free( p -> data);
    free(p);

    return;
}


//The numElements Function; This function has a time complexity of O(1)
//This function returns the Number of Elements by returning the count variable in the set
int numElements(SET *p){

    assert( p != NULL);
    return p -> count;

}



//The removeElement Function; this function has a time complexity of O(n)
//This function will linearly look through the set for the element, and if the element is not found
//The function will add the element to the end of the set, the increment the count of elements
void addElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);
    if (search(p, elt) == -2){
        p -> data[p -> count] = strdup(elt);
        assert( p-> data[p->count] != NULL);
        p -> count++;
    } 

}

//The removeElement Function; this function has a time complexity of O(n)
//This function will linearly look through the set for the element, and if found will free the memory then place the final element into that slot
void removeElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);

    int index;
    index = search(p,elt);

    if ( index != -2){

        free(p->data[index]);

        p -> data[index] = p -> data[p -> count - 1];
        p -> count--;

    }


}

//The findElement Function; this function has a time complexity of O(n)
//This function will linearly look through the set for the element, and will return it if found, otherwise it will return NULL
char *findElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);

    int i;
    for(i = 0; i < p-> count; i++){

        if(strcmp(p->data[i], elt) == 0){
            
            return elt;

        }

    }

    return NULL;

}

//the getElements function; This function has a time complexity of O(n)
//This function returns a copy of the array
//Originally I used a forloop to return the array using strdup but switch it to use memcpy

char **getElements(SET *p){

    assert( p != NULL);

    char **x;
    x = malloc((sizeof(char*)*p -> count));

    assert(x != NULL);

    memcpy(x, p -> data, (sizeof(char*)*p -> count));

    return x;

}

