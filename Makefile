OBJS = compose_sin_curve.o fileIO.o waves.o

all: $(OBJS)
	gcc -Wall -O2 $(OBJS)

compose_sin_curve.o: compose_sin_curve.c
    gcc -c compose_sin_curve.c

fileIO.o: fileIO.c
	gcc -c fileIO.c

waves.o: waves.c
	gcc -c waves.c

.PHONY: clean

clean: 
	rm -f ./a.out $(OBJS)


