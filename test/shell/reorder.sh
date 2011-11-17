#!/bin/bash
NUMFRUIT="$1"
if [ -f "NUMFRUIT" ] ; then NUMFRUIT=75 ; fi
awk '
	$3 <= numfruit {print ;}
' numfruit="$NUMFRUIT" fruit_prices.txt
