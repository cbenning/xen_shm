/*!
 * \file main.c
 *
 * \author Christopher Benninger
 * \date June 10
 */

#include <unistd.h>
#include "shm_socket.h"

int main(int argc, char** argv){

	//int shmID = ftok(argv[1],1);
	int shmID = 1234;/*
	if (shmID == -1) {
		perror("Failed to setup sharedmemory key:");
		exit(1);
	}
	*/
	//int pid = fork();

	//Process 2
/*
	if(pid == 0){

		shm_socket_t* tmp;
		tmp = shm_socket(shmID,BUFLEN);
		char* result;
		printf("PROC1> Listening\n");
		while(shm_listen(tmp)){

			if(shm_socket_read_str(tmp,&result)>0){
				//printf("2 %p\n",result);
				printf("PROC1> Received %s\n",result);
			}
		}
		shm_close_server(tmp);

	}
	else{
		*/
		shm_socket_t* tmp;
		tmp = shm_bind(shmID,BUFLEN);
		char myarray[] = "Wilkommen!\n\0";
		shm_socket_write_str(tmp,myarray);
		shm_close_client(tmp);
//	}

	return 0;
}

