#!/usr/bin/env bash

if (( $# != 0 ))
then
  for i in $*
  do
    echo "Hello $i !"
  done
else
  echo "May the force be with you !"
fi
