#include"data.h"

#define MAXSTUDENTS 3000

int ID = 0;

int main()
{
	SET *set;
	set = createSet(MAXSTUDENTS);
	srand(time(NULL));
	int studentNumber = 0;
	int randomID;
	int randomAge;

	//generate 1000 student records the insertion runs at O(n)
	while(studentNumber < 1001){

		randomID = (rand() % 2) + 1;
		randomAge = (rand() % 13) + 18;
		ID += randomID;
		insertion(set,ID,randomAge);
		studentNumber++;
	}
	//generate random student and try to find it
	randomAge = (rand() % 13) + 18;
	randomID = (rand() % 2000);
	searchAge(set,randomAge);

	//After searching for a random age we will generate a new age which will now remove from our SET
	randomAge=(rand() % 13) + 18;
	printf("\n %d The Age we are going to search for and delete is: \n",randomAge);
	deletion(set,randomAge);

	//Finds the maximum age gap between the student ID numbers
	maxAgeGap(set);
	
	destroySet(set);

}