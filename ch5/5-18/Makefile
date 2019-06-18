CC = /usr/bin/gcc
DEPS = get_token.c

all: clean dcl undcl

dcl:
	$(CC) -o dcl.out dcl.c $(DEPS) 

undcl:
	$(CC) -o undcl.out undcl.c $(DEPS) 

clean:
	rm -f *out