#!/bin/bash
awk '{
	printf "%s\t",$0;
	if($2 ~ /\$[1-9][0-9]*\.[0-9][0-9]/){
		printf "*";	
		if($3 <= 75){
			printf "REORDER\n"
		}else{
			printf "\n";	
		}
	}else{
		if($3 < 75){
			printf "REORDER\n";
		}else{
			printf "\n";
		}
	}
}' fruit_prices.txt
