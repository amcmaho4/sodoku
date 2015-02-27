all: main

main:main.cpp sodoku2.h
	g++ main.cpp -o main
clean:
	rm *.o main

