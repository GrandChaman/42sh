#!/bin/bash
RED="\033[1;31"m
GREEN="\033[1;32m"
NC="\033[0m"

function check_if_ok {
eval $1
if [ $? -ne 0 ]
then
	echo -e "$> $1" $RED " KO " "$NC"
	exit 1
else
	echo -e "$> $1" $GREEN " OK " "$NC"
fi
}

check_if_ok "diff <(./42sh test/basics) <(bash -- test/basics)"
