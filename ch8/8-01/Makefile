CC = /usr/bin/gcc 

all: clean cat cat_syscall

cat:
	$(CC) $(DEBUG) -o cat.out cat.c

cat_syscall:
	$(CC) $(DEBUG) -o cat_syscall.out cat_syscall.c


debug: DEBUG = -g
debug: clean cat cat_syscall

clean:
	rm -f *out