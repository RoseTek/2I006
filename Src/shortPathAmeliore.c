/* EXERCICE 8 */
#include <string.h>
#include <limits.h>
#include <float.h>
#include "ShortPath.h"
#include "Tas.h"
#include "evaluation_NChaines.h"

static double distFunction(Arete *arete, double parametre)
{
  return arete->longueur + arete->calc_gamma * parametre;
}

static void majBordure(Tas *bordure, Sommet *s, double *dist, int *pred, int *marque, double parametre)
{
  int i = 0;
  Arete *arete = NULL;
  Cellule_arete *arr = s->L_voisin;

  while (arr){
    arete = arr->a;
    if (arete->u == s->num)
      i = arete->v;
    else
      i = arete->u;
    if (marque[i - 1] == 0){
      if ((dist[i - 1]) >= (dist[s->num - 1] + distFunction(arete, parametre))){
    	dist[i - 1] = dist[s->num - 1] + distFunction(arete, parametre);
    	pred[i - 1] = s->num;
    	insereElem(bordure, i, dist[i-1]);
      }
    }
    arr = arr->suiv;
  }
}

static int algoDjikstraAmeliore(Graphe *G, int r, int dest, FILE *f, double *total_size, int *gammaMax, double parametre)
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
      if (getNextDist(&bordure) > dist[dest - 1])
	break;
      sommet = popElem(&bordure);
      s = rechercheSommet(sommet, G);
      marque[sommet - 1] = 1;
      majBordure(&bordure, s, dist, pred, marque, parametre);
    }
  show_path(pred, r, dest, f, G, total_size, gammaMax);
  fprintf(f,"-1\n");
  free(pred);
  free(dist);
  free(marque);
  libereTas(&bordure);
  return 0;
}

static void reinit_gamma(Graphe *G)
{
  int i;
  Sommet **tab_sommet = G->T_som;

  for (i=1 ; i<=G->nbsom ; i++)
    {
      Cellule_arete *arr = tab_sommet[i]->L_voisin;
      while (arr)
	{
	  Arete *arete = arr->a;
	  arete->calc_gamma = 0;
	  arr = arr->suiv;
	}
    }
}

/* En commentaire : code permettant de tester différents coeff pour le gamma */
int shortPathAmeliore(Graphe *G, char *file)
{
  int i, u, v;
  FILE *f = NULL;

  char filenamencha[205];
  double parametre=100.;
  
  strcpy(filenamencha,"Output/\0");
  strcat(filenamencha,file);
  strcat(filenamencha,".ncha");
  
  if ((f=fopen(filenamencha,"w")) == NULL)
    return 1;
  /* while (parametre <= 100.) */
  /*   { */
  int gammaMax=0;
  double total_size = 0;
  for (i=0 ; i<G->nbcommod ; i++)
    {
      u = G->T_commod[i].e1;
      v = G->T_commod[i].e2;				   
      algoDjikstraAmeliore(G, u, v, f, &total_size, &gammaMax, parametre);
    }
  fclose(f);
  
  printf("\tParametre %.2f\n", parametre);
  printf("Total size : %.2f\t", total_size);
  printf("Gamma max : %d\n", gammaMax);
  printf("evaluation %s : %.2f/100\n\n", file, evaluation_NChaines(gammaMax,total_size,file));
  /* reinit_gamma(G); */
  /*   parametre += 10.; */
  /* } */
  
  return 0;
}
