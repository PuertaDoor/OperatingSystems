#!/usr/bin/env bash

somme=0

if (( $# == 0 ))
then
  echo "usage : $0 <entier1> <entier2> ... <entierN>"
  exit 1
fi

for i in $*
do
  somme=$(($somme + $i))
done
echo "Somme = $somme"
