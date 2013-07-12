#!/bin/sh
g++ -ggdb `pkg-config --cflags opencv` detectflip.c deskewnew.cpp -I/usr/local/include/leptonica -l lept -l png -l jpeg -l tiff -lm -o autorotate `pkg-config --libs opencv`
