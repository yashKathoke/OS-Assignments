#!/bin/bash

read str

# Reverse manually
reversed=""
len=${#str}

for (( i=$len-1; i>=0; i-- ))
do
    reversed="$reversed${str:$i:1}"
done


if [ "$str" = "$reversed" ];
then 
    echo "string is palindrome"
else 
    echo "string is not palindrome"
fi
