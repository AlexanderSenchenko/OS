#!/bin/bash

fname=$1

if [ -f $fname ]
then
	cat $fname

	if [ $2 ]
	then
		gcc -Wall -o test_task6 test_task6.c

		if [ $3 ]
		then
			./test_task6
		fi
	fi

else
	fname='.bashrc'
	cat $fname
fi
