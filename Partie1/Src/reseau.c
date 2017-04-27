#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "entree_sortie.h"
#include "SVGwriter.h"
#include "Reseau.h"

#define SIZE 700

int nbCommodite(Reseau *R)
{
  CellCommodite *com;
  int count = 0;
  
  if (!R)
    return 0;
  com = R->commodites;
  while (com)
    {
      count++;
      com = com->suiv;
    }
  return count;
}

int nbLiaison(Reseau *R)
{
  int cpt = 0;
  CellNoeud *noeuds;
  CellNoeud *voisins;
  
  if (!R)
    return 0;
  noeuds = R->noeuds;
  while (noeuds)
    {
      voisins = noeuds->nd->voisins;
      while (voisins)
	{
	  cpt++;
	  voisins = voisins->suiv;
	}
      noeuds = noeuds->suiv;
    }
  return cpt/2;
}

void ecrireReseauTxt(Reseau *R, FILE*f)
{  
  CellCommodite *cd;
  CellNoeud *nd;
  CellNoeud *voisins;

  if (!R || !f) return ;
  fprintf(f, "NbNoeuds: %d\nNbLiaison: %d\nNbCommodite: %d\nGamma: %d\n\n", R->nbNoeuds, nbLiaison(R), nbCommodite(R), R->gamma);
  nd = R->noeuds;
  while (nd)
    {
      fprintf(f,"v %d %.2f %.2f\n", nd->nd->num, nd->nd->x, nd->nd->y);
      nd = nd->suiv;
    }
  fprintf(f,"\n");
  nd = R->noeuds;
  while (nd)
    {
      voisins = nd->nd->voisins;
      while (voisins)
	{
	  if (voisins->nd->num < nd->nd->num) //affiche une seule des paires
	    fprintf(f, "l %d %d\n", voisins->nd->num, nd->nd->num);
	  voisins = voisins->suiv;
	}
      nd = nd->suiv;
    }
  fprintf(f,"\n");  
  cd = R->commodites;
  while (cd)
    {
      fprintf(f, "k %d %d\n", cd->extrA->num, cd->extrB->num);
      cd = cd->suiv;
    }
  fprintf(f,"\n");
}

void reseauCoordMinMax(Reseau *R, double *xmin, double *ymin, double *xmax, double *ymax)
{
  CellNoeud *noeud = R->noeuds;

  *xmin = DBL_MAX;
  *ymin = DBL_MAX;
  *xmax = 0;
  *ymax = 0;
  while (noeud)
    {
      if (*xmin > noeud->nd->x)
	*xmin = noeud->nd->x;
      if (*xmax < noeud->nd->x)
	*xmax = noeud->nd->x;
      if (*ymin > noeud->nd->y)
	*ymin = noeud->nd->y;
      if (*ymax < noeud->nd->y)
	*ymax = noeud->nd->y;
      noeud = noeud->suiv;
    }
}

void afficheReseauSVG(Reseau *R, char *nomInstance)
{
  SVGwriter svg;
  double ratiox,ratioy;
  double xmin, xmax, ymin, ymax;
  CellNoeud *voisin;
  
  if (!R) return ;
  reseauCoordMinMax(R, &xmin, &ymin, &xmax, &ymax);
  ratiox = SIZE/(xmax-xmin);
  ratioy = SIZE/(ymax-ymin);
  SVGinit(&svg, nomInstance, SIZE, SIZE);
  SVGpointColor(&svg, "Red");
  SVGlineColor(&svg, "Black");
  CellNoeud *noeud = R->noeuds;
  while (noeud)
    {
      voisin = noeud->nd->voisins;
      while (voisin)
	{
	  SVGline(&svg,
		  (int)(ratiox*(noeud->nd->x-xmin)), (int)(ratioy*(noeud->nd->y-ymin)),
		  (int)(ratiox*(voisin->nd->x-xmin)), (int)(ratioy*(voisin->nd->y-ymin)));
	  voisin = voisin->suiv;
	}
      SVGpoint(&svg, (int)(ratiox*(noeud->nd->x-xmin)), (int)(ratioy*(noeud->nd->y-ymin)));
      noeud = noeud->suiv;
    }
  SVGfinalize(&svg);  
}
