all : errors errorsc

errors : analisi_errori.cpp
	g++ -std=c++11 analisi_errori.cpp -o analisi_errori
	./analisi_errori

errorsc : analisi_errori.c
	gcc analisi_errori.c -o analisi_erroric -lm
	./analisi_erroric