
##Variables
CC=gcc
CTYPE=-g
CFLAGS=-lpthread -Wall -Wextra
#CTYPE=-O3 -O0
#CTYPE=-g3 -O0

##Construction
SOURCE_FILES=server ../socket/shm_socket
SOURCE := $(foreach FILE,$(SOURCE_FILES),$(FILE).c)
OBJS := $(foreach FILE,$(SOURCE_FILES),$(FILE).o)

##Rules
all : server
	
server: $(OBJS)
	$(CC) $(CTYPE) $(CFLAGS) $(OBJS) -o server

$(OBJS): $(SOURCE)
	$(CC) $(CTYPE) $(CFLAGS) -c $(SOURCE)

clean: 
	rm -f *.o *~ server

	
