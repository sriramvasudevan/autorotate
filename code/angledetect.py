import sys

with open("log.txt", "r") as f:
    lines = f.readlines() # Read to end

rot,notrot = 0,0

result = []
for line in lines:
    line = line.split()
    if line[0]=="0":
        notrot+=1
    else:
        rot+=1
print "Number of file that had to be rotated is ",rot
print "Number of files that were already rightside-up ",notrot

