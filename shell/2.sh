#!/bin/bash
echo "PID of 2.sh:$$"
echo "2.sh get \$A=$A from 1.sh"
A=C
export A
echo "2.sh:\$A is $A"
