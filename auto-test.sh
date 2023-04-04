#!/bin/bash

while :;
do \
	ARG=$(seq $1 $2 | shuf | tr '\n' ' ' | sed -r 's/.$//')
	RESULT=$(./push_swap $ARG | ./checker_linux $ARG)
	echo "$RESULT" | grep "OK" > /dev/null
	if [ $? -ne 0 ]; then
		echo "linux checker gave an error for the following args : $ARG"
		echo "$RESULT"
		exit 1;
	fi;
	RESULT=$(valgrind ./push_swap $ARG 2>&1 > /dev/null)
	echo "$RESULT" | grep "no leaks are possible" > /dev/null
	if [ $? -ne 0 ]; then
		echo "valgrind shows leaks for the following args : $ARG"
		echo "$RESULT"
		exit 1;
	fi;
	echo "$RESULT" | grep "0 errors" > /dev/null
	if [ $? -ne 0 ]; then
		echo "valgrind shows errors for the following args : $ARG"
		echo "$RESULT"
		exit 1;
	fi;
	RESULT=$(./push_swap $ARG | ./checker $ARG)
	echo "$RESULT" | grep "OK" > /dev/null
	if [ $? -ne 0 ]; then
		echo "own checker gave an error for the following args : $ARG"
		echo "$RESULT"
		exit 1;
	fi;
	echo "test passed"
done
