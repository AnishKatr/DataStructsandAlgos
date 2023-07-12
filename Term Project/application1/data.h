#ifndef DATA_H
#define DATA_H


#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

typedef struct student STUDENT;
typedef struct class_year SET;
typedef struct list LIST;


SET* createSet(int maxStudents);
void destroySet(SET *p);
void searchAge(SET *p,int age);
void insertion(SET *p, int insertID,int insertAge);
void deletion(SET *p, int deleteAge);
int maxAgeGap(SET *p);
int findIndex(SET *p,int age);



#endif