#!/bin/bash

SELECTION=$(whiptail --title "The Main Menu" --menu "Arrow/Enter Selects or Tab Key" 0 0 0 --cancel-button Quit --ok-button Select \
"a OPTION_1 " "This is option 1" \
"b OPTION_2 " "This is option 2" \
"c OPTION_3 " "This is option 3" \
"q QUIT" "Exit"  3>&1 1>&2 2>&3)

RET=$?
if [ $RET -eq 1 ]; then
	exit 0
elif [ $RET -eq 0 ]; then
	case "$SELECTION" in
	  a\ *) echo "A" ;;
	  b\ *) echo "B" ;;
	  c\ *) echo "C" ;;
	  d\ *) echo "D" ;;
	  e\ *) echo "E" ;;
	  f\ *) echo "F" ;;
	  g\ *) echo "G" ;;
	  h\ *) echo "H" ;;
	  i\ *) echo "I" ;;
	  j\ *) echo "J" ;;
	  k\ *) echo "K" ;;
	  l\ *) echo "L" ;;
	  q\ *) echo "Q" ;;
	     *) whiptail --msgbox "Programmer error: unrecognised option" 20 60 1 ;;
	esac || whiptail --msgbox "There was an error running selection $SELECTION" 20 60 1
fi
