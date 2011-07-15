
DIRS=socket server client

##Rules
all:
	for dir in $(DIRS); do make -C $$dir $@; done

clean: 
	rm -f *.o *~
	cd ./socket ; make clean
	cd ./server ; make clean
	cd ./client ; make clean

	
