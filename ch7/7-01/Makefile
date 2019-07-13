CC = /usr/bin/gcc 

all: clean upper lower

upper:
	$(CC) $(DEBUG) -o upper caseconv.c

lower: upper
	cp upper lower

debug: DEBUG = -g
debug: clean upper lower

clean:
	rm -f *out upper lower