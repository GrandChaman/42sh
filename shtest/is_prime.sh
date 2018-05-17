target=$1;
i=2;
if [ $# -lt 1 ];
then
	echo you need an argument;
	exit 1;
fi;
while [ $(($i * $i)) -le $target ];
do
    if [ $(($target % $i)) -eq 0 ] || [ $target -eq 1 ];
    then
        echo "$target is not prime";
        exit;
    else
        i=$(($i + 1));
    fi;
done;
echo "$target is prime"
