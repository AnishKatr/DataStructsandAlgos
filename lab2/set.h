/*
 * File:        set.h
 *
 * Copyright:	2021, Darren C. Atkinson
 *
 * Description: This file contains the public function and type
 *              declarations for a set abstract data type for strings.  A
 *              set is an unordered collection of distinct elements.
 */

# ifndef SET_H
# define SET_H

typedef struct sets SET;

SET *createSet(int maxElts);

void destroySet(SET *sp);

int numElements(SET *sp);

void addElement(SET *sp, char *elt);

void removeElement(SET *sp, char *elt);

char *findElement(SET *sp, char *elt);

char **getElements(SET *sp);

# endif /* SET_H */
