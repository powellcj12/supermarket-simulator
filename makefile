CC = g++
CFLAGS = -c -Wall -Wextra
all: simulator

simulator: main.o Supermarket.o Queue.o Customer.o
	$(CC) main.o Supermarket.o Queue.o Customer.o -o simulator

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Supermarket.o: Supermarket.cpp
	$(CC) $(CFLAGS) Supermarket.cpp

Queue.o: Queue.cpp
	$(CC) $(CFLAGS) Queue.cpp

Customer.o: Customer.cpp
	$(CC) $(CFLAGS) Customer.cpp

clean:
	rm -rf *o simulator
