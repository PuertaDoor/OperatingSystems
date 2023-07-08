#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocation.h"
#include "liste.h"

void usage(char *s){
  fprintf(stderr,"Usage : %s <algo> <nbcases> <debug> <fichier>\n",s);
  fprintf(stderr,"<algo>\n1 = FIFO\n2 = LRU\n3 = Horloge\n4 = Optimal\n\n");
  fprintf(stderr,"<debug>\n0 = affichage du nombre de defauts de page\n1 = affichage du contenu des cases a chaque etape et du defaut de page\n");
  exit(EXIT_FAILURE);
}

int somme(int *tab, int n){
  if (n<0){
    return 0;
  }
  else {
    return tab[n]+somme(tab,n-1);
  }
}

int fifo(int *acces, int *valide, int nbcases, int nbacces, int nbpages, int debug){
  int i,j;
  int defaut = 0;
  int affdefaut = 0;
  liste l = creer_liste_vide();
  for (i=0 ; somme(valide,nbpages-1)<nbcases && i<nbacces ; i++){
    if (!valide[acces[i]]){
      l = inserer_element_liste(l,acces[i]);
      valide[acces[i]] = 1;
    }
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  for (; i<nbacces ; i++){
    if (!valide[acces[i]]){
      defaut++;
      valide[renvoie_dernier_liste(l)] = 0;
      l = supprimer_dernier_liste(l);
      l = inserer_element_liste(l,acces[i]);
      valide[acces[i]] = 1;
    }
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  detruire_liste(l);
  return defaut;
}

int lru(int *acces, int *valide, int nbcases, int nbacces, int nbpages, int debug){
  int i,j;
  int * dernier_acces = (int *)allocation_mem_init0(nbpages,sizeof(int));
  int defaut = 0;
  int min=0,aremplacer=0,affdefaut=0;
  for (i=0 ; somme(valide,nbpages-1)<nbcases && i<nbacces ; i++){
    if (!valide[acces[i]])
      valide[acces[i]] = 1;
    dernier_acces[acces[i]] = i;
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  for (; i<nbacces ; i++){
    dernier_acces[acces[i]] = i;
    if (!valide[acces[i]]){
      defaut++;
      min = dernier_acces[acces[i]];
      for (j=0 ; j<nbpages ; j++){
        if (dernier_acces[j]<min && valide[j]){
          min = dernier_acces[j];
          aremplacer = j;
        }
      }
      valide[aremplacer] = 0;
      valide[acces[i]] = 1;
    }
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  libere_mem(&dernier_acces);
  return defaut;
}

int horloge(int *acces, int *valide, int nbcases, int nbacces, int nbpages, int debug){
  int i,j;
  liste l = creer_liste_vide();
  liste p = NULL; /* pointeur sur la page */
  int * b_acces = (int *)allocation_mem_init0(nbpages,sizeof(int));
  int defaut=0,affdefaut=0;
  for (i=0 ; somme(valide,nbpages-1)<nbcases && i<nbacces ; i++){
    b_acces[acces[i]] = 1;
    if (!valide[acces[i]]){
      valide[acces[i]] = 1;
      l = inserer_element_liste_fin(l,acces[i]);
    }
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  p=l;
  for (; i<nbacces ; i++){
    if (!valide[acces[i]]){
      defaut++;
      while (b_acces[p->objet]){
        b_acces[p->objet] = 0;
        if (est_liste_vide(p->suivant)){
          p = l;
        }
        else {
          p = p->suivant;
        }
      }
      valide[p->objet] = 0;
      p->objet = acces[i];
      valide[acces[i]] = 1;
      if (est_liste_vide(p->suivant)){
        p = l;
      }
      else {
        p = p->suivant;
      }
    }
    b_acces[acces[i]] = 1;
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  libere_mem(&b_acces);
  detruire_liste(l);
  return defaut;
}

int optimal(int *acces, int *valide, int nbcases, int nbacces, int nbpages, int debug){
  int i,j;
  int aremplacer=0;
  liste l = creer_liste_vide();
  int defaut=0,affdefaut=0;
  for (i=0 ; somme(valide,nbpages-1)<nbcases && i<nbacces ; i++){
    if (!valide[acces[i]]){
      valide[acces[i]] = 1;
    }
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  for (; i<nbacces ; i++){
    if (!valide[acces[i]]){
      defaut++;
      l = creer_liste_vide();
      for (j=i+1 ; j<nbacces ; j++){
        if (valide[acces[j]]){
          aremplacer = acces[j];
          if (!appartient(l,acces[j]))
            l = inserer_element_liste(l,acces[j]);
        }
      }
      if (taille_liste(l)!=nbcases){
        for (j=0 ; j<nbpages ; j++){
          if (!appartient(l,j) && valide[j]){
            aremplacer = j;
            break;
          }
        }
      }
      valide[aremplacer] = 0;
      valide[acces[i]] = 1;
      detruire_liste(l);
    }
    if (debug){
      printf("Numeros des pages en RAM (si * a la fin : defaut de page) : ");
      for (j=0 ; j<nbpages ; j++){
        if (valide[j]){
          printf("%d ",j);
        }
      }
      if (affdefaut!=defaut){
        printf("*");
      }
      printf("\n");
      affdefaut = defaut;
    }
  }
  return defaut;
}

int main(int argc, char *argv[]){
  FILE* fichier = NULL;
  int *acces = NULL;
  int *valide = NULL;
  int *p = NULL;
  int nbcases,nbpages,nbacces,debug,choixalgo;
  if (argc < 5 || strcmp(argv[1],"-h")==0 || strcmp(argv[1],"-help")==0){
    usage(argv[0]);
  }
  choixalgo = atoi(argv[1]);
  nbcases = atoi(argv[2]);
  debug = atoi(argv[3]);
  if ((fichier = fopen(argv[4],"r"))==NULL){
    fprintf(stderr,"Fichier inexistant ou errone\n");
    return EXIT_FAILURE;
  }
  if (fscanf(fichier,"%d",&nbacces)!=1){
    fprintf(stderr,"Erreur premiere ligne fichier\n");
    return EXIT_FAILURE;
  }
  if (fscanf(fichier,"%d",&nbpages)!=1){
    fprintf(stderr,"Erreur deuxieme ligne fichier\n");
    return EXIT_FAILURE;
  }
  acces = (int *)allocation_mem(nbacces,sizeof(int));
  p = acces;
  valide = (int *)allocation_mem_init0(nbpages,sizeof(int));
  while (fscanf(fichier,"%d",p)==1){
    p++;
  }
  fclose(fichier);
  switch(choixalgo){
    case 1:
           printf("Nombre de defauts de page algorithme FIFO : %d\n",fifo(acces,valide,nbcases,nbacces,nbpages,debug));
           break;
    case 2:
           printf("Nombre de defauts de page algorithme LRU : %d\n",lru(acces,valide,nbcases,nbacces,nbpages,debug));
           break;
    case 3:
           printf("Nombre de defauts de page algorithme de l'horloge : %d\n",horloge(acces,valide,nbcases,nbacces,nbpages,debug));
           break;
    case 4:
           printf("Nombre de defauts de page algorithme optimal : %d\n",optimal(acces,valide,nbcases,nbacces,nbpages,debug));
           break;
    default:
            libere_mem(&acces);
            libere_mem(&valide);
            fprintf(stderr,"Mauvais nombre pour l'algo a choisir (entrer un nombre entre 1 et 4)\n");
            return EXIT_FAILURE;
  }
  libere_mem(&acces);
  libere_mem(&valide);
  return EXIT_SUCCESS;
}
