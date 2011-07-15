
EXEC=proctest
CC=gcc
CFLAGS=-lpthread -Wall -Wextra
#CTYPE=-g
CTYPE=-O3 -O0
#CTYPE=-g3 -O0
SOURCE_FILES=main proc timing timers

SOURCE := $(foreach FILE,$(SOURCE_FILES),$(FILE).c)
OBJS := $(foreach FILE,$(SOURCE_FILES),$(FILE).o)



all : $(OBJS)
	$(CC) $(CTYPE) $(CFLAGS) $(OBJS) -o $(EXEC)

$(OBJS) : $(SOURCE)
	$(CC) $(CTYPE) $(CFLAGS)  -c $(SOURCE)

clean: 
	rm *.o $(EXEC)

	
