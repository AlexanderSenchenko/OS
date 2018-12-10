#!/bin/bash

printf '%b' 'Введите команду: '
read answer

if [[ -n $answer ]] ; then
	$answer
else
	printf '%b\n' "Error"
fi

# eval $answer
# $answer

a=5
b=a
c='$'$b
echo $c

eval c='$'$b
echo $c
