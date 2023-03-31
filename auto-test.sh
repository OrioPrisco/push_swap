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
	RESULT=$(valgrind ./push_swap $ARG 2>&1 > /dev/null)
	echo "$RESULT" | grep "no leaks are possible"
	if [ $? -ne 0 ]; then
		exit 1;
	fi;
	echo "$RESULT" | grep "0 errors"
	if [ $? -ne 0 ]; then
		exit 1;
	fi;
done
