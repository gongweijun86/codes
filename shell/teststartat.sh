#!/bin/bash
#@(#) test 'for' loops with $* and $@
#
echo "Test star"
echo "We have $# arguments"
for arg in $*
do
	echo $arg
done

echo "Test at"
echo "We have $# arguments"
for arg in "$@"
do
	echo $arg
done
#end of file
