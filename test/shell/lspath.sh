#!/bin/bash

for dir in $PATH
do
	oldifs="$IFS"
	IFS=:
	echo $dir
	IFS=$oldfs
done

