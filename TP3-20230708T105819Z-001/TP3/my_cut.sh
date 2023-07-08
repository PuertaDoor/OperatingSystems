#!/usr/bin/env bash

if (( $# != 2 ))
then
  echo "Mauvais nombre d'arguments ! Il en faut deux">&2
  exit 1
else
  if ( [ ! -f $2 ] || [ -d $2 ] )
  then
    echo "Le deuxieme argument ne correspond pas à un fichier existant ou correspond à un répertoire">&2
    exit 1
  fi
fi


compteur=1
while read line
do
  compt_mot=0
  for mot in $line
  do
    ((compt_mot++))
    if (( compt_mot == $1 ))
    then
      echo "$compteur : $mot"
    fi
  done
  ((compteur++))
done < $2
exit 0
