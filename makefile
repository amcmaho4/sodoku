all: main

main:main.cpp sodoku.h
	g++ main.cpp -o main
clean:
	rm *.o main

