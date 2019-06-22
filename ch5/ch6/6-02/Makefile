CC = /usr/bin/gcc 
DEPS = getword_c.c

all: clean keyword_count

keyword_count:
	$(CC) $(DEBUG) -o keyword_count.out keyword_count.c $(DEPS) 

debug: DEBUG = -g
debug: clean keyword_count

clean:
	rm -f *out