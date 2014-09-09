all: client

client: frac.o fracArray.o fracArrayClient.o
	g++ frac.o fracArray.o fracArrayClient.cpp -o client

fracArrayClient.o:
	g++ -c fracArrayClient.cpp

fracArray.o:
	g++ -c fracArray.cpp

frac.o:
	g++ -c frac.cpp

clean:
	rm -f *.o client