#!/bin/bash

if [ -n "$1" ] ; then
	if [ -n "$2" ] ; then
		cat $1 >> $2
	fi
fi

if [ -n "$3" ] ; then
	last >> $3
fi
