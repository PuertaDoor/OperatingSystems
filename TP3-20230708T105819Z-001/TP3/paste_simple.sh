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
while read line1
do
  echo "$line1"
  read line2 <&4
  echo "$line2"
done <&3
exit 0
