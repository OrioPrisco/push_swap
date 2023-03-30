#!/bin/bash

while :;
do \
	ARG=$(seq $1 $2 | shuf | tr '\n' ' ' | sed -r 's/.$//');
	RESULT=$(echo $ARG && ./push_swap $ARG | ./checker_linux $ARG)
	echo $RESULT;
	echo "$RESULT" | grep "OK"
	if [ $? -ne 0 ]; then
		exit 1;
	fi;
done
