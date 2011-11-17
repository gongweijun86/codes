#!/bin/bash
ioin file1 file2 >file3.txt
join -v1 file1 file3.txt >tmp1
join -v1 file2 file3.txt >tmp2
awk '{print $0" "0}' tmp1 >>file3.txt
awk '{print $1” "0" " $2}' tmp2 >>file3.txt
sort file3.txt -o output.txt
rm tmp1 tmp2 file3.txt
exit 0
