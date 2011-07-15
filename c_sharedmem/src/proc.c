/*!
 * \file proc2.c
 *
 * \author Christopher Benninger
 * \date May 22
 *
 * Contains functions for server and client processes
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include "timing.h"
#include "timers.h"
#include "random_sleep.h"
#include "proc.h"

/*!
 * \brief Performs Client Activities
 *
 * Copies a random integer between 1 and 1000 into shared memory space. Waits for signal. If the server process
 * responds with the same number it records the response time.
 *
 * \param shmKey The Key for the shared memory space
 * \param shmLength The size of the shared memory space
 * \param procID The process number between 0 and numProcs-1
 * \param iters The number of transactions each pair should complete before terminating.
 * \return void
 */
void clnProc(int shmKey, int shmLength, int procID, int iters) {

	sem_t* empty;
	sem_t* full;
	sem_t* mutex;

	usleep(100000);

	result_set* timerData;
	timerData = timing_init_resultset(iters);

	int writeCount;
	int shmID;
	void* shm;
	int* shmInt;

	//Initialization
	writeCount = 0;

	//Get SHM reference
	if ((shmID = shmget(shmKey, shmLength, 0666)) < 0) {
		perror("Unable to allocate shared memory space.\n");
		exit(1);
	}

	//Attach SHM segment to memory space
	if ((shm = shmat(shmID, (void *) 0, 0)) == (char *) -1) {
		perror("unable to attach SHM segment to memory space\n");
		exit(1);
	}

	empty = shm;
	full = shm+sizeof(sem_t);
	mutex = shm+(2*sizeof(sem_t));

	//Get integer handle
	shmInt = (int*)(shm+(3*sizeof(sem_t)));

	int startVal = 0;
	int endVal = 0;

	while (writeCount < iters) {

		startVal = (rand() % 1000) + 1;

		//Start Timer
		timing_start_timer(timerData, writeCount);

		sem_wait(empty);
		sem_wait(mutex);

		//CRITICAL SECTION
		shmInt[procID - 1] = startVal;
		shmInt[procID] = 0;
		//printf("PROC-%d> Sent(1): %d.\n", procID, shmInt[procID - 1]);
		//END CRITICAL SECTION

		sem_post(mutex);
		sem_post(full);

		sem_wait(empty);
		sem_wait(mutex);

		//CRITICAL SECTION
		//printf("PROC-%d> Received(3): %d.\n", procID, shmInt[procID]);
		endVal = shmInt[procID];
		shmInt[procID] = 0;
		shmInt[procID - 1] = 0;
		//END CRITICAL SECTION

		sem_post(mutex);
		sem_post(empty);

		//Stop Timer
		timing_stop_timer(timerData, writeCount);


		//Record and report
		writeCount++;

		if(startVal != endVal){

			printf("Wrong Value Returned!");
			break;

		}

	}

	sem_wait(empty);
	sem_wait(mutex);
	//CRITICAL SECTION
	shmInt[procID - 1] = -1;
	shmInt[procID] = 0;
	//END CRITICAL SECTION
	sem_post(mutex);
	sem_post(full);

	timing_print_result_set(timerData);

	//printf("PROC-%d> Terminating.\n", procID);
	exit(0);

}

/*!
 * \brief Performs Server Activities
 *
 * Receives an integer in the shared memory space. Copying the integer to the next memory space
 * and wiping the original space back to 0
 *
 * \param shmKey The Key for the shared memory space
 * \param shmLength The size of the shared memory space
 * \param procID The process number between 0 and numProcs-1
 * \return void
 */
void srvProc(int shmKey, int shmLength, int procID) {

	sem_t* empty;
	sem_t* full;
	sem_t* mutex;

	int writeCount;
	int shmID;
	void* shm;
	int* shmInt;

	//Initialization
	writeCount = 0;

	//Get SHM reference
	if ((shmID = shmget(shmKey, shmLength, 0666)) < 0) {
		perror("Unable to allocate shared memory space.\n");
		exit(1);
	}

	//Attach SHM segment to memory space
	if ((shm = shmat(shmID, (void *) 0, 0)) == (char *) -1) {
		perror("unable to attach SHM segment to memory space\n");
		exit(1);
	}

	empty = shm;
	full = shm+sizeof(sem_t);
	mutex = shm+(2*sizeof(sem_t));

	//Get integer handle
	shmInt = (int*)(shm+(3*sizeof(sem_t)));

	while (1) {

		sem_wait(full);
		sem_wait(mutex);

		//if(shmInt[procID] > 0 && shmInt[procID + 1] == 0) {

		if(shmInt[procID]<0) {
			//printf("PROC-%d> Terminating, returned %d times.\n",procID,writeCount);
			exit(0);
		}

		//CRITICAL SECTION
		shmInt[procID+1] = shmInt[procID];
		//printf("PROC-%d> Returning(2): %d.\n",procID,shmInt[procID]);
		shmInt[procID] = 0;
		//END CRITICAL SECTION
		writeCount++;
		//}

		sem_post(mutex);
		sem_post(empty);


	}
exit(0);
}

