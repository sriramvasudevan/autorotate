#/bin/bash
function usage {
        echo "Usage : ./rawautorotate.sh [input.file.directory] [succesful.rotations.directory] [failed.rotations.directory] [storage.directory.once.done]"
        echo -e "\t - 1) input directory can have any number of files"
        echo -e "\t - 2) succesfully rotated files and files that were straight to begin with both will be stored in success directory"
        echo -e "\t - 3) failed directory will have all the files that could not be analyzed, regardless of orientation.\
        Please be advised that typical reasons for failure are lack of enough of enough text in the picture or insufficient quality."
        echo -e "\t - 4) Once looked into, the files will be moved to this directory, success or fail."
}

rootdir=$1
rootsuc=$2
rootfai=$3
rootdon=$4
bdate=$(date +"%m-%d-%Y %H:%M:%S")

if [ -z "$rootdir" ] ; then
        echo "Insufficient parameters"
        usage
        exit 2
fi

if [ -z "$rootsuc" ] ; then
        echo "Insufficient parameters"
        usage
        exit 2
fi

if [ -z "$rootfai" ] ; then
        echo "Insufficient parameters"
        usage
        exit 2
fi

if [ -z "$rootdon" ] ; then
        echo "Insufficient parameters"
        usage
        exit 2
fi

mkdir -p "$rootsuc/"success
mkdir -p "$rootfai/"failed
mkdir -p "$rootdon/"done

success="${rootsuc}/success/"$(date +"%m%d%Y_%H%M%S")
failed="${rootfai}/failed/"$(date +"%m%d%Y_%H%M%S")
donerot="${rootdon}/done/"$(date +"%m%d%Y_%H%M%S")

mkdir -p tempstore
mkdir $success
mkdir $failed
mkdir $donerot

numfil=$(find $1/ -maxdepth 1 -type f| wc -l)
echo "${numfil} potential files to analyze"
id=0
echo "Deleting previous logs..."
rm log.txt

for f in "$1"/*
do

    if [ -f $f ]; then
        ((id++))
        echo "${id} out of ${numfil}"
        ext=${f##*.}
        if [ "$ext" == "tif" ] || [ "$ext" == "tiff" ] || [ "$ext" == "jpg" ] || [ "$ext" == "jpeg" ] || [ "$ext" == "bmp" ] || [ "$ext" == "png" ] ; then
            echo "Found an image. Analyzing..."
            ./deskew "$f" >> log.txt

            orientation=$(./detectflip tempstore/temp.$ext 2>&1)

            if [ "$orientation" == "upside-down" ]; then
                ./rotateimg tempstore/temp.$ext
                mv tempstore/temp.$ext $success/$(basename $f)
            elif [ "$orientation" == "" ]; then
                echo "Image size too small. Please try using an image of higher resolution."
                cp $f $failed/$(basename $f)
            else
                mv tempstore/temp.$ext $success/$(basename $f)
            fi
            mv $f $donerot
        else
            echo "Not an image. Moving on to the next file..."
        fi
    fi
done

rm tempstore -rf
numrot=$(python angledetect.py)
numstr=`expr $numfil - $numrot`
numfail=$(find $failed -maxdepth 1 -type f| wc -l)
numsuc=$(find $success -maxdepth 1 -type f| wc -l)
echo "${bdate},${numfil},${numsuc},${numfail},${numrot},${numstr}" >> results.csv

echo "Done. Successful autorotations saved to ${success} and failures saved to ${failed}"

