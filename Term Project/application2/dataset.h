//Anish Katragadda
//COEN 12 - Spring 2023
//Term Project Application 2 - dataset.h


# ifndef DATASET_H
# define DATASET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"

typedef struct record RECORD;

typedef struct set SET;

SET* createSet(int);

int searchID(SET*,int,bool*);

void destroySet(SET*);

void addElement(SET*,int,int);

void removeElement(SET*,int);

# endif