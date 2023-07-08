#include "liste.h"

liste creer_liste_vide(){
  return NULL;
}

int est_liste_vide(liste l){
  return l==creer_liste_vide();
}

int taille_liste(liste l){
  if (est_liste_vide(l)){
    return 0;
  }
  else {
    return 1+taille_liste(l->suivant);
  }
}

int appartient(liste l, element elem){
  if (est_liste_vide(l)){
    return 0;
  }
  else if (l->objet==elem){
    return 1;
  }
  else {
    appartient(l->suivant,elem);
  }
}

liste inserer_element_liste(liste l, element elem){
  liste lnew = (liste)allocation_mem(1,sizeof(struct_cellule));
  lnew->objet = elem;
  lnew->suivant=l;
  return lnew;
}

liste inserer_element_liste_fin(liste l, element elem){
  liste lnew = inserer_element_liste(creer_liste_vide(),elem);
  liste p=l;
  if (est_liste_vide(l)){
    return lnew;
  }
  else {
    while (!est_liste_vide(p->suivant)){
      p = p->suivant;
    }
    p->suivant = lnew;
    return l;
  }
}

element renvoie_premier_liste(liste l){
  if (est_liste_vide(l)){
    fprintf(stderr,"Erreur la liste est vide dans la fonction renvoie_premier\n");
    exit(EXIT_FAILURE);
  }
  return l->objet;
}

element renvoie_dernier_liste(liste l){
  if (est_liste_vide(l)){
    fprintf(stderr,"Erreur la liste est vide dans la fonction renvoie_dernier\n");
    exit(EXIT_FAILURE);
  }
  if (l->suivant==creer_liste_vide()){
    return l->objet;
  }
  else {
    renvoie_dernier_liste(l->suivant);
  }
}

liste supprimer_dernier_liste(liste l){
  liste p=l;
  if (est_liste_vide(p)){
    fprintf(stderr,"Erreur la liste est vide dans la fonction supprime_dernier\n");
    exit(EXIT_FAILURE);
  }
  else {
    while (!est_liste_vide(p->suivant->suivant)){
      p = p->suivant;
    }
    libere_mem(&p->suivant);
    return l;
  }
}

liste supprimer_premier_liste(liste l){
  liste lsuivant = l->suivant;
  libere_mem(&l);
  return lsuivant;
}

void detruire_liste(liste l){
  if (!est_liste_vide(l)){
    detruire_liste(l->suivant);
    libere_mem(&l);
  }
}
