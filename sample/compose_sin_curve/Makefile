OBJS = compose_sin_wave.o waves.o fileIO.o
CFLAGS = -Wall -O2 -I../../header

all: $(OBJS)
	gcc $^

compose_sin_curve.o: compose_sin_wave.c
	gcc -c $(CFLAGS) compose_sin_wave.c

waves.o: ../../header/waves.c
	gcc $(CFLAGS) -c ../../header/waves.c

fileIO.o: ../../header/fileIO.c
	gcc $(CGLAGS) -c ../../header/fileIO.c

.PHONY: clean

clean: 
	rm -f $(OBJS)
