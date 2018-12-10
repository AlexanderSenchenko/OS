#!/bin/bash

fname=$1
# echo $1

var=""
while [ -n "$2" ] ; do 
	# echo $2
	var=$var" "$2
	shift
done

# echo $var
# echo $1

tar -czf $fname.tar.gz $var