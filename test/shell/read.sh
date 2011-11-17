#!/bin/bash
while read LINE
do 
case $LINE in
*root*) echo $LINE ;;
esac
done 
