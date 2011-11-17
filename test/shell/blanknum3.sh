#!/bin/bash
for i in $@ ;
do
    if [ -f "$i" ]; then
	    awk 'BEGIN { printf "%s\t",FILENAME;}
	    /^ *$/ {x=x+1;}
	    END { ave=100*(x/NR); printf " %s\t%3.1f\n",x,ave;}
	    ' "$i"
    else
	   echo "ERROR:$i is not a file" >&2
    fi
done
