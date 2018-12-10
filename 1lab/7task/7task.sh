#!/bin/bash

# ls *.c
# for file in *c
# do

# 	printf '%b\n' $file
# done

select file in *c ; do 
	gcc -Wall $file -o `basename $file .c` #2> test.txt
	./`basename $file .c`
done
