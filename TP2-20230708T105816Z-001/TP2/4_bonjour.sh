#!/usr/bin/env bash

j=0
if (( $# != 0 ))
then
  for i in $*
  do
    if (( j%2 == 0 ))
    then
      echo "Hello $i !"
    fi
    j=$(($j + 1))
  done
else
  echo "May the force be with you !"
fi
