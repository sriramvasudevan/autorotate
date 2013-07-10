mkdir tempstore
mkdir final

for f in "$1"/*
do
    ext=${f##*.}
    if [[ "${ext}" == "tif" ] || [ "${ext}" == "tiff" ] || [ "${ext}" == "jpg" ] || [ "${ext}" == "jpeg" ] || [ "${ext}" == "bmp" ] || [ "${ext}" == "png" ]]
    then
        
        ./houghlines "$1"/f > log.txt

        ./detectflip tempstore/temp1."$ext" > temp1.txt 2>&1
        ./detectflip tempstore/temp2."$ext" > temp2.txt 2>&1

        rm junkpix*

        imgpath=$(python picker.py)
        if [ -f "$imgpath" ]; then
            mv "$imgpath" final/$(basename $1)
        else
            echo "$imgpath"
        fi

        rm temp*.txt -f
        rm tempstore -rf
done
