#!/bin/bash
x=0
while [ $x -lt 10 ]
do
	echo $x
#	x=`echo "$x+1" | bc`
x=`echo $(($x+1))`
done
