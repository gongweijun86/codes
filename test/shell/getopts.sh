#!/bin/bash
USAGE="Usage: `basename $0` [-v] [-f] [filename] [-o] [filename]";
VERBOSE=false

while getopts f:o:v OPTION ; do
	case "$OPTION" in
		f) INFILE="$OPTARG" ;;
		o) OUTFILE="$OPTARG" ;;
		v) VERBOSE=true ;;
		\?) echo "$USAGE"
		    exit 1
		    ;;
	esac
done


shift `echo "$OPTIND - 1" | bc`
echo $*
echo $OPTIND
if [ -z "$1" -a -z "$INFILE" ]; then
	echo "ERROR: Input file was not specified."
	exit 1
fi
if [ -z "$INFILE" ]; then INFILE="$1" ; fi
: ${OUTFILE:=${INFILE}.uu}
if [ -f "$INFILE" ]; then
	if [ "$VERBOSE" = "true" ]; then
		echo "uuencoding $INFILE to $OUTFILE... \c"
	fi
	ls $INFILE ; ls $OUTFILE; RET=#?
	if [ "VERBOSE" = "true" ] ;then
		MSG="Failed" ; if [ $RET -eq 0 ] ; then MSG="Done" ; fi
		echo "$MSG"
	fi
fi
exit 0
