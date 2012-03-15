# SupermarketSimulator

## Introduction
This is a simulator for computing wait times of customers at a supermarket. It is a discrete time simulator - it uses a "tick" as a second.

Wait time for each customer is the difference between when they are ready to check out and when they actually begin checking out. The time it takes them at the register does not count towards their wait time.

## Usage
	make
	./simulator

## Execution
The simulator first asks which of the following configurations you would like to use:

1. A simple configuration with a single register that takes all customers.
2. A supermarket with 4 registers, each with its own line.
3. A supermarket with 2 regular lines and 2 express lines. Only customers with 5 items or fewer can use the express lines.
4. A supermarket with 4 registers, but only 1 line. The front customer goes to the next available register when it becomes free. Think of this like a bank.

It will then ask for the name of a file to use as input. The input format is as follow:
	
	Name NumberOfItems ArrivalTime

Here is an example:
	
	Same 17 2
	Ben 4 6
	Norman 11 9
	Bruce 2 11
	Diane 9 15
	...etc...

Note that this list must be sorted by increasing arrival times.

## Output
The average wait time for all customers and express customers will be printed to stdout. A file will also be created that displays the order in which the customers finished checking out. The name of this file is the same as the one used as input with the ".out" extension appended.
