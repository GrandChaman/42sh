target=$1;
i=2;

while [ $(($i * $i)) -lt $target ];
do
    if [ $(($target % $i)) -eq 0 ];
    then
        echo "$target is not prime";
        exit;
    else
        i=$(($i + 1));
    fi;
done;
echo "$target is prime"
