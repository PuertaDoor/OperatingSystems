#!/usr/bin/env bash

if (( $# != 2 ))
then
  echo "Nombre d'arguments different de 2">&2
  exit 1
else
  if ( [ ! -f $1 ] || [ ! -f $2 ] )
  then
    echo "Un des deux arguments n'est pas chemin vers fichier existant">&2
    exit 1
  fi
fi

exec 3<$1
exec 4<$2
while true
do
  cpt=0
  if read line1 <&3
  then
    echo "$line1"
  else
    ((cpt++))
  fi
  if read line2 <&4
  then
    echo "$line2"
  else
    ((cpt++))
  fi
  if (( $cpt == 2 ))
  then
    exit 0
  fi
done
