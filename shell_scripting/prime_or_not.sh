#!/bin/bash

echo "Enter a number"
read num

if [ $num -lt 2 ]; then
    echo "$num is not prime"
    exit
fi

is_prime=1

for(( i=2;i<=n/2;i++))
do
    if(( num%i == 0)); then
        is_prime=0
        break
    fi
done

if [ $is_prime -eq 1 ]; then
    echo "$num is prime"
else
    echo "$num is not prime"
fi