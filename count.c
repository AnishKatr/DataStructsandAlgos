//Anish Katragadda
//COEN 12L Thursday 9:15AM 4/6/2023
//Lab1
// Summary - This lab is to count the total words on a text file

//Library Inclusions
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Max Word Length
#define MAX_WORD_LENGTH 30


//main function
int main(int argc, char *argv[]){


        //if there is no file name it will end program and inform user
        if(argc == 1){
            printf("The name of the file isn't there\n");
            return 1;
        }

        //creates file pointer
        FILE *fp;

        //opens file and checks if it opened correctly
        fp = fopen(argv[1], "r");
        if(fp == NULL){
            printf("error opening file");
            return 1;
        }

        //counter variable, and creates char temp array to allow fscanf to scanf each word at a max length of 30 + 1 NULL byte
        int counter = 0;
        char temp[MAX_WORD_LENGTH + 1];
        

        //fscanf scans in each word and then moves on to the next, it scans one word at a time
        while((fscanf(fp,"%s", temp)) == 1){
            counter++;
            
        }

        //Prints total number of words
        printf("The Number of words is %d \n", counter);

        //closes file
        fclose(fp);
        return 0;
}