#!/bin/bash

response=
while [ -z $response ]
do
	echo "enter a dir:"
	read response
	if [ ! -d $response ]
	then
		echo "error: not directory"
		response=
	fi
done


