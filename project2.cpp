#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int num_threads = 0;
//Arrays to store the mins of threads
int min_arr1[5] = { 0 };
int min_arr2[100] = { 0 };
//Declare and set the array size to 10000
const unsigned int sizeOfArray = 10000;
int numberArray[sizeOfArray];
int numberArray1[5];

//Minimum function for level 2
void *minimum(void *arg) {
	int num = num_threads++;
	int min = 0;
	for (int i = num * (10000 / 100); i < (num + 1) * (10000 / 100); i++) {
		if (numberArray[i] < min) {
			min = numberArray[i];
		}
	}
	min_arr2[num] = min;
  pthread_exit(0);
}

//Minimum function for level 1
void *minimum1(void *arg) {
	int num = num_threads++;
	int min1 = 0;
	for (int i = num; i < (num + 1); i++) {
		if (numberArray1[i] < min1) {
			min1 = numberArray1[i];
		}
	}
	min_arr1[num] = min1;
	pthread_exit(0);
}


int main() {

	//Seed the random system
	srand(time(0));
	//Insert a randomly generated number for each slot in the numberArray
	for (int i = 0; i < sizeOfArray; i++) {
		numberArray[i] = rand();
		//Test code to print out the values in the array
		//std::cout<<numberArray[i]<<std::endl;
	}

	int minl1 = 0;
	int minl2 = 0;
	pthread_t threadsl1[5];
	pthread_t threadsl2[100];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//Keeps track of the joining of 20 threads per level 1 thread
	int counter = 0;

	//Create 20 threads for each level 1 thread
	//100 total level 2 threads
	for (int j = 0; j < 100; j++) {
		pthread_create(&threadsl2[j], &attr, minimum, (void*)NULL);
	}

	//Create the 5 threads for level 1
	for (int i = 0; i < 5; i++) {
		pthread_create(&threadsl1[i], &attr, minimum1, (void*)NULL);

		//Join 20 level 2 threads
		//Wait for all 20 threads to complete
		for (int j = counter; j < (counter + 20); j++) {
			pthread_join(threadsl2[j], NULL);
		}

		//Find min in an array for individual level 2 threads attached to level 1 thread
		for (int j = 0; j < 20; j++) {
			if (min_arr2[j] < minl2) {
				minl2 = min_arr2[j];
			}
		}
		//Place the min of all 20 threads into an array of 5 for the level 1 threads
		min_arr1[i] = minl2;
	}

	//Join the 5 threads
	//Wait for all 5 threads to compelete
	for (int i = 0; i < 5; i++) {
		pthread_join(threadsl1[i], NULL);
	}

	//Find min in an array for individual threads in level 1
	for (int i = 0; i < 5; i++) {
		if (min_arr1[i] < minl1) {
			minl1 = min_arr1[i];
		}
	}

  std::cout<<minl1<<std::endl;

	return 0;
}