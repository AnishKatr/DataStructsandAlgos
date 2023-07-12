//Anish Katragadda
//Coen 12 Lab - 4
//Labe 4 Part 1 - Lists
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

//Defines the structures for the nodes of the linked lists
typedef struct node{
    void *data;
    struct node *next;
    struct node *prev;
}NODE;

//Degines thr structure for the LIST
typedef struct list{
    int count;
    struct node *head;
    int(*compare)();
};

//This function will create the list and then will return a pointer to the location of this linked list
//It also establishes a dummy node, and a counter to count all the elements which the dummy node is not a part of
LIST *createList(int (*compare)()){

    LIST *lp;
    lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp -> head = malloc(sizeof(struct node));
    assert(lp -> head != NULL);

    lp -> count = 0;
    lp -> compare = compare;
    lp -> head -> next = lp -> head;
    lp -> head -> prev = lp -> head;

    
    return lp;

};

//The Destroy List Function
//This function will call the remove the last node function and continuosly wipe the nodes
//Till there are no more left and the count hits 0
void destroyList(LIST *lp){
    assert(lp != NULL);
    while(lp -> count > 0){
        removeLast(lp);
    }
}

//NumItems functions
//Will return the count of the number of items that are a part of the list
int numItems(LIST *lp){
    assert(lp != NULL);
    return lp -> count;
}

//addFirst function
//This function inserts a node into to the list at the start of the list then will increment the counter
void addFirst(LIST *lp, void *item){
    
    assert(lp != NULL);
    struct node *newNode = malloc(sizeof(struct node));
    assert(lp != NULL);

    newNode -> data = item;
    newNode -> next = lp -> head -> next;
    newNode -> prev = lp -> head;
    lp -> head -> next -> prev = newNode;
    lp -> head -> next = newNode;

    lp -> count++;

}


//addLast Function
//This function will add a node to the end of the list, then it will increment the counter
void addLast(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE *Add = malloc(sizeof(NODE));              
    assert(Add != NULL);

    Add->data = item;
    lp->head->prev->next = Add;                    
    Add->next = lp->head;                          
    Add->prev = lp->head->prev;                    
    lp->head->prev = Add; 

    lp->count++;                                    
    return;
}

//removeFirst function
//This function will remove the first element of the list
//This is done by creating temporary pointer that assigns the new head to the following node
//Then will remove the node from the list and free the pointer and data
//Then it will decrement the counter
void *removeFirst(LIST *lp) {
    assert(lp != NULL);
    NODE *Del = lp->head->next;
    void *temp = Del->data;
    lp->head->next = Del->next;                    
    Del->next->prev = lp->head;                    
    free(Del);                                     
    lp->count--;
    return temp;
}

//removeLast Function
//removeFirst function
//This function will remove the Last element of the list
//This is done by creating a temporary pointer which is then assigned the the node before the head since it is a circularly doubly linked list
//Then will remove the node from the list and free the pointer and data
//Then it will decrement the counter
void *removeLast(LIST *lp){

    assert(lp -> count > 0);

    struct node *lastNode = lp -> head -> prev;
    void *lastData = lastNode -> data;
    lastNode -> prev -> next = lp -> head;
    lp -> head -> prev = lastNode -> prev;
    free(lastNode);
    lp -> count--;

    return lastData;


}

//getFirst Function
//This function will return the data of the first node of the function
void *getFirst(LIST *lp){
    assert(lp -> count > 0);
    return lp -> head -> next -> data;
}

//getLast Function
//This function will return the data of the Last node of the function
void *getLast(LIST *lp){
    assert(lp -> count > 0);
    return lp -> head -> prev -> data;
}

//removeItem Function
//given the linked list and data, this function will traverse the list free the node containing that data
//but will make sure  the connected nodes are then connected to eachother so no data is list
//it will then decrement the counter since an element is removed
void removeItem(LIST *lp, void *item){

    assert(lp -> compare != NULL && lp -> count > 0 && item != NULL);
    int i;
    struct node *caseNode = lp -> head -> next;
    for(i = 0; i < lp -> count; i++){
        if(lp -> compare(caseNode -> data, item) == 0){
            caseNode -> prev -> next = caseNode -> next;
            caseNode -> next -> prev = caseNode -> prev;
            free(caseNode);
            lp -> count--;
            break;
        }else{
            caseNode = caseNode -> next;
        }
    }

}

//findItem Function
//this function returns the data of a node if it matches the data that the function is provided with
//otherwise it will return NULL
void *findItem(LIST *lp, void *item){
    assert(lp -> compare != NULL);
    assert(item != NULL);
    int i;
    struct node *caseNode = lp ->head -> next;
    for(i = 0; i < lp -> count; i++){
        if(lp -> compare(caseNode -> data, item) == 0){
            return caseNode -> data;
        }
        caseNode = caseNode -> next;
    }
    
    return NULL;

}

//getItems Function
//This function will return an array with all the data
void *getItems(LIST *lp) {
    assert(lp != NULL);
    int i = 0;
    void **temp;
    NODE *node = lp->head->next;
    temp = malloc(sizeof(void *)*lp->count);
    assert(temp != NULL);
    while(i < lp->count && node != lp->head) {
        temp[i] = node->data;
        node = node->next;
        i++;
    }
    return temp;
}

