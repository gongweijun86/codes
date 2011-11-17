#!/bin/bash

USAGE="USAGE: sh $0 filename begintime endtime"    # time format: hh:mm
if [ $# == 3 ]; then
    File_name=$1
    Begin_time=$2
    End_time=$3
else
    echo $USAGE
    exit 1
fi

Begin_timestamp=$(date +%s -d"$Begin_time")
End_timestamp0=$(date +%s -d"$End_time")
let End_timestamp=$End_timestamp0+60

cat $File_name | while read line; do
    Time=$(echo $line | awk -F'[' '{print $2}' | awk -F':' '{print $1":"$2}')
    Timestamp=$(date -d"$Time" +%s)

    if [ $Timestamp -ge $Begin_timestamp -a $Timestamp -lt $End_timestamp ]; then
        echo "$line"
    fi
done

exit 0
