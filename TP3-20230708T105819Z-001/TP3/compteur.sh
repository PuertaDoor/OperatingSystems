#!/usr/bin/env bash

# traite le cas dans lequel les arguments du script sont erronés
if (( $# != 2 || $2 < 1 ))
then
  echo "Usage : $0 <chemin vers fic> <entiersupa0>" >&2
  exit 1
else
  if ( [ -d $1 ] )
  then
    echo "Le premier argument ne doit pas etre un chemin vers un repertoire existant">&2
    exit 1
  fi
fi

echo $2 >$1
while (( $(cat $1) != 0 ))
do
  read m <$1
  m=$(expr $m - 1)
  echo $m >$1
  sleep 1
done

echo "Le script a termine son execution."
exit 0
