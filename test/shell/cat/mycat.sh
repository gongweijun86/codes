#!/bin/bash

allFile=`ls file*`
echo $allFile
fileNum=${#allFile}
fileNum=9
echo $fileNum
i=1
while [ $i -lt ${fileNum} ]; do
	while read LINE
	do
		col1=`echo ${LINE%' '*}`
		col2=`echo ${LINE#*' '}`
		isExist=`cat f | grep ${col1}`
		if [ -z "${isExist}" ]
		then
			str="${col1}"
			for((j=1;j<$i;j++)); do
				str+=" -"
			done
			str+=" ${col2}"
			echo $str >> f
			cp f a
		else
			#text=`sed "s/${col1}.*$/& ${col2}/" f`
			sed  "s/${col1}.*$/& ${col2}/" f | tee a 
			#echo $text > f
			cp a f
		fi
	done < file${i}
	((i+=1))
	while read aLine; do
		var=`echo ${aLine} | cut -f${i} -d" "`
		if [ -z "${var}" ]; then
			sed  "s/${aLine}.*$/${aLine} -/" f | tee a
			cp a f
		fi
	done < f
done
