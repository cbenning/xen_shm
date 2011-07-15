#include <sys/time.h>
#include "timers.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "random_sleep.h"
/*
 * Subtracts tv2 from tv1 and returns difference in usecs
 */
usec difference(struct timeval tv1, struct timeval tv2) {

	struct timeval temp;
#define USEC_PER_SEC 1000000

	timerclear(&temp);
	timersub(&tv1,&tv2,&temp);

	usec rt = (temp.tv_sec * USEC_PER_SEC) + temp.tv_usec;

	return rt;

}

#define NANO_PER_SEC 1000000000l
#define SPEED_FACTOR 1000l
#define FACTOR NANO_PER_SEC / SPEED_FACTOR

/** If isRand is true, sleep for sleep amount of time.*/
void
random_sleep(int isRand, int sleep)
{

	struct timespec requested_time;
	struct timespec actual_time;

	requested_time.tv_sec = 0;
	if (isRand) {
		requested_time.tv_nsec = rand()%(sleep * FACTOR);
	} else {
		requested_time.tv_nsec = (sleep * FACTOR);
	}

	if (nanosleep(&requested_time, &actual_time)) {
		perror("sleep");
	}
}
