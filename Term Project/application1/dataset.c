#include"data.h"


struct student{ // This is the structure that defines what eachs tudent will have esentially
	int age;
	int id;

	STUDENT *next;
	STUDENT *prev;
};


struct class_year{
	LIST **lists;//pointer to an array of data

	int count;//count of total number of students
	int length;//this integers holds the lengeth of tthe student array
	int maxClassSize;//number that represents the maximum students allowed
};

struct list{
	int count;
	STUDENT *head;
};



//createSet Function
//This function will create the set of our data, and the maximum students is provided as an arg
//Then when it is complete will return a pointer to the set
//This function runs at O(1)
SET* createSet(int maxStudents){
	int i;
	SET *setp;
	setp = malloc(sizeof(SET));
	assert(setp != NULL);
	setp -> maxClassSize = maxStudents;
	setp -> count = 0;
	setp -> length = 13;
	setp -> lists = malloc(sizeof(LIST *)*13);
	assert(setp -> lists != NULL);
	for(i = 0;i < 13;i++){//creates a trash node for each of the lists
		setp -> lists[i] = malloc(sizeof(LIST));
		setp -> lists[i] -> head = malloc(sizeof(STUDENT));
		assert(setp -> lists[i] != NULL && setp -> lists[i] -> head != NULL);
		setp -> lists[i] -> head -> prev = setp -> lists[i] -> head;
		setp -> lists[i] -> head -> next = setp -> lists[i] -> head;
		setp -> lists[i] -> head -> id = -1;
		setp -> lists[i] -> count = 0;
	}
	return setp;
}

//destroySet Function
//This function clears the set, then frees all memory allocated
//This Function runs at O(n)
void destroySet(SET *setp){
	assert(setp != NULL);
	int i,j;
	for(i = 0;i < 13;i++){
		if(setp -> lists[i] -> count > 0){
			
			STUDENT *pDel;
			STUDENT *pNext;
			pDel = setp -> lists[i] -> head;
			do{
				pNext = pDel -> next;
				free(pDel);
				pDel = pNext;
			}
			while(pDel != setp -> lists[i] -> head);
		}else{//If the list is empty will free our trash node
			free(setp -> lists[i] -> head);
		}
	}
	free(setp -> lists);
	free(setp);
	return;
}



//searchAge Function
//This function will search for the student age provided as an arg
//This function runs at O(n) - since we print at each found age, but the searching process is O(1)
void searchAge(SET *setp, int age){
	assert(setp != NULL);
	int index = findIndex(setp, age);
	if(index == -1){
		printf("there are no students enrolled with that age: %d \n", age);
	}else{
		//found the list of sought ages, indexed by variable index
		STUDENT *p;
		p = setp -> lists[index] -> head;
		p = p -> next;
		//print off all the students with that age
		printf("\n\nWe Will now Remove Students whose age is = %d \n", age);
		while(p != setp -> lists[index] -> head){
			printf("student id: %d student age: %d was found \n",p -> id,p -> age);
			p = p -> next;
		}
	}
	return;
}

//findIndex Function
//This function will return the index of the lists if the age we are looking for is found
//Otherwise it will return -1 Fucntion runs at O(1)
int findIndex(SET *setp,int age){
	if(age > 30|| age < 18){
		return -1;
	}
	int index = age % 18;

	if(setp -> lists[index] -> count > 0){
		return index;
	}else{
		return -1;
	}
}

//insertion Function
//This function inserts students into the data structure at a runtime of O(1)
void insertion(SET *setp,int insertID,int insertAge){
	assert(setp != NULL);
	if(insertAge < 18||insertAge > 30){
		printf("invalid age for entry \n");
		return;
	}
	int index = insertAge % 18;
	STUDENT *temp;
	temp = malloc(sizeof(STUDENT));
	assert(temp != NULL);
	temp -> age = insertAge;
	temp -> id = insertID;
	temp -> prev = setp -> lists[index] -> head;
	temp -> next = setp -> lists[index] -> head -> next;
	setp -> lists[index] -> head -> next = temp;
	setp -> lists[index] -> count++;
	setp -> count++;
	printf("Added student : %d age %d \n",insertID, insertAge);
	return;
}

//deletion Function
//This function when called will delete all the Id's with the age which is provided as an arg
//runs at O(1)
void deletion(SET *setp,int ageInput){
	assert(setp != NULL);
	if(ageInput < 18||ageInput > 30){
		printf("deletion request not complete, age not found \n");
		return;
	}
	int index = findIndex(setp,ageInput);
	if(index == -1){
		printf("no students ewith corresponding age \n");
		return;
	}
	STUDENT *pDel = setp -> lists[index] -> head -> next;
	printf("\n\nWe Will now Remove Students whose age is = %d \n",ageInput);
	while(pDel != setp -> lists[index] -> head){
		setp -> lists[index] -> head -> next = pDel -> next;
		printf("student : %d  Age : %d was deleted \n",pDel -> id,index + 18);
		free(pDel);
		pDel = setp -> lists[index] -> head -> next;
		setp -> count--;
	}
	setp -> lists[index] -> count = 0;
	setp -> lists[index] -> head -> next = setp -> lists[index] -> head;
	setp -> lists[index] -> head -> prev = setp -> lists[index] -> head;
	return;
}

//maxAgeGap
//This function will find the maximum age gap between all the individual students
//runs at O(1)
int maxAgeGap(SET *setp){
	int min = 0;
	int max = 12;
	while(setp -> lists[min] -> count == 0){
		min++;
		if(min > 12){
			printf("list is empty\n");
			return -1;
		}
	}
	while(setp -> lists[max] -> count == 0){
		max--;
	}
	printf("max age gap between students = %d years \n",max - min);
	return max - min;
}