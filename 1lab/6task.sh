#!/bin/bash

fname=$1

if [ -f $fname ] ; then
	cat $fname

	if [ $2 ] ; then
		# bfile="$($fname | cut -d "." -f2)" #$($fname | cut -d "." -f1)
		# printf '%b\n' $bfile
		# # printf '%b\n' "$($fname | cut -d "." -f2)"
		# gcc -Wall -o main $fname
		gcc -Wall $fname -o `basename $fname .c`

		if [ $3 ] ; then
			./`basename $fname .c`
		fi
	fi

else
	fname='.bashrc'
	cat $fname
fi
