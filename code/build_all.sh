#!/bin/sh

if [ $# -gt 0 ] ; then
	base=`basename $1 .c`
	echo "compiling $base"
    gcc $base.c -I/usr/local/include/leptonica -I/usr/local/include -L/usr/lib -l lept -l png -l jpeg -l tiff -lm -o $base

else
	for i in *.c; do
	    echo "compiling $i"
        gcc $i -I/usr/local/include/leptonica -I/usr/local/include -L/usr/lib -l lept -l png -l jpeg -l tiff -lm -o `basename $i .c`
	done
	for i in *.cpp; do
	    echo "compiling $i"
	    g++ -ggdb `pkg-config --cflags opencv` -o `basename $i .cpp` $i `pkg-config --libs opencv`;
	done
fi
