CC = /usr/bin/gcc 
DEPS = get_token.c

all: clean dcl undcl

dcl:
	$(CC) $(DEBUG) -o dcl.out dcl.c $(DEPS) 

undcl:
	$(CC) $(DEBUG) -o undcl.out undcl.c $(DEPS) 

debug: DEBUG = -g
debug: clean dcl undcl

clean:
	rm -f *out