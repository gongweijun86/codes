#!/bin/bash
while getopts "ab:cd:" Option
# b and d take arguments
#
do
case $Option in
a) echo -e "a = $OPTIND";;
b) echo -e "b = $OPTIND $OPTARG";;
c) echo -e "c = $OPTIND";;
d) echo -e "d = $OPTIND $OPTARG";;
esac
done
echo $0$1$2$3$4
echo 
shift "$(($OPTIND - 1))"
echo $0$1$2$3$4
