
##Variables
CC=gcc
CTYPE=-g
CFLAGS=-lpthread -Wall -Wextra
#CTYPE=-O3 -O0
#CTYPE=-g3 -O0

##Construction
SOURCE_FILES=client ../socket/shm_socket
SOURCE := $(foreach FILE,$(SOURCE_FILES),$(FILE).c)
OBJS := $(foreach FILE,$(SOURCE_FILES),$(FILE).o)

##Rules
all : client
	
client: $(OBJS)
	$(CC) $(CTYPE) $(CFLAGS) $(OBJS) -o client

$(OBJS): $(SOURCE)
	$(CC) $(CTYPE) $(CFLAGS) -c $(SOURCE)

clean: 
	rm -f *.o *~ client