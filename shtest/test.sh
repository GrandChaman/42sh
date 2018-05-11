x=$1;
echo $2;
while [ $x -ne 1 ];
do
    echo $x;
    if [ $(($x % 2)) -eq 0 ];
    then
        x=$(($x / 2));
    else
        x=$(($x * 3 + 1));
    fi;
done
