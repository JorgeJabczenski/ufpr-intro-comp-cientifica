CC = gcc
CFLAGS = -std=c11
LDLIBS = -lm

all: analiseIntervalar.out

analiseIntervalar.out : main.c
	$(CC) main.c -o analiseIntervalar.out $(CFLAGS) $(LDLIBS) 

clean:
	rm *.out