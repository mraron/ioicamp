for((i=0;i<10000;i++)); do
    echo $i
    ./a.out $i <<< "1231243353443345325325" || break;
    
done ;