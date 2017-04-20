/* EXERCICE 7 */
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "Graphe.h"
#include "Struct_File.h"
#include "evaluation_NChaines.h"

void show_path(int *pred, int u, int v, FILE *f, Graphe *G, double *total_size, int *gammaMax)
{
  if (u != v)
    {
      show_path(pred, u, pred[v - 1], f, G, total_size, gammaMax);
      Arete *arr = acces_arete(G, pred[v-1], v);
      if (arr != NULL)
  	{
  	  *total_size += arr->longueur;
  	  arr->calc_gamma++;
  	  if (arr->calc_gamma > *gammaMax)
  	    *gammaMax = arr->calc_gamma;
  	}
    }
  fprintf(f, "%d ", v);
}

/* indices avec -1 => numerotation noeud commence à 1 */
int courtCheminLargeur(Graphe *G, int s, int dest, FILE *f, double *total_size, int *gammaMax)
{
  int i, t, origin = s;
  int *visit;
  S_file F;
  Cellule_arete *voisin;
  
  if ((visit = malloc(sizeof(int)*G->nbsom)) == NULL)
    return -1;
  for (i=0 ; i<G->nbsom ; i++)
    visit[i] = -1;
  visit[s-1] = 0;
  
  Init_file(&F);
  enfile(&F, s);
  
  while (!(estFileVide(&F)))
    {
      s = defile(&F);
      voisin = (G->T_som)[s]->L_voisin;
      while (voisin)
	{
	  if (voisin->a->u == (G->T_som)[s]->num)
	    t = voisin->a->v;
	  else
	    t = voisin->a->u;
	  if (visit[t-1] == -1 )
	    {
	      visit[t-1] = s;
	      enfile(&F, t);
	    }
	  voisin = voisin->suiv;
	}
    }
  
  show_path(visit, origin, dest, f, G, total_size, gammaMax);
  fprintf(f, "-1\n");
  t = visit[dest-1];
  free(visit);
  return t;
}

int genereCheminMinCommodite(Graphe *G, char *file, int option)
{
  int i, u, v, gammaMax=0;
  FILE *f;
  double total_size = 0;
  char filenamencha[205];

  strcpy(filenamencha,"Output/\0");
  strcat(filenamencha,file);
  strcat(filenamencha,".ncha");
  
  if ((f=fopen(filenamencha,"w")) == NULL)
    return 1;
  for (i=0 ; i<G->nbcommod ; i++)
    {
      u = G->T_commod[i].e1;
      v = G->T_commod[i].e2;
      courtCheminLargeur(G, u, v, f, &total_size, &gammaMax);
    }
  fclose(f);

  if (option == 1)
    {
      printf("Total size : %.2f\t", total_size);
      printf("Gamma max : %d\n", gammaMax);
      printf("evaluation %s : %.2f/100\n", file, evaluation_NChaines(gammaMax,total_size,file));
    }
  return 0;
}
