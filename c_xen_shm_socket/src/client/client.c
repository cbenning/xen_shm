/*!
 * \file main.c
 *
 * \author Christopher Benninger
 * \date June 10
 */

#include <unistd.h>
#include "../socket/shm_socket.h"

#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>


int main(int argc, char** argv){

	/*
	//int shmID = ftok("Makefile",1);
	int shmID = atoi(argv[1]);

	shm_socket_t* tmp;
	tmp = shm_bind(shmID,BUFLEN);
	FILE *fp;
	fp=fopen(argv[2], "r");
	char charBuf;
	charBuf = fgetc(fp);

	while(charBuf != EOF){
	printf("asd\n");
		//printf("Writing: %c\n", charBuf);
		shm_socket_write_byte(tmp,&charBuf);
		charBuf = fgetc(fp);
	}

	fclose(fp);
	shm_close_client(tmp);
*/



	int fd;

	fd = open("/dev/xenshm", O_RDWR );
	if(ioctl(fd, 0) == -1){
	  printf("Failed to send IOCTL command\n");
	}

	void* mem;
	if( (mem = mmap(NULL , 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
	      perror("Could not mmap file");
	      exit (43);
	}

	//char* tmpStr = "Test";

	return 0;
}
