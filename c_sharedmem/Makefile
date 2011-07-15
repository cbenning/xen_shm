
EXEC=proctest
CC=gcc
CFLAGS=-g -lpthread -Wall -Wextra
OBJS=main2.o proc2.o timing.o timers.o
SOURCE=main2.c proc2.c timing.c timers.c

all: $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) 
	
$(OBJS) : $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE)

clean: 
	rm *.o $(EXEC)
