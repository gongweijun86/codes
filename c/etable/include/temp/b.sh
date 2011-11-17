#!/bin/bash

cut -f2 -d" " left.txt > temp.txt
sed 's/^/&nit./g' temp.txt > temp2.txt
sed 's/;/:%d\\n\t/g' temp2.txt > temp3.txt
sed 's/;/,/g' temp2.txt > temp4.txt

cat temp4.txt >> temp3.txt
