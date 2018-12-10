#!/bin/bash

case $1 in
	1)
	pts="$(ps | grep --max-count=1 'pts' | awk '{print $2}')"
	ps -eo pid,uid,tty | grep -v $pts
	;;
	2)
	user="$(whoami)"
	ps -eo pid,uid,tty,user | grep $user
	;;
	3)
	pstree -p
	;;
	*)
esac