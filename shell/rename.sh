#!/bin/bash

folder=~/Downloads/dvb
cd $folder
for filename in `ls $folder`;do
	echo $filename|tr -d [0-9]
done
exit
