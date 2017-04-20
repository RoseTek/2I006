/* EXERCICE 8 */
#include <string.h>
#include <limits.h>
#include <float.h>
#include "ShortPath.h"
#include "Tas.h"
#include "evaluation_NChaines.h"

void majBordure(Tas *bordure, Sommet *s, double *dist, int *pred, int *marque)
{
  int i;
  Arete *arete;
  Cellule_arete *arr = s->L_voisin;

  while (arr) {
    arete = arr->a;
    if (arete->u == s->num)
      i = arete->v;
    else
      i = arete->u;
    if (marque[i - 1] == 0)
      {
	if ((dist[i - 1]) >= (dist[s->num - 1] + arete->longueur)) {
	  dist[i - 1] = dist[s->num - 1] + arete->longueur;
	  pred[i - 1] = s->num;
	  insereElem(bordure, i, dist[i-1]);
	}
      }
    arr = arr->suiv;
  }
}

Sommet *rechercheSommet(int sommet, Graphe *G)
{
  int i;
  Sommet **tab_sommet = G->T_som;

  for (i=1 ; i<=G->nbsom ; i++)
    {
      if ((tab_sommet[i])->num == sommet)
	return tab_sommet[i];
    }
  return NULL;
}

int algoDjikstra(Graphe *G, int r, int dest, FILE *file, double *total_size, int *gammaMax)
{
  int i, sommet;
  int *pred, *marque;
  double *dist;
  Tas bordure;
  Sommet *s;

  /* init */
  dist = malloc(sizeof(double) * G->nbsom);
  pred = malloc(sizeof(int) * G->nbsom);
  marque = malloc(sizeof(int) * G->nbsom);
  creationTas(&bordure, G);
  if (!dist || !pred || !marque || !bordure.tab) {
    printf("Allocation failed\n");
    return 1;
  }
  for (i=0 ; i<G->nbsom ; i++) {
    dist[i] = DBL_MAX;
    pred[i] = -1;
    marque[i] = 0;
  }

  /* algo */
  insereElem(&bordure, r, 0);
  marque[r - 1] = 1;
  dist[r - 1] = 0;
  while (taille(&bordure) > 0)
    {
      sommet = popElem(&bordure);
      s = rechercheSommet(sommet, G);
      marque[sommet - 1] = 1;
      majBordure(&bordure, s, dist, pred, marque);
    }
  show_path(pred, r, dest, file, G, total_size, gammaMax);
  /* printf("-1\n"); */
  free(pred);
  free(dist);
  free(marque);
  return 0;
}

int djikstraMinCommodite(Graphe *G, char *file)
{
  int i, u, v, gammaMax=0;
  FILE *f = NULL;
  double total_size = 0;
  
  /* ouverture file */
  for (i=0 ; i<G->nbcommod ; i++)
    {
      u = G->T_commod[i].e1;
      v = G->T_commod[i].e2;
      /* printf("\tGO %d %d\n", u, v); */
      algoDjikstra(G, u, v, f, &total_size, &gammaMax);
      /* printf("\tNEXT\n\n"); */
    }
  /* fclose(f); */

  
  printf("Total size : %.2f\t", total_size);
  printf("Gamma max : %d\n", gammaMax);
  printf("evaluation %s : %.2f/100\n", file, evaluation_NChaines(gammaMax,total_size,file));
  

  return 0;
}
