all : fileio fileioc

fileio : fileio.cpp
	g++ -std=c++11 fileio.cpp -o fileio
	./fileio

fileioc : fileio.c
	gcc fileio.c -o fileioc
	./fileioc