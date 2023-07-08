#!/usr/bin/env bash

if (($# < 4))
then
  echo "Usage : $0 <nbcases> <debug> <nbacces> <nbpages>"
  exit 1
fi

echo "$3" >> test.txt
echo "$4" >> test.txt

i=0

while (($i < $3))
do
  echo "$((RANDOM % $4))" >> test.txt
  ((i++))
done

for j in {1..4}
do
  SECONDS=0
  ./algo_remplacement_page $j $1 $2 test.txt
  echo $SECONDS
done

rm test.txt
