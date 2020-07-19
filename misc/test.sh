#!/bin/bash

BLACK="\e[1;30m"
RED="\e[1;31m"
GREEN="\e[1;32m"
YELLOW="\e[1;33m"
BLUE="\e[1;34m"
PURPLE="\e[1;35m"
CYAN="\e[1;36m"
WHITE="\e[1;37m"

RESET="\e[0m"

echo 'Hello'
echo -e "You are ${CYAN}${USER}${RESET} !"
echo -e "This computer is called ${YELLOW}${HOSTNAME}${RESET}"
TEMPERATURE=$(vcgencmd measure_temp)
echo -e "The temperature of the CPU is ${PURPLE}${TEMPERATURE}${RESET}"
echo " "
echo -e "This is ${BLACK}BLACK${RESET}."
echo -e "This is ${RED}RED${RESET}."
echo -e "This is ${GREEN}GREEN${RESET}."
echo -e "This is ${YELLOW}YELLOW${RESET}."
echo -e "This is ${BLUE}BLUE${RESET}."
echo -e "This is ${PURPLE}PURPLE${RESET}."
echo -e "This is ${CYAN}CYAN${RESET}."
echo -e "This is ${WHITE}WHITE${RESET}."
echo " "
echo -e "${WHITE}Memory:${RESET}"
free -h
echo -e "${WHITE}Disk Usage:${RESET}"
df -h
echo -e "${WHITE}Uptime:${RESET}"
uptime

LOCALIP="$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1')"

echo -e "Your local IP is ${GREEN}${LOCALIP}${RESET}"

myFunc() {

echo "Hello ${RED}Hello ${YELLOW}World${RESET}."
sudo apt-get autoremove -yy
sudo apt-get autoclean

}

if [ "$1" == "--clean" ]; then
  myFunc
  exit
fi

if [ -n "$1" ]; then
  echo "Try with argument --clean"
  exit 1
fi

echo "Usage: ./test.sh --clean" >&2

for PARA in [1,2]
  do
    echo -e "Para = ${BLUE} ${PARA}  ${RESET}"
  done

read -n 1 -s choice;
  case $choice in
    1) echo "You pressed 1" ;;
    2) echo "You pressed 2" ;;
    *) echo "You pressed something else" ;;
  esac



