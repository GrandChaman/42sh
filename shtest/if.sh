x=$1;
if [ $x ];
then
	echo "Input $x";
else
	x="250";
	echo "Automatic input $x";
fi;
if [ $x -lt 100 ];
then
	echo "Yes, it is under 100!";
elif [ $x -gt 1000 ];
then
	echo "Wow, big boy!";
fi;
