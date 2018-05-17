#!/bin/bash
RED="\033[1;31"m
GREEN="\033[1;32m"
NC="\033[0m"

function check_if_ok {
eval $1
last_val=$?
if [ $last_val -ne 0 ]
then
	echo -e "$> $1" $RED "\tKO " "$NC"
	exit $last_val
else
	echo -e "$> $1" $GREEN "\tOK " "$NC"
fi
}

check_if_ok "diff <(./42sh test/basics) <(bash -- test/basics)"
check_if_ok "diff <(./42sh test/builtins) <(bash -- test/builtins)"
check_if_ok "diff <(./42sh test/path) <(cat test/path_correct)"
check_if_ok "diff <(./42sh test/pipe) <(bash -- test/pipe)"
check_if_ok "diff <(./42sh test/redirections 0) <(bash -- test/redirections 1)"
check_if_ok "diff <(./42sh test/logical_operator) <(bash -- test/logical_operator)"
check_if_ok "diff <(./42sh test/separator) <(bash -- test/separator)"
check_if_ok "diff <(./42sh test/backquote 2>&-) <(bash -- test/backquote 2>&-)"
