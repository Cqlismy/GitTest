# A simple Makefile for test app

all:
	gcc test.c -o test

clean:
	rm -rf test
