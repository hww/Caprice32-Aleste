#!/bin/bash

# Bash on Ubuntu on Windows script

# ----------------------------------------------------
# Requires the PASMO assembler.
# Use "Bash on Ubuntu on Windows" inside windows
# > sudo apt-get install pasmo
# ----------------------------------------------------

# Designate location of target disk

DISK="../../disk/tests-msx.dsk"

#Compile files

cat files.txt | while read line
do
   IFS=, read file1 file2 <<< $line
   pasmo --bin "$(basename "$file1").asm" "$(basename "$file2").com"
done

# Create disk

#./cpcxfs.exe -f -nd $DISK

# Copy files

cat files.txt | while read line
do
    IFS=, read file1 file2 <<< $line
    #./DISKMGR.exe -A -F -C $DISK  "$(basename "$file2").com"
    ./wrdsk $DISK "$(basename "$file2").com"
done

#./cpcxfs.exe $DISK -f -p  alestesystem/BDOS.SYS
#./cpcxfs.exe $DISK -f -p  alestesystem/BIOS.SYS
#./cpcxfs.exe $DISK -f -p  alestesystem/MSXDOS.SYS
#./cpcxfs.exe $DISK -f -p  alestesystem/COMMAND.COM
#./cpcxfs.exe $DISK -f -p  alestesystem/DBG.COM

