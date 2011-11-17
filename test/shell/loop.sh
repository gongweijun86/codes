#!/bin/bash
x=0
while [ "$x" -lt 10 ]
do
	y="$x"
	while [ "$y" -ge 0 ]
	do
	    echo -e "$y\c"
	    y=`echo "$y-1"|bc`
	done
	echo
	x=`echo "$x + 1"|bc`
done


