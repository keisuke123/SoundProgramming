OBJS = compose_sin_curve.o waves.o fileIO.o
CFLAGS = -Wall -O2 -lm

all: $(OBJS)
	gcc $^

compose_sin_curve.o: compose_sin_curve.c
	gcc -c compose_sin_curve.c

waves.o: ../../header/waves.c
	gcc $(CFLAGS) -c ../../header/waves.c

fileIO.o: ../../header/fileIO.c
	gcc $(CGLAGS) -c ../../header/fileIO.c

.PHONY: clean

clean: 
	rm -f $(OBJS)
