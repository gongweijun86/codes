#!/bin/bash
USAGE="Usage:`basename $0` [-t|-c] [files|dirctory]"

if [ $# -lt 2 ]; then
	echo "$USAGE"
	exit 1
fi

case "$1" in
	-t) shift ; TARGS="-tvf" ;
	for i in "$@" ; do
		if [ -f "$i" ] ; then
			FILES=`tar $TARGS "$i" 2>/dev/null` #不要输出原命令的错误输出，而是使用我们自己的
			if [ $? -eq 0 ] ; then
				echo ; echo "$i" ; echo "$FILES"
			else
				echo "ERROR:$i not a tar file"
			fi
		else
			echo "ERROR: $i not a file"
		fi
	done
	;;
	-c) shift ; TARGS="-cvf" ;
	    tar $TARGS archive.tar "$@"
	    ;;
	*) echo "$USAGE"
	   exit 0
	   ;;
esac

