/*!
 * \file shm_socket.h
 *
 * \author Christopher Benninger
 * \date June 8
 *
 * Custom SHM Socket IFace
 */

#ifndef SHM_SOCKET_H_
#define SHM_SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <strings.h>


#define BUFLEN 5
#define MAXSTR 1024

typedef struct{

	sem_t empty;
	sem_t full;
	sem_t mutex;
	int buflen;
	int shmID;
	int bufhead;
	int buftail;
	int connected;
	int sigclose;
	char buffer[BUFLEN];

}shm_socket_t;


shm_socket_t* attach_socket_to_shm(void* shm, int shmID, int buflen);

shm_socket_t* shm_socket(int shmKey, int buflen);

shm_socket_t* shm_bind(int shmKey, int buflen);

int shm_close_server(shm_socket_t* sock);

int shm_close_client(shm_socket_t* sock);

int shm_socket_write(shm_socket_t* sock, void* buf, int size);

int shm_socket_read(shm_socket_t* sock, void* buf, int size);

int shm_socket_write_byte(shm_socket_t* sock, char* byte);

int shm_socket_write_str(shm_socket_t* sock, char* buf);

int shm_socket_read_byte(shm_socket_t* sock, char* buf);

int shm_socket_read_str(shm_socket_t* sock, char** buf);

int shm_listen(shm_socket_t* sock);

int shm_is_connected(shm_socket_t* sock);

#endif
