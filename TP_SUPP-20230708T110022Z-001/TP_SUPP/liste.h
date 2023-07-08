#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdio.h>
#include <stdlib.h>
#include "allocation.h"

typedef int element;

typedef struct cellule {
  element objet;
  struct cellule * suivant;
} struct_cellule;

typedef struct_cellule * liste;

/* renvoie la liste vide */
liste creer_liste_vide();

/* teste si une liste est vide */
int est_liste_vide(liste l);

/* renvoie la taille de la liste l */
int taille_liste(liste l);

/* renvoie 1 si elem appartient a la liste l et 0 sinon */
int appartient(liste l, element elem);

/* ajoute un element elem a la liste l */
liste inserer_element_liste(liste l, element elem);

/* ajoute un element elem a la fin de la liste l */
liste inserer_element_liste_fin(liste l, element elem);

/* renvoie le premier element de la liste l */
element renvoie_premier_liste(liste l);

/* renvoie le dernier element de la liste l */
element renvoie_dernier_liste(liste l);

/* supprime la premiere cellule de la liste l */
liste supprimer_premier_liste(liste l);

/* supprime la derniere cellule de la liste l */
liste supprimer_dernier_liste(liste l);

/* detruit la liste l */
void detruire_liste(liste l);

#endif
