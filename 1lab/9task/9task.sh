#!/bin/bash

while getopts c:m:n: opt ; do
	case $opt in
		c)
			if [[ -n $OPTARG ]] ; then
				mask=$OPTARG
			fi

			if [[ -e $mask ]] ; then
				printf '%b\n' 'Куда копировать: '
				read answer
				cp $mask $answer
			fi
		;;
		m)
			if [[ -n $OPTARG ]] ; then
				mask=$OPTARG
			fi

			if [[ -e $mask ]] ; then
				rm $mask
			fi
		;;
		n)
			if [[ -n $OPTARG ]] ; then
				mask=$OPTARG
			fi

			if [[ -e $mask ]] ; then
				printf '%b\n' 'Новое имя: '
				read answer
				mv $mask $answer
			fi
		;;
	esac
done

