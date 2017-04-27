#include <stdlib.h>
#include "Reseau.h"

Noeud *rechercheCreeNoeudListe(Reseau *R, double x, double y)
{
  CellNoeud *n;
  
  if (!R)
    return NULL;

  n = R->noeuds;
  while (n)
    {
      if (n->nd && (n->nd->x == x) && (n->nd->y == y))
	return n->nd;
      n = n->suiv;
    }
  Noeud *nd = malloc(sizeof(Noeud));
  if (!nd) return NULL;
  nd->num = R->nbNoeuds+1;
  R->nbNoeuds++;
  nd->x = x;
  nd->y = y;
  nd->voisins = NULL;
  n = malloc(sizeof(CellNoeud));
  n->nd = nd;
  n->suiv = R->noeuds;
  R->noeuds = n;
  return nd;
}

void creeCommodite(Reseau *reseau, Chaines *chaines)
{
  CellChaine *chaine;
  CellPoint *fst = NULL, *last = NULL;
  Noeud *ndA, *ndB;
  CellCommodite *com;
  
  if (!chaines)
    return ;
  chaine = chaines->chaines;
  while (chaine)
    {
      fst = chaine->points;
      last = chaine->points;
      while (last->suiv != NULL)
	  last = last->suiv;
      ndB = rechercheCreeNoeudListe(reseau, fst->x, fst->y);
      ndA = rechercheCreeNoeudListe(reseau, last->x, last->y);
      if ((com = malloc(sizeof(CellCommodite))) == NULL)
	return ;
      com->extrA = ndA;
      com->extrB = ndB;
      com->suiv = reseau->commodites;
      reseau->commodites = com;
      chaine = chaine->suiv;
    }
}

void enleveDoublonVoisin(CellNoeud *noeuds)
{
  while (noeuds)
    {
      Noeud *nd = noeuds->nd;
      CellNoeud *voisins = noeuds->nd->voisins;
      while (voisins)
	{
	  CellNoeud *v = voisins->suiv;
	  CellNoeud *prev = voisins;
	  while (v)
	    {
	      if (v->nd == voisins->nd)
		{
		  prev->suiv = v->suiv;
		  free(v);
		  v = prev->suiv;
		}
	      else
		{
		  prev = v;
		  v = v->suiv;
		}
	    }
	  voisins = voisins->suiv;
	}
      noeuds = noeuds->suiv;
    }
}

Reseau *reconstitueReseauListe(Chaines *C)
{
  Reseau *R = malloc(sizeof(Reseau));
  Noeud *current;
  CellNoeud *cn;
  
  R->nbNoeuds = 0;
  R->gamma = C->gamma;
  R->noeuds = NULL;
  R->commodites = NULL;
  CellChaine *ch = C->chaines;
  while (ch)
    {
      CellPoint *pt = ch->points;
      Noeud *prev = NULL;
      while (pt)
	{
	  current = rechercheCreeNoeudListe(R, pt->x, pt->y);
	  if (prev != NULL) // ajout de voisins
	    {
	          cn = malloc(sizeof(CellNoeud));
	          cn->nd = prev;
	          cn->suiv = current->voisins;
	          current->voisins = cn;
		  
	          cn = malloc(sizeof(CellNoeud));
	          cn->nd = current;
	          cn->suiv = prev->voisins;
	          prev->voisins = cn;
	    }
	  prev = current;
	  pt = pt->suiv;
	}
      ch = ch->suiv;
    }
  enleveDoublonVoisin(R->noeuds);
  creeCommodite(R, C);
  return R;
}
