for((i=0;i<100;i++)); do
#    $rnd = $(($RANDOM % 100)) 
#    echo "100 2 $rnd"
#    echo $rnd
    echo "2000000 3" > in
    echo $i >> in
    ./a.out < in || break 
done;
