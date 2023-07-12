//Anish Katragadda
//Coen 12 Lab 3 Part 1 - Strings
//May 2023


//Program Description:
//This program implements sets, and hashing methods to store and organize data
//The Program can Create and Destroy Sets, Search using linear probing, Add or Remove Elements, Find Elements
// And Return Copies of the array


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define CLEARED 2

//Defining a Set for the program, which hold the number of elements, Length of the Array, and the array for strings
typedef struct sets{

    int count;
    int length;
    char **data;
    char* flags;

}SET;


//Str Hash Function
//This is the Hash Function for our set of data. For each item of data it should assign a unique hash value
//This Function has a Runtime of O(1)
unsigned strhash(char *s){

    unsigned hash = 0;
    while( *s != 0){
        hash = 31 * hash + *s++;
    }

    return hash;
}


//The CreateSet Function;
//This function had a time complexity of O(n)
// This function creates a set to keep a count of the number of elements, and then
//Create an array with the data and an array called flags which would be empty
SET *createSet(int maxElts){

    SET *p;
    int i;

    p = malloc(sizeof(SET));
    assert(p != NULL);

    p -> count = 0;
    p -> length = maxElts;
    p -> data = malloc(sizeof(char*)*(p -> length));
    p -> flags = malloc(sizeof(char)*(p -> length));

    for(i = 0; i < maxElts; i++){

        p -> flags[i] = EMPTY;

    }

    assert(p -> data != NULL);
    p -> count = 0;
    return p;



}


//The Search Function; This function has a time complexity of O(n) but it is possible to be O(1)
// This function uses the concept of Linear Probing to search through the array, this is because
// since we stored the data using a hash function the search has to check our flag array which will identify where the elements are
// And then let the function know weather or not the space is empty due to a deletion, or since it had not been filled yet.

static int search(SET *p, char *elt, bool *found){

    int head = strhash(elt) % p -> length;
    int i, index;
    int deletedindex = -1;
    for( i = 0; i < p-> length; i++){

        index = (head + i) % p -> length;
        if(p -> flags[index] == FILLED){

            if((strcmp( p -> data[index], elt)) == 0){
                
                *found = true;
                return index;

            }

        } else if( p -> flags[index] == CLEARED){

            if( deletedindex == -1){

                deletedindex = index;

            }

        } else{
            break;
        }

    }

    *found = false;
    if(deletedindex == -1){

        return index;

    }
    return deletedindex;
}


//The Function destroySet; This function has a time compeltexity of O(n)
//This function starts by clearing the memory at each index of the array using the free function - emptying the array
// Then it will clear the array itself, then before it returns out of the function will clear the set
void destroySet(SET *p){

    assert(p!= NULL);
    int i;
    for(i = 0; i < p -> length; i++){

        if( p -> flags[i] == FILLED){

            free(p-> data[i]);

        }

    }

    free(p -> data);
    free(p -> flags);
    free(p);

    return;
}



//The numElements Function; This function has a time complexity of O(1)
//This function returns the Number of Elements by returning the count variable in the set

int numElements(SET *p){

    assert( p != NULL);
    return p -> count;

}



//The addElement Function; This function has a time complexity of O(n)
// The addElement function will call upon the search function to find weather or not an element had been stored already
//If it is not found, then the function will store the element and adjust the flag array to filled at that index
// The function has the ability to have an O(1) runtime
void addElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);
    bool looked;
    int index, i;
    index = search(p, elt, &looked);
    if( looked == false){

        p -> data[index] = strdup(elt); 
        p -> flags[index] = FILLED;
        p -> count++;

    }


}


// The removeElement Function; This function has a time complexity of O(n)
// The removeElement function will call upon the search function to find weather the element is in the array
// If it is found it will then remove the element and create a Tombstone in the flag array
// The function has the ability to have an O(1) runtime
void removeElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);

    bool looked;
    int index, i;
    index = search(p, elt, &looked);
    if(looked == true){
        free(p -> data[index]);
        p -> flags[index] = CLEARED;
        p -> count--;
    }


}


//The function findElement; this function has a time complexity of O(n)
// The findElement function will call upon the search function and if found it will return the element itself
//otherwise it will return NULL
// The function has the ability to run in O(1)
char *findElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);
    bool looked;
    int index;
    index = search(p, elt, &looked);

    return(looked ? elt:NULL);

}


//the getElements function; This function has a time complexity of O(n)
//This function returns a copy of the array
char **getElements(SET *p){

    int i = 0;
    int end = 0;

    assert( p != NULL);

    char **x;
    x = malloc((sizeof(char*)*p -> count));

    assert(x != NULL);

    for( i = 0; i < p -> length; i++){

        if( p -> flags[i] == FILLED){

            x[end] = p -> data[i];
            end++;

        }

    }


    return x;

}

