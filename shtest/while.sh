i=0;
j=0;
k=0;
while [ $i -lt 10 ];
do
	while [ $j -lt 10 ];
	do
		until ! [ $k -lt 10 ];
		do
			echo "I: $i, J: $j, K: $k";
			k=$(($k + 1));
		done;
		k=0;
		j=$(($j + 1));
	done;
	j=0;
	i=$(($i + 1));
done;
