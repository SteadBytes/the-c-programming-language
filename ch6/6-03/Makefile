CC = /usr/bin/gcc 
DEPS = getword.c

all: clean cross_reference

cross_reference:
	$(CC) $(DEBUG) -o cross_reference.out cross_reference.c $(DEPS) 

debug: DEBUG = -g
debug: clean cross_reference

clean:
	rm -f *out