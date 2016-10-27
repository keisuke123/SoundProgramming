OBJS = dft.o waves.o fileIO.o
CFLAGS = -Wall -O2 -lm

all: $(OBJS)
	gcc $^

dft.o: dft.c
	gcc -c dft.c

waves.o: ../../header/waves.c
	gcc $(CFLAGS) -c ../../header/waves.c

fileIO.o: ../../header/fileIO.c
	gcc $(CGLAGS) -c ../../header/fileIO.c

.PHONY: clean

clean: 
	rm -f $(OBJS)
