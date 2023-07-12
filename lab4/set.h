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

typedef struct set SET;

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)());

void destroySet(SET *lp);

int numElements(SET *lp);

void addElement(SET *lp, void *elt);

void removeElement(SET *lp, void *elt);

void *findElement(SET *lp, void *elt);

void *getElements(SET *lp);

# endif /* SET_H */
