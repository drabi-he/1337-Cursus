#!/bin/bash
x=1
rm -rf file
while [ $x -le 250000 ]
do
  echo $x >> file
  x=$(( $x + 1 ))
done
