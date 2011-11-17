#!/bin/bash

printf "%-32s %s\n" "File Name" "File Type"
 
for i in *;
do
printf "%-32s " "$i"
if [ -d "$i" ]; then
echo "directory"
elif [ -h "$1" ]; then
echo "symbolic link"
elif [ -f "$i" ]; then
echo "file"
else
echo "unknown"
fi
done
