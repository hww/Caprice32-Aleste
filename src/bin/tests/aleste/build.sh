#!/bin/bash

# ----------------------------------------------------
# Requires the PASMO assembler.
# Use "Bash on Ubuntu on Windows" inside windows
# > sudo apt-get install pasmo
# ----------------------------------------------------

# Designate location of target disk

DISK=../../bin/disk/tests.dsk

#Compile files

cat files.txt | while read line
do
   IFS=, read file1 file2 <<< $line
   pasmo --amsdos "$(basename "$file1").asm" "$(basename "$file1").bin"
done

# Create disk

./cpcxfs.exe -f -nd $DISK

# Copy files

cat files.txt | while read line
do
    IFS=, read file1 file2 <<< $line
   ./cpcxfs.exe $DISK -f -p "$(basename "$file1").bin" "$(basename "$file2")"
done
