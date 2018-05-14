#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "******** Starting ********"
for script in shtest/*.sh ; do
	echo "******** " $script " ********"
	./42sh $script
	if [ $? -ne 0 ] ;
	then
		exit $?
	fi
done
