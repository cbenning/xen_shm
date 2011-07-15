/*!
 * \file main2.c
 *
 * \author Christopher Benninger
 * \date May 22
 *
 * Main file of project
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include "main.h"
#include "proc.h"

/*!
 * \brief entry point
 *
 * puts commandline args into aplication
 *
 * \param argc The number of params
 * \param arvg[] Array of params
 */
int main(int argc, char *argv[]){

	if(argc!=2){
		printf("Two Parameters Required.\n");
		printf("Usage: proctest <iterations>\n");
	//	printf("<process_pairs> - How many producer/consumer pairs to generate\n");
		printf("<iterations> - Number of transactions each pair will complete\n");
		printf("Exiting.\n");
		exit(0);
	}

	//int pairs = atoi(argv[1]);
	int runs = atoi(argv[1]);
	int pairs = 1;

	init(pairs,runs);
	exit(0);
}

/*!
 * \brief Sets up the test environment
 *
 * Sets up the test environment and spawns the processes. Waits for them to finish before terminating
 *
 * \param numPairs The number of producer/consumer pairs to create
 * \param iter The number of transactions each pair should complete before terminatin.
 * \return void
 */
void init(int numPairs, int iter){


	sem_t* empty;
	sem_t* full;
	sem_t* mutex;

	unsigned int emptyVal = 1;
	unsigned int fullVal = 0;
	unsigned int mutexVal = 1;

	//SHM addrs ID
	int shmID;

	//SHM Pointer
	void* shm;
	int* shmInt;
	int shmKey;

	shmKey = ftok("proctest",1);

	int shmLength;
	shmLength = ((sizeof(int)*numPairs*2)+(3*sizeof(sem_t)));

	//Setup SHM Segment
	if ((shmID = shmget(shmKey, shmLength, IPC_CREAT | 0666)) < 0){
        perror("Unable to allocate shared memory space.\n");
        exit(1);
	}

	//Attach SHM segment to memory space
	if ((shm = shmat(shmID, (void *)0, 0)) == (char *) -1) {
		perror("unable to attach SHM segment to memory space\n");
		exit(1);
	}

	empty = shm;
	full = shm+sizeof(sem_t);
	mutex = shm+(2*sizeof(sem_t));

	//Default last param
	sem_init(empty,1,emptyVal);
	sem_init(full,1,fullVal);
	sem_init(mutex,1,mutexVal);

	//Put zeroed int array into SHM
	int k;
	shmInt = (int*)(shm+(3*sizeof(sem_t)));

	for(k = 0; k < numPairs*2 ; k++){
		shmInt[k] = 0;
	}

	/**************************
	//Fire up processes
	**************************/
	int i = 0;
	pid_t pid = 0;
	while( i < numPairs*2 ){
		//printf("MASTER> Creating Process %d\n",i);
		//Fork Server
		pid = fork();
		if(pid==0){
			srvProc(shmKey,shmLength, i);
		}
		else if(pid<0){
			printf("MASTER> Failed to Create Process %d\n",i);
			exit(1);
		}
		else{
			i++;

		}

		//printf("MASTER> Creating Process %d\n",i);
		//Fork Client
		pid = fork();
		if(pid==0){
			clnProc(shmKey,shmLength, i, iter);
		}
		else if(pid<0){
			printf("MASTER> Failed to Create Process %d\n",i);
			exit(1);
		}
		else{
			i++;
		}

	}

	int j = 0;
	while( j < numPairs*2 ){
		wait(NULL);
		j++;
	}

	sem_destroy(empty); /* destroy semaphore */
	sem_destroy(full); /* destroy semaphore */
	sem_destroy(mutex);

	//printf("Experiment Finished\n");

	exit(0);
}


