#!/bin/bash
let min=$1
let max=$2
let step=($max-$min)/10
#echo "step:"$step

while [ $min -le $max ]
do
	#echo "min:"$min
	./lab1-par-1 $min
	min=$(($min+$step))
done
