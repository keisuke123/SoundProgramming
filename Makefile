OBJS = fileIO.o forfileIO.o

all: $(OBJS)
	gcc -Wall -O2 $(OBJS)

fileIO.o: fileIO.c
	gcc -c fileIO.c

forfileIO.o: forfileIO.c
	gcc -c forfileIO.c

.PHONY: clean

clean: 
	rm -f ./a.out $(OBJS)


