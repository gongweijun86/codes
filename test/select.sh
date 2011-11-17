#!/bin/bash
select COMPONENT in comp1 comp2 comp3 all none
do
    case $COMPONENT in
	    comp1|comp2|comp3) echo "choose $COMPONENT"
	    ;;
	    all) echo "choose comp1,comp2,comp3" ;;
	    none) break ;;
	    *) echo "error:invalid selection.$REPLY." ;;
    esac
done
