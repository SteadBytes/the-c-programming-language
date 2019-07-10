CC = /usr/bin/gcc 
DEPS = getword.c

all: clean distinct_count

distinct_count:
	$(CC) $(DEBUG) -o distinct_count.out distinct_count.c $(DEPS) 

debug: DEBUG = -g
debug: clean distinct_count

clean:
	rm -f *out