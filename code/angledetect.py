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
print "Number of files that had to be rotated was ",rot
print "Number of files that were already rightside-up was ",notrot

