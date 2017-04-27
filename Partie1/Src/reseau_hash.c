#include <math.h>
#include <stdlib.h>
#include "Hash.h"

#define M 100

Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y)
{
  CellNoeud *n;
  double A = (sqrt(5) - 1)/2;
  double key = y + (x + y)*(x + y + 1)/2;
  int hash = floor(M * (key * A - floor(key * A)));

  if (H->table[hash] != NULL)
    {
      Hachage *hash_list = H->table[hash];
      while (hash_list)
	{
	  if (hash_list->nd->x == x && hash_list->nd->y == y)
	    return hash_list->nd;
	  hash_list = hash_list->suiv;
	}
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
  Hachage *h = malloc(sizeof(Hachage));
  h->nd = nd;
  h->suiv = H->table[hash];
  H->table[hash] = h;
  return nd;
}

static void init_hash(TableHachage *H)
{
  int i;

  for (i=0; i<HASH_TABLE_SIZE; i++)
    H->table[i] = NULL;
}

Reseau *recreeReseauHachage(Chaines *C)
{
  Reseau *R = malloc(sizeof(Reseau));
  TableHachage H;
  Noeud *current;
  CellNoeud *cn;

  init_hash(&H);
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
	  current = rechercheCreeNoeudHachage(R, &H, pt->x, pt->y);
	  if (prev != NULL)
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
