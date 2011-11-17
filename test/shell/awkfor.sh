#!/bin/bash
awk '{
	for (x=NF;x>=1;x-=1){
		printf "%-10s    ",$x
	}
	printf "\n"
}' fruit_prices.txt
各种工具

