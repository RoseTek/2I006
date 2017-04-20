#ifndef TAS__H_
# define TAS__H_

#include "Graphe.h"

/* TAS A REALISER APRES */

typedef struct elemTas{
  int s;
  double dist;
} Elem_Tas;

typedef struct tas {
  int n;
  Elem_Tas *tab;
  int max;
} Tas;

int taille(Tas *tas);
void creationTas(Tas *tas, Graphe *G);
int popElem(Tas *tas);
/* int estPresent(Tas *tas, int elem); */
void insereElem(Tas *tas, int num_sommet, double dist);
void libereTas(Tas *tas);

#endif