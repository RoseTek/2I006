#ifndef SHORTPATH_H_
#define SHORTPATH_H_

#include "Graphe.h"

int genereCheminMinCommodite(Graphe *G, char *file, int option);
int djikstraMinCommodite(Graphe *G, char *file);
int shortPathAmeliore(Graphe *G, char *file);
void show_path(int *pred, int u, int v, FILE *f, Graphe *G, double *total_size, int *gammaMax);

#endif
