CC=g++
DEPS = Deck.h
OBJ = main.o Deck.o 
EXEC = roba-paquetes

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

pack:
	tar cvzf $(EXEC).tgz $(DEPS) *.cpp Makefile
