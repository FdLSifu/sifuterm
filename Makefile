CC=gcc
CFLAGS=-O3 -Wall `pkg-config --cflags vte-2.91` 
LDFLAGS=`pkg-config --libs vte-2.91`
EXEC=sifuterm

all: $(EXEC)

sifuterm: main.c
	$(CC) $(CFLAGS) main.c -o $(EXEC) $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)

