all : erftut erftutc

erftut : erf_tutorial.cpp
	g++ -std=c++11 erf_tutorial.cpp -o erf_tutorial
	./erf_tutorial

erftutc : erf_tutorial.c
	gcc erf_tutorial.c -o erf_tutorialc -lm
	./erf_tutorialc