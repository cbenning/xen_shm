/*!
 * \file main.c
 *
 * \author Christopher Benninger
 * \date June 10
 */

#include <unistd.h>
#include "shm_socket.h"
//#include "srv.h"




int main(int argc, char** argv){

	//int shmID = ftok("Makefile",1);

	int shmID = getpid();
	char* outfile = argv[1];

	processRequests(shmID, outfile);
return 0;
}



void processRequests(int shmID, char* outfile){

	FILE *file;
	file = fopen(outfile, "w");

    if (file == NULL) {
        fprintf(stderr,"Can not open output file\n");
        exit (8);
    }


	shm_socket_t* tmp;

	tmp = shm_socket(shmID,BUFLEN);
	char result;
	printf("SERVER> Listening\n");
	shm_listen(tmp);
	printf("SERVER> Session Begun\n");

	while(shm_is_connected(tmp)){

		if(shm_socket_read_byte(tmp,&result)>0){
			//printf("SERVER> Received %c\n",result);
			fputc((unsigned int)result, file);
		}
		else{
			break;
		}
	}


	printf("SERVER> Session Ended\n");

	shm_close_server(tmp);

	fclose(file);


}


double add(double i, double j){
	return i+j;
}
