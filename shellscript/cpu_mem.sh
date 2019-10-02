#! /bin/bash

echo $0 $1 $2 $3

#pass argument to an array
#${args[0] = $1}

args=("$@")

echo ${args[0]} ${args[1]} ${args[2]}
echo ${args[@]}
echo $@
#argc:
echo $#


