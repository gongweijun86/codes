#!/bin/bash
for i in $@;
do
    if [ -f $i ];then
	echo $i
	awk '/^ *$/ {x=x+1;print x;}' $i
    else
	    echo "error:$i not a file" >&2
    fi
done



