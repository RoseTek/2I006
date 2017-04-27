#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Chaine.h"
#include "entree_sortie.h"
#include "SVGwriter.h"

#define STR_SIZE 255
#define SIZE 700

static void *my_error(char *str)
{
  fprintf(stderr, "Error : %s\n", str);
  return NULL;
}

Chaines* lectureChaine(FILE *f)
{
  Chaines *chaine = NULL;
  char tmp_str[STR_SIZE];
  CellChaine *cell = NULL, *tmp_cell = NULL;
  CellPoint *pt = NULL, *tmp_pt = NULL;
  int i, n, nb_pts;
  
  if (!f)
    return my_error("NULL file descriptor");
  if ((chaine = malloc(sizeof(Chaines))) == NULL)
    return my_error("malloc failed");
  fscanf(f, " %s %d", tmp_str, &(chaine->nbChaines));
  fscanf(f, " %s %d", tmp_str, &(chaine->gamma));
  chaine->chaines = NULL;  
  for (i=0 ; i<chaine->nbChaines ; i++)
    {
      if (!(cell = malloc(sizeof(CellChaine))))
	return my_error("malloc failed");
      cell->numero = GetEntier(f);
      nb_pts = GetEntier(f);
      cell->suiv = NULL;
      for (n=0 ; n<nb_pts ; n++)
	{
	  if (!(pt = malloc(sizeof(CellPoint))))
	    return my_error("malloc failed");
	  pt->suiv = NULL;
	  pt->x = GetReel(f);
	  pt->y = GetReel(f);
	  if (!cell->points)
	    cell->points = pt;
	  else
	    tmp_pt->suiv = pt;
	  tmp_pt = pt;
	}      
      if (!chaine->chaines)
	chaine->chaines = cell;
      else
	tmp_cell->suiv = cell;
      tmp_cell = cell;
    }
  return chaine;
}

static int points_count(CellPoint *pt)
{
  int i;

  i = 0;
  while (pt)
    {
      pt = pt->suiv;
      i++;
    }
  return i;
}

void ecrireChaineTxt(Chaines *C, FILE *f)
{
  CellChaine *chaine = NULL;
  CellPoint *point = NULL;
  
  if (!C || !f)
    {
      my_error("Null pointer");
      return ;
    }    
  fprintf(f, "NbChain: %d\nGamma: %d\n\n", C->nbChaines, C->gamma);
  chaine = C->chaines;
  while (chaine)
    {
      fprintf(f, "%d %d", chaine->numero, points_count(chaine->points));
      point = chaine->points;
      while (point)
	{
	  fprintf(f, " %.2f %.2f", point->x, point->y);
	  point = point->suiv;
	}
      fprintf(f, "\n");
      chaine = chaine->suiv;
    }
}

void chaineCoordMinMax(Chaines *C, double *xmin, double *ymin, double *xmax, double *ymax)
{
  *xmin = DBL_MAX;
  *ymin = DBL_MAX;
  *xmax = 0;
  *ymax = 0;

  CellChaine *ch = C->chaines;
  while (ch)
    {
      CellPoint *pt = ch->points;
      while (pt)
	{
	  if (*xmin > pt->x)
	    *xmin = pt->x;
	  if (*xmax < pt->x)
	    *xmax = pt->x;
	  if (*ymin > pt->y)
	    *ymin = pt->y;
	  if (*ymax < pt->y)
	    *ymax = pt->y;
	  pt = pt->suiv;
	}
      ch = ch->suiv;
    }
}

void afficheChaineSVG(Chaines *C, char* nomInstance)
{
  SVGwriter svg;
  CellChaine *chaine = NULL;
  CellPoint *point = NULL, *tmp = NULL;
  double ratiox,ratioy;
  double xmin, xmax, ymin, ymax;

  if (!C)
    {
      my_error("Null pointer");
      return ;
    }
  chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
  ratiox = SIZE/(xmax-xmin);
  ratioy = SIZE/(ymax-ymin);
  SVGinit(&svg, nomInstance, SIZE, SIZE);
  SVGpointColor(&svg, "Red");
  chaine = C->chaines;
  while (chaine)
    {
      SVGlineRandColor(&svg);
      point = chaine->points;
      tmp = NULL;
      while (point)
	{
	  if (tmp != NULL)
	    SVGline(&svg,
	  	    (int)(ratiox*(point->x-xmin)), (int)(ratioy*(point->y-ymin)),
	  	    (int)(ratiox*(tmp->x-xmin)), (int)(ratioy*(tmp->y-ymin)));
	  SVGpoint(&svg, (int)(ratiox*(point->x-xmin)), (int)(ratioy*(point->y-ymin)));
	  tmp = point;
	  point = point->suiv;
	}
      chaine = chaine->suiv;
    }
  SVGfinalize(&svg);
}

double longueurChaine(CellChaine *c)
{
  double total;
  CellPoint *pt = NULL, *tmp = NULL;
  
  total = 0;
  if (!c)
    {
      my_error("NULL pointer");
      return 0;
    }
  pt = c->points;
  while (pt)
    {
      if (tmp != NULL)
	total += sqrt(pow((pt->x - tmp->x), 2) + pow((pt->y - tmp->y), 2));
      tmp = pt;
      pt = pt->suiv;
    }
  return total;
}

double longueurTotale(Chaines *C)
{
  double total;
  CellChaine *chaine = NULL;

  total = 0;
  if (!C)
    {
      my_error("NULL pointer");
      return 0;
    }
  chaine = C->chaines;
  while (chaine)
    {
      total += longueurChaine(chaine);
      chaine = chaine->suiv;
    }
  return total;
}

int comptePointsTotal(Chaines *C)
{
  CellChaine *chaine = NULL;
  int total;

  total = 0;
  if (!C)
    my_error("NULL pointer");
  else
    chaine = C->chaines;
  while (chaine)
    {
      total += points_count(chaine->points);
      chaine = chaine->suiv;
    }
  return total;
}
