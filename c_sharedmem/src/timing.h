/*
 * timing.h
 *
 *  Created on: May 29, 2009
 *      Author: cmatthew
 */

#ifndef TIMING_H_
#define TIMING_H_

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

/** Holds all the values needed in a resultset*/
typedef struct result_set_t {

	/** the number of elements in this result set.*/
	unsigned int nelements;

	/** space to store nelements worth of start times.*/
	struct timeval* start_times;
	/** space to store nelements worth of end times.*/
	struct timeval* end_times;
} result_set;


/** Print a particular result out to the console in a format that the test
 * program can read.
 * @see timing_print_result_set*/
void timing_report_result( struct timeval *start, struct timeval *end);


/** Make a new result set.
 *
 * This will allocate a new result set (includeing the memory) for NRESUTLS
 * worth of results.
 *
 * @param nresults The size (number of entries) this results set should hold.
 * @return A reference to a newly allocated result set.
 */
result_set * timing_init_resultset(unsigned int nresults);

/**Print this result set out to the console.
 * @see timing_report_result*/
void timing_print_result_set(result_set* r);


/** Start the timer TIMERNO in the result set R.
 * @param r The current result set.
 * @param timerno The timer number in this result set to start.
 * */
void timing_start_timer(result_set* r, unsigned int timerno);


/** Stop the timer TIMERNO in the result set R.
 * @param r The current result set.
 * @param timerno The timer number in this result set to stop.
 * */
void timing_stop_timer(result_set* r, unsigned int timerno);

#endif /* TIMING_H_ */
