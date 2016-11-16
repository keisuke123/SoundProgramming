OBJS = output_wave.o waves.o fileIO.o
CFLAGS = -Wall -O2 -lm -I ../../header

all: $(OBJS)
	gcc $^

output_wave.o: output_wave.c
	gcc -c $(CFLAGS) output_wave.c

waves.o: ../../header/waves.c
	gcc $(CFLAGS) -c ../../header/waves.c

fileIO.o: ../../header/fileIO.c
	gcc $(CGLAGS) -c ../../header/fileIO.c

.PHONY: clean

clean: 
	rm -f $(OBJS)
