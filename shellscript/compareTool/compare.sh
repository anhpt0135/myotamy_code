#!/bin/bash

age=25

if [[ "$age" -lt 18
    || "$age" -gt 30 ]]
then
    echo "valid age"
else
    echo "age not valid"
fi

num1=100
num2=500

num3=$num1 + $num2

echo $num3
echo $(( $num1 + $num2 ))
echo "scale=2;sqrt($num1)" | bc -l
