
##Variables
CC=gcc
CTYPE=-g
CFLAGS=-lpthread -Wall -Wextra
LFLAGS=-DORBIT2=1 -pthread -I/usr/include/orbit-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include    -pthread -lORBit-2 -lgthread-2.0 -lrt -lgobject-2.0 -lglib-2.0 
#CTYPE=-O3 -O0
#CTYPE=-g3 -O0

##Construction
CLIENT_SOURCE_FILES=client shm_socket srv-common srv-stubs
CLIENT_HEADER_FILES=srv
SERVER_SOURCE_FILES=srv shm_socket srv-common srv-skels srv-skelimpl
SERVER_HEADER_FILES=srv
CLIENT_SOURCE := $(foreach FILE,$(CLIENT_SOURCE_FILES),$(FILE).c)
CLIENT_HEADER := $(foreach FILE,$(CLIENT_HEADER_FILES),$(FILE).h)
CLIENT_OBJS := $(foreach FILE,$(CLIENT_SOURCE_FILES),$(FILE).o)
SERVER_SOURCE := $(foreach FILE,$(SERVER_SOURCE_FILES),$(FILE).c)
SERVER_HEADER := $(foreach FILE,$(SERVER_HEADER_FILES),$(FILE).h)
SERVER_OBJS := $(foreach FILE,$(SERVER_SOURCE_FILES),$(FILE).o)


##Rules
all : client srv
	
client: $(CLIENT_OBJS)
	$(CC) $(CTYPE) $(CFLAGS) $(LFLAGS) $(CLIENT_OBJS) -o client

$(CLIENT_OBJS): $(CLIENT_SOURCE)
	$(CC) $(CTYPE) $(CFLAGS) $(LFLAGS) -c $(CLIENT_SOURCE) $(CLIENT_HEADER)

srv: $(SERVER_OBJS)
	$(CC) $(CTYPE) $(CFLAGS) $(LFLAGS) $(SERVER_OBJS) -o srv

$(SERVER_OBJS): $(SERVER_SOURCE)
	$(CC) $(CTYPE) $(CFLAGS) $(LFLAGS) -c $(SERVER_SOURCE) $(SERVER_HEADER)

clean: 
	rm *.o client srv

	
