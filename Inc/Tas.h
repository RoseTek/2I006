#ifndef TAS__H_
# define TAS__H_

#include "Graphe.h"

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
double getNextDist(Tas *tas);
void insereElem(Tas *tas, int num_sommet, double dist);
void libereTas(Tas *tas);
Sommet *rechercheSommet(int sommet, Graphe *G);

#endif
