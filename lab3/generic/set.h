/*
 * File:        set.h
 *
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for generic
 *              pointer types.  A set is an unordered collection of
 *              distinct elements.
 */

# ifndef SET_H
# define SET_H

typedef struct sets SET;

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)());

void destroySet(SET *p);

int numElements(SET *p);

void addElement(SET *p, void *elt);

void removeElement(SET *p, void *elt);

void *findElement(SET *p, void *elt);

void *getElements(SET *p);

# endif /* SET_H */
