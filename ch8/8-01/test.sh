#!/usr/bin/env bash

fnames=`seq -w 15 | sed 's/$/.txt/'`


# create 10Mb files of random content
for f in $fnames
do
    base64 /dev/urandom | head -c 10000000 > $f
done

benchmark() {
    echo "Benchmarking $1:"
    time echo $fnames | xargs $1 > /dev/null
    echo
}

# compare execution time of stdlib cat vs syscall cat
benchmark ./cat.out
benchmark ./cat_syscall.out

# clean up random test files
for f in $fnames
do
    rm $f
done