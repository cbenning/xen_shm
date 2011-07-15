/*!
 * \file shm_socket.c
 *
 * \author Christopher Benninger
 * \date June 8
 *
 * Custom SHM Socket IFace
 */

#include <unistd.h>
#include "shm_socket.h"


shm_socket_t* shm_socket(int shmKey, int buflen){

	shm_socket_t* sock = NULL;
	void* shm;
	int shmSize = (3*sizeof(sem_t))+6*(sizeof(int))+buflen;
	int shmID;
	//Get SHM reference
	if ((shmID = shmget(shmKey, shmSize, IPC_CREAT | 0666)) < 0) {
		perror("Unable to allocate shared memory space.\n");
		exit(1);
	}

	//Attach SHM segment to memory space
	if ((shm = shmat(shmID, (void *) 0, 0)) == (char *) -1) {
		perror("unable to attach SHM segment to memory space\n");
		exit(1);
	}


	//Fill up the struct
	sock = shm;
    sock->buflen = buflen;
    sock->shmID = shmID;
    sock->bufhead = 0;
    sock->buftail = 0;
    sock->connected = 0;
    sock->sigclose = 0;

	//Write 0 bytes into buffer
	bzero(sock->buffer, buflen);

	//Initialize the semaphores
	sem_init(&(sock->empty),1,buflen);
	sem_init(&(sock->full),1,0);
	sem_init(&(sock->mutex),1,1);

	return sock;
}


shm_socket_t* shm_bind(int shmKey, int buflen){

	void* shm;
	int shmSize = (3*sizeof(sem_t))+buflen;
	int shmID;

	//Get SHM reference
	int binding = 1;
	while(binding){
		if ((shmID = shmget(shmKey, shmSize, 0666)) < 0) {
			printf("In bind loop\n");
			usleep(100);
        }
		else{
            //managed to bind;
            binding = 0;
        }
    }

    //Attach SHM segment to memory space
    if((shm = shmat(shmID, (void*)0, 0)) == (char*)-1){
        perror("unable to attach SHM segment to memory space\n");
        exit(1);
    }

    //Notify server
    ((shm_socket_t*)shm)->connected = 1;
    sem_post(&((shm_socket_t*)shm)->full);

	return shm;
}

int shm_close_server(shm_socket_t* sock){
	sem_wait(&(sock->mutex));
	sock->connected = 0;
	sock->sigclose = 1;
	sem_destroy(&(sock->empty));
	sem_destroy(&(sock->full));
	sem_destroy(&(sock->mutex));
	int shmID = sock->shmID;
	shmdt(&(sock->empty));
	shmctl(shmID, IPC_RMID, 0);
	return 0;
}


int shm_close_client(shm_socket_t* sock){
	//signal the server to terminate socket
	sem_wait(&(sock->mutex));
	sock->connected = 0;
	sock->sigclose = 1;
	sem_post(&(sock->mutex));
	//detach
	sem_post(&(sock->empty));
	sem_post(&(sock->full));
	shmdt(sock);
	return 0;
}


int shm_socket_write(shm_socket_t* sock, void *buf, int size){

	char* chbuf = (char*)buf;
	int i;
	for(i = 0; i < size; i++){
		//Write
		shm_socket_write_byte(sock,&chbuf[i]);
	}
	return 0;
}

int shm_socket_write_str(shm_socket_t* sock, char* buf){

	int reading = 1;
	int i = 0;
	while(reading && i < MAXSTR){

		//Write
		shm_socket_write_byte(sock,&buf[i]);

		if(buf[i]=='\0'){
			reading=0;
		}
		i++;
	}

	return i;
}

int shm_socket_write_byte(shm_socket_t* sock, char* byte){

	if(!sock->connected || sock->sigclose){
		return 0;
	}

	sem_wait(&(sock->empty));
	sem_wait(&(sock->mutex));

	//printf("writing> %c\n",*byte);
	*(char*)(sock->buffer+sock->bufhead) = *byte;

	//Increment the index
	sock->bufhead++;
	if(sock->bufhead>=(sock->buflen)){
		sock->bufhead=0;
	}

	sem_post(&(sock->mutex));
	sem_post(&(sock->full));

	return 1;
}

int shm_socket_read(shm_socket_t* sock, void* buf, int size){

	char* chbuf = (char*)buf;
	int i;
	for(i = 0; i < size; i++){

		//Write
		shm_socket_read_byte(sock,&chbuf[i]);

	}

	return 0;
}


int shm_socket_read_str(shm_socket_t* sock, char** buf){

	char* chbuf = calloc(0,MAXSTR);
	int reading = 1;
	int i =0;
	while(reading && i < MAXSTR){

		//Write
		shm_socket_read_byte(sock,&chbuf[i]);

		if(chbuf[i]=='\0'){
			reading=0;
		}
		i++;
	}

	*buf = chbuf;

	return i;
}

int shm_socket_read_byte(shm_socket_t* sock, char* buf){

	sem_wait(&(sock->full));
	sem_wait(&(sock->mutex));


	*buf = *(char*)(sock->buffer+sock->buftail);

	//Increment the index
	sock->buftail++;
	if(sock->buftail>=(sock->buflen)){
		sock->buftail=0;
	}

	sem_post(&(sock->mutex));
	sem_post(&(sock->empty));

	if(!sock->connected || sock->sigclose){
		return 0;
	}

	return 1;
}

int shm_listen(shm_socket_t* sock){

	int listening = 1;

	int state = 0;

	while(listening){

		sem_wait(&(sock->full));

		if(sock->connected != 1){
			if(sock->sigclose == 1){

				state = 0;

			}
			else{
				state= 1;
			}
		}
		else{
			state =0;
			listening = 0;
		}
		//sem_post(&(sock->full));

	}

	return state;

}


int shm_is_connected(shm_socket_t* sock){

		int state = 0;

		if(sock->connected == 1){
			if(sock->sigclose == 1){

				state = 0;

			}
			else{
				state = 1;
			}
		}
		else{
			state = 0;
		}

		return state;

}

