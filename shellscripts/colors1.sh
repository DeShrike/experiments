#! /bin/bash

RED="\e[31m"
GREEN="\e[32m"
ENDCOLOR="\e[0m"

echo -e "${RED}This is some red text, ${ENDCOLOR}"
echo -e "${GREEN}And this is some green text${ENDCOLOR}"

for i in {16..21} {21..16} ; do
   echo -en "\e[38;5;${i}m#\e[0m" ;
done ;
echo

for i in {16..21} {21..16} ; do
   echo -en "\e[48;5;${i}m \e[0m" ;
done ;
echo

echo -e "\e[1;4mBold and Underlined"
echo -e "\e[1;31;42m Yes it is awful \e[0m"

