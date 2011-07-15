/*!
 * \file main.c
 *
 * \author Christopher Benninger
 * \date June 10
 */

#include <unistd.h>
#include "shm_socket.h"

int main(int argc, char** argv){

	//int shmID = ftok("Makefile",1);
	int shmID = atoi(argv[1]);
	shm_socket_t* tmp;
	tmp = shm_bind(shmID,BUFLEN);
	char myarray[] = "Wilkommen!\n\0";
	shm_socket_write_str(tmp,myarray);
	shm_close_client(tmp);

	return 0;
}

