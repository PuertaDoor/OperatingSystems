#!/usr/bin/env bash

if (( $# != 2 ))
then
  echo "Mauvais nombre d'arguments ! Il en faut deux">&2
  exit 1
else
  if ( [ ! -f $2 ] || [ -d $2 ] )
  then
    echo "Le premier argument ne correspond pas à un fichier existant ou correspond à un répertoire">&2
    exit 1
  fi
fi


compteur=1
while read line
do
  echo "$compteur : $line" >&1
  ((compteur++))
done < $2
exit 0
