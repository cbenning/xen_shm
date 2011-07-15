#ifndef TIMERS_H_
#define TIMERS_H_

#include <sys/time.h>

#define timerisset(tvp)\
((tvp)->tv_sec || (tvp)->tv_usec)

#define timerclear(tvp)\
((tvp)->tv_sec = (tvp)->tv_usec = 0)

typedef unsigned long int usec;
usec difference(struct timeval tv1, struct timeval tv2);

/** Should we sleep for a random amount of time? */
void random_sleep(int isRand, int sleep);

#endif /*TIMERS_H_*/
