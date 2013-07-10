mkdir tempstore

./houghlines "$1"

./detectflip tempstore/temp1.png > temp1.txt 2>&1
./detectflip tempstore/temp2.png > temp2.txt 2>&1

rm junkpix*
