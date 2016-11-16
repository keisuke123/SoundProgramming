OBJS = read_wave_file.o waves.o fileIO.o
CFLAGS = -Wall -O2 -lm -I ../../header

all: $(OBJS)
	gcc $^

read_wave_file.o: read_wave_file.c
	gcc -c $(CFLAGS) read_wave_file.c

waves.o: ../../header/waves.c
	gcc $(CFLAGS) -c ../../header/waves.c

fileIO.o: ../../header/fileIO.c
	gcc $(CGLAGS) -c ../../header/fileIO.c

.PHONY: clean

clean: 
	rm -f $(OBJS)
