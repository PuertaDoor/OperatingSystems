#!/usr/bin/env bash

# Auteur : Léo PORTE

function A(){
  if (( $(cat $FAV | grep -c "^$1 ") != 0 ))
  then
    echo "Le raccourci $1 existe déjà (taper L pour vérifier son raccourci)"
  else
    echo "$1 -> $(pwd)" >>$FAV
    echo "Le répertoire $(pwd) est sauvegardé dans vos favoris."
    echo "raccourci : $1"
  fi
}

function C(){
  nbrac=$(cat $FAV | cut -d' ' -f1 | grep -c "$1")
  nomrac=$(cat $FAV | cut -d' ' -f1 | grep "$1")
  if (( $nbrac == 0 ))
  then
    echo "Le favori '$1' n'existe pas"
  else
    if (( $nbrac == 1 ))
    then
      rep=$(cat $FAV | grep "^$nomrac " | cut -d' ' -f3)
      cd $rep
      echo "Vous êtes maintenant dans le répertoire $rep"
    else
      echo "Trop de raccourcis liés à ce paterne."
    fi
  fi
}

function R(){
  if (( $(cat $FAV | grep -c "^$1 ") != 0 ))
  then
    ligne=$(cat $FAV | grep -n "^$1 " | cut -d: -f1)
    sed -i "$ligne d" $FAV
    echo "Le favori '$1' est supprimé de votre liste."
  else
    echo "Le favori '$1' n'existe pas"
  fi
}

function L(){
  if (( $# != 1 ))
  then
    cat $FAV | column -t
  else
    listejuste=$(cat $FAV | cut -d' ' -f1 | grep $1)
    while read line
    do
      for i in $listejuste
      do
        if (( $(echo "$line" | grep -c "^$i ") != 0 ))
        then
          echo "$line"
        fi
      done
    done < $FAV
  fi
}

function Q(){
  if (( $# != 2 ))
  then
    echo "Usage : $0 <nomrac1> <nomrac2>"
  else
    sed -i "s/^$1/$2/" $FAV
  fi
}
