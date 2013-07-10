import sys

with open("temp1.txt", "r") as f:
    f.seek (0, 2)           # Seek @ EOF
    fsize = f.tell()        # Get Size
    f.seek (max (fsize-1024, 0), 0) # Set pos @ last n chars
    lines = f.readlines()       # Read to end 

lines = [lines[-4], lines[-2]]

result = []
for line in lines:
    line = line.split()
    if line[0]=="Text":
        result.append(line[-1])
    else:
        print "Image size too small. Please try using an image of higher resolution."
        sys.exit(0)

if result[0]==result[1]:
    pass
else:
    print "Image size too small. Please try using an image of higher resolution."
    sys.exit(0)

with open("temp2.txt", "r") as f:
    f.seek (0, 2)           # Seek @ EOF
    fsize = f.tell()        # Get Size
    f.seek (max (fsize-1024, 0), 0) # Set pos @ last n chars
    lines = f.readlines()       # Read to end 

lines = [lines[-4], lines[-2]]

for line in lines:
    line = line.split()
    if line[0]=="Text":
        result.append(line[-1])
    else:
        print "Image size too small. Please try using an image of higher resolution."
        sys.exit(0)

if result[2]==result[3]:
    result = [result[0], result[2]]
else:
    print "Image size too small. Please try using an image of higher resolution."
    sys.exit(0)

if result[0] == "rightside-up":
    print "tempstore/temp1.png"
else:
    print "tempstore/temp2.png"
