#!/bin/bash

name=$1

user=$(whoami)
whereami=$(pwd)

echo "Hello $name !!"
sleep 2

echo "You are logged is as $user and your currect directory is $whereami"

