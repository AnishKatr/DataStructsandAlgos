//Anish Katragadda
//Coen 12 Lab 2 Part 2 - Sorted
//April 2023


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
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


//The Search Function; This function has a time complexity of O(logn)
// This function uses the process of binary search, using the three bounds lower avg being the middle, and high being the upper
// This function will use the temp to compare the strings and depending on the value returned will adjust the bounds

static int search(SET *p, char *elt, bool *found){

    int low, avg, high, temp;

    low = 0;
    high = p -> count - 1;
    while(low <= high){

        avg = (low + high)/2;
        temp = strcmp(elt, p -> data[avg]);
        if (temp < 0){

            high = avg - 1;

        }else if(temp > 0){
            
            low = avg + 1;

        }else{

            *found = true;
            return avg;
        }

    }


    *found = false;
    return low;
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



//The addElement Function; This function has a time complexity of O(n)
//This function checked wheather an element has been found, if the element has not been found it will 
//then shift all the elements 
//We assign the empty spot to a duplicated string using strdup
void addElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);
    bool looked;
    int index, i;
    index = search(p, elt, &looked);
    if( looked == false){
        for(i = p -> count; i > index; i--){

            p -> data[i] =  p -> data[i - 1];

        }
        p -> data[index] = strdup(elt); 
        p -> count++;
    }


}


//The function removeElement; This function has a time complexity of O(n)
//Uses search to find the specific element, then if found will use free to clear that index and shift all the data
//to the left to fill in that empty slot
void removeElement(SET *p, char *elt){

    assert( p != NULL);
    assert( elt != NULL);

    bool looked;
    int index, i;
    index = search(p, elt, &looked);
    if(looked == true){
        free(p -> data[index]);
        for(i = index + 1;i < p -> count; i++){
            p -> data[i -1] = p -> data[i];
        }
        p -> count--;
    }


}


//The function findElement; this function has a time complexity of O(logn)
// This function will use the search function and either return the element or NUll depending on whether it was found or not
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
//Originally I used a forloop to return the array using strdup but switch it to use memcpy
char **getElements(SET *p){

    assert( p != NULL);

    char **x;
    x = malloc((sizeof(char*)*p -> count));

    assert(x != NULL);

    memcpy(x, p -> data, (sizeof(char*)*p -> count));


    return x;

}

