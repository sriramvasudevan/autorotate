mkdir tempstore
mkdir final

./houghlines "$1" > log.txt

./detectflip tempstore/temp1.png > temp1.txt 2>&1
./detectflip tempstore/temp2.png > temp2.txt 2>&1

rm junkpix*

imgpath=$(python picker.py)
if [ -f "$imgpath" ]; then
    mv "$imgpath" final/$(basename $1).png
else
    echo "$imgpath"
fi

rm temp*.txt -f
rm tempstore -rf
