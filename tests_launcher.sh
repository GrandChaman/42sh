#!/bin/bash
RED="\033[1;31"m
GREEN="\033[1;32m"
NC="\033[0m"

function check_if_ok {
eval $1
last_val=$?
if [ $last_val -ne 0 ]
then
	echo -e "$> $1" $RED " KO " "$NC"
	exit $last_val
else
	echo -e "$> $1" $GREEN " OK " "$NC"
fi
}

check_if_ok "diff <(./42sh test/basics) <(bash -- test/basics)"
check_if_ok "diff <(./42sh test/builtins) <(bash -- test/builtins)"
check_if_ok "diff <(./42sh test/path) <(cat test/path_correct)"
