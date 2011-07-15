/*!
 * \file proc.h
 *
 * \author Christopher Benninger
 * \date May 22
 *
 * Contains functions for server and client processes
 */
#ifndef PROC_H_
#define PROC_H_

void srvProc(int shmKey, int shmLength, int procID);

void clnProc(int shmKey, int shmLength, int procID, int iters);

#endif
