#!/bin/bash

NUM_REQUIRED_ARGS=2
num_args=$#

if [ $num_args -lt $NUM_REQUIRED_ARGS ]; then
	echo "Not enough arguments: Call this script with ${0} <name> <number>"
	exit 1
fi

name=$1
number=$2
echo "Yout first 2 arguments are: $1 $2"

echo "You gave ${num_args} arguments:"
for arg in "$@"; do
	echo "$arg"
done

spaced() {
	echo
	echo "#####################"
	echo "$1"
	echo "#####################"
	echo
}

function javatest() {
	if [[ $number -eq 99 ]]; then
		spaced "You win"
	elif (( $number < 10 )); then
		spaced "You entered a small number"
	fi
}

javatest $number
exit 0

