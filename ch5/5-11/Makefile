CC = /usr/bin/gcc
DEPS = tabs.c

all: clean entab detab

entab:
	$(CC) -o entab.out entab.c $(DEPS) 

detab:
	$(CC) -o detab.out detab.c $(DEPS) 

clean:
	rm -f *out