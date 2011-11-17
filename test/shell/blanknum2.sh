#!/bin/bash
for i in $@;
do
    if [ -f $i ]; then
	    echo -e "$i\c"
	    awk '/^ *$/ {x=x+1;}
	    END {printf " %s\n",x;}
	    ' "$i"
    else
	    echo "ERROR:$i is not a file" >&2
    fi
done

