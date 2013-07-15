#/bin/bash

cd ~/autorotate/code/

mkdir -p tempstore
mkdir -p success
mkdir -p failed

numfil=$(find $1/ -maxdepth 1 -type f | wc -l)
echo "${numfil} potential files to analyze"
id=0

for f in "$1"/*
do
    if [ -f $f ]; then
        ((id++))
        echo "${id} out of ${numfil}"
        ext=${f##*.}
        if [ "$ext" == "tif" ] || [ "$ext" == "tiff" ] || [ "$ext" == "jpg" ] || [ "$ext" == "jpeg" ] || [ "$ext" == "bmp" ] || [ "$ext" == "png" ] ; then
            echo "Found an image. Analyzing..."
            ./deskew "$f" > log.txt

            orientation=$(./detectflip tempstore/temp.$ext 2>&1)

            if [ "$orientation" == "upside-down" ]; then
                ./rotateimg tempstore/temp.$ext
                mv tempstore/temp.$ext success/$(basename $f)
            elif [ "$orientation" == "" ]; then
                echo "Image size too small. Please try using an image of higher resolution."
                cp $f failed/$(basename $f)
            else
                mv tempstore/temp.$ext success/$(basename $f)
            fi
        else
            echo "Not an image. Moving on to the next file..."
        fi
    fi
done

rm tempstore -rf
