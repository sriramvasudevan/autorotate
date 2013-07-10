mkdir -p tempstore
mkdir -p success
mkdir -p failed

./deskew "$1" > log.txt

orientation=$(./detectflip tempstore/temp.tiff 2>&1)

if [ "$orientation" == "upside-down" ]; then
    ./rotateimg tempstore/temp.tiff
    mv tempstore/temp.tiff success/$(basename $1)
elif [ "$orientation" == "" ]; then
    echo "Image size too small. Please try using an image of higher resolution."
    mv tempstore/temp.tiff failed/$(basename $1)
else
    mv tempstore/temp.tiff success/$(basename $1)
fi

rm tempstore -rf
