all: frac.exe

frac.exe: frac.o fracClient.cpp
	g++ -o frac.exe frac.o fracClient.cpp

frac.o:
	g++ -c frac.cpp