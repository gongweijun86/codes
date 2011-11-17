#!/bin/bash
PROG=find / -name signame.sh
AlarmHandler(){
	echo "Got SIGALERM,cmd too too long"
	KillSubProcs
	exit 14
}
KillSubProcs(){
	kill ${CHPROCIDS:-$!}
	if [ $? -eq 0 ]; then
		echo "Sub-processes killed";
	fi
}
SetTimer(){
	DEF_TOUT=${1:-10};
	if [ $DEF_TOUT -ne 0 ];then
		sleep $DEF_TOUT && kill -s 14 $$ &
		CHPROCIDS="$CHPROCIDS $!"
		TIMERPROC=$!
	fi	
}
UnsetTimer(){
	kill $TIMERPORC
}
#main
trap AlarmHandler 14
SetTimer 15
$PROG &
CHPROCIDS="$CHPROCIDS $!"
wait $!
UnsetTimer
echo "All Done"
exit 0
