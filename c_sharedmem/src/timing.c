/*
 * timing.c
 *
 *  Created on: May 29, 2009
 *      Author: cmatthew
 */
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "timers.h"
#include "timing.h"


//how do we distinguish the output?
const char * marker = "";

void
timing_report_result( struct timeval *start, struct timeval *end)
{
	usec val = difference(*end, *start);

	printf("%s %lu.%06lu %lu.%06lu %lu\n", marker,
										start->tv_sec,
										start->tv_usec,
										end->tv_sec,
										end->tv_usec,
										val);
}

void timing_print_result_set(result_set* r) {
	int i = 0;
	for (i = 0; i < r->nelements; i++) {
		timing_report_result(&(r->start_times[i]), &(r->end_times[i]));
	}

}


result_set * timing_init_resultset(unsigned int nresults) {


	result_set* r = calloc(sizeof(result_set), 1);

	r->nelements = nresults;

	r->start_times =
			(struct timeval*) calloc(sizeof(struct timeval), nresults);

	r->end_times = (struct timeval*) calloc(sizeof(struct timeval),nresults);

	return r;
}


inline void timing_start_timer(result_set* r, unsigned int timerno){
	gettimeofday(&(r->start_times[timerno]), NULL);
}


inline void timing_stop_timer(result_set* r, unsigned int timerno) {
	gettimeofday(&(r->end_times[timerno]), NULL);
}

void timing_destroy_resultset(result_set * r) {

	free(r->start_times);
	free(r->end_times);
	free(r);
}
