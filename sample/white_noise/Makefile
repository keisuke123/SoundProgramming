OBJS = white_noise.o waves.o fileIO.o
CFLAGS = -Wall -O2 -lm -I ../../header

all: $(OBJS)
	gcc $^

white_noise.o: white_noise.c
	gcc -c $(CFLAGS) white_noise.c

waves.o: ../../header/waves.c
	gcc $(CFLAGS) -c ../../header/waves.c

fileIO.o: ../../header/fileIO.c
	gcc $(CGLAGS) -c ../../header/fileIO.c

.PHONY: clean

clean: 
	rm -f $(OBJS)
