OBJS = 12et.o waves.o fileIO.o
CFLAGS = -Wall -O2 -lm

all: $(OBJS)
	gcc $^

12et.o: 12et.c
	gcc -c 12et.c

waves.o: ../../header/waves.c
	gcc $(CFLAGS) -c ../../header/waves.c

fileIO.o: ../../header/fileIO.c
	gcc $(CGLAGS) -c ../../header/fileIO.c

.PHONY: clean

clean:
	rm -f $(OBJS)
