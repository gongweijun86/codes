#!/bin/bash/

cut -f2 -d" " left.txt > left1.txt
sed 's/^/&pat./g' left1.txt > left2.txt
sed 's/;/ = /g' left2.txt > left3.txt

cut -f1 -d")" right.txt > right1.txt
cut -f2 -d"#" right1.txt > right2.txt
grep "define" right2.txt > right5.txt
sed 's/define[\t, ]//g' right5.txt > right3.txt
sed 's/b/sec_start);/g' right3.txt > right4.txt

i=0
j=0
while read LINE
do
	j=0
	while read L
	do
	    if [ $i -eq $j ];then
		echo "$L $LINE"
	    fi
	    j=$(($j+1))
	done < left3.txt
	i=$(($i+1))
done < right4.txt

#rm left[1-9].txt
#rm right[1-9].txt
