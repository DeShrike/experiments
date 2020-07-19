#!/bin/bash

# This is a test script.

allfolders=$( /bin/ls -d */ | cut -d " " -f 1 )

echo "Folders:"
echo ${allfolders}

sleep 1

a=1234
b=4567

let "c = $a + $b"
echo "$a + $b = $c"

mynum=100

sleep 1

if [ $mynum -eq 200 ]
then
	echo "mynum is 200"
else
	echo "mynum is not 200"
fi

sleep 1

if [ -d ~/repos ]
then
	echo "There is a folder called 'repos' in my home folder"
fi

sleep 1

if [ -f ~/nohup.out ]
then
	echo "nohup.out found !!"
else
	echo "nohup.out not found"
fi

sleep 1

echo "Enter your name:"
read myname
echo "Your name is $myname"

sleep 1

ls /root 2> errors.log

sleep 1

myvar=1

while [ $myvar -le 10 ]
do
	echo "Loop $myvar"
	myvar=$(( $myvar + 1 ))
	sleep 0.2
done

sleep 1

echo "Select:"

echo "1 - Kirk"
echo "2 - Picard"
echo "3 - Janeway"
echo "4 - Sisco"

read captain

case $captain in
	1) echo "Star Trek - TOS";;
	2) echo "Star Trek - TNG";;
	3) echo "Star Trek - Voyager";;
	4) echo "Star Trek - Deep Space Nine";;
	*) echo "You fool !";;
esac

sleep 1

