CC = gcc
CFLAGS = -O0 -std=c99 -Wall
DEPS = ssbc.h
LIBS = ~cse231/ssbc.a -lpthread -lncurses

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: demo warmup poll-calculator interrupt-calculator

demo: demo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
     
warmup: warmup.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
     
poll-calculator: poll-calculator.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

interrupt-calculator: interrupt-calculator.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

