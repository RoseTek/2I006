#include <stdlib.h>
#include "QuadTree.h"
#include "Hash.h"

/* Partie qui n'a pas été implémentée avec succès */

ArbreQuat *creerArbreQuat(double xc, double yc, double coteX, double coteY)
{
  ArbreQuat *ab = malloc(sizeof(ArbreQuat));

  ab->xc = xc;
  ab->yc = yc;
  ab->coteX = coteX;
  ab->coteY = coteY;
  ab->noeud = NULL;
  ab->so = NULL;
  ab->se = NULL;
  ab->no = NULL;
  ab->ne = NULL;
  return ab;
}


ArbreQuat *getPlacement(Noeud *n, ArbreQuat **ab)
{
  ArbreQuat *a = *ab;
  
  if (n->x < a->xc && n->y < a->yc)
    return (*ab)->so;
  if (n->x >= a->xc && n->y < a->yc)
    return (*ab)->se;
  if (n->x < a->xc && n->y >= a->yc)
    return (*ab)->no;
  if (n->x >= a->xc && n->y >= a->yc)
    return (*ab)->ne;
}

/* problèmes sur la partie feuille si appelée sur un noeud du graphe non vide */

ArbreQuat *insererNoeudArbre(Noeud *n, ArbreQuat *a, ArbreQuat *parent)
{
  if (a !=NULL && a->noeud == NULL)
    {
      ArbreQuat *tmp = getPlacement(n,&a);
      if (tmp)
	tmp = insererNoeudArbre(n,getPlacement(n, &a), a);
      else if (n->x < a->xc && n->y < a->yc)
	a->so = insererNoeudArbre(n,a->so,a);
      else if (n->x >= a->xc && n->y < a->yc)
	a->se = insererNoeudArbre(n,a->se,a);
      else if (n->x < a->xc && n->y >= a->yc)
	a->no = insererNoeudArbre(n,a->no,a);
      else if (n->x >= a->xc && n->y >= a->yc)
	a->ne = insererNoeudArbre(n,a->ne,a);
      return a;
    }

  if (a != NULL && a->noeud != NULL)
    {
      //printf("Insertion feuille\n");
      if ((n->x == a->noeud->x) && (n->y == a->noeud->y))
	{
	  //printf("Noeud deja placé\n");
	  return a;
	}
      Noeud *nd2 = a->noeud;

      //laisse comme c'était
      /* insererNoeudArbre(nd2, a, parent); */
      //remplace par le nouveau noeud
      /* insererNoeudArbre(n, a, parent);       */

      if (nd2->x < a->xc && nd2->y < a->yc)
      	a->so = insererNoeudArbre(nd2, a->so, a);
      if (nd2->x >= a->xc && nd2->y < a->yc)
      	a->se = insererNoeudArbre(nd2, a->se, a);
      if (nd2->x < a->xc && nd2->y >= a->yc)
      	a->no = insererNoeudArbre(nd2, a->no, a);
      if (nd2->x >= a->xc && nd2->y >= a->yc)
      	a->ne = insererNoeudArbre(nd2, a->ne, parent);
      a->noeud = NULL;
      return a;
    }
  if (a == NULL)
    {
      //printf("Insertion arbre vide\n");
      ArbreQuat *qt;
      if (n->x < parent->xc && n->y < parent->yc) //SO
	qt = creerArbreQuat( parent->xc-parent->coteX*0.75, parent->yc-parent->coteY*0.25
			     ,parent->coteX/2, parent->coteY/2);
      if (n->x >= parent->xc && n->y < parent->yc) //SE
	qt = creerArbreQuat( parent->xc-parent->coteX*0.25, parent->yc-parent->coteY*0.25
			     ,parent->coteX/2, parent->coteY/2);
      if (n->x < parent->xc && n->y >= parent->yc) //NO
	qt = creerArbreQuat(parent->xc-parent->coteX*0.75, parent->yc-parent->coteY*0.75
			    ,parent->coteX/2, parent->coteY/2);
      if (n->x >= parent->xc && n->y >= parent->yc) //NE
	qt = creerArbreQuat( parent->xc-parent->coteX*0.25, parent->yc-parent->coteY*0.75
			     ,parent->coteX/2, parent->coteY/2);
      qt->noeud = n;
      return qt;
    }
  return NULL;
}

/* code supprimé car ne fonctionnant pas du tout */
Noeud *chercherNoeudArbre(CellPoint *pt, Reseau *R, ArbreQuat **aptr, ArbreQuat *parent)
{
  return NULL;
}

static void showTree(ArbreQuat *a)
{
  /* printf("draw:"); */
  if (!a){
    //printf("\n");
    return;
  }
  if (a->noeud)
    printf("%.2f %.2f\tsizex %.2f sizey %.2f poscentre (%.2f %.2f)\n", a->noeud->x, a->noeud->y, a->coteX, a->coteY, a->xc, a->yc);
  printf("SO:");
  showTree(a->so);
  printf("SE:");
  showTree(a->se);
  printf("NO:");
  showTree(a->no);
  printf("NE:");
  showTree(a->ne);
}

/* non fonctionnel */
Reseau *recreeReseauArbre(Chaines *C)
{
  /* Reseau *R = malloc(sizeof(Reseau)); */
  /* ArbreQuat *qt; */
  /* Noeud *current =NULL; */
  /* CellNoeud *cn; */
  /* double xmin, xmax, ymin, ymax; */

  /* chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax); */
  /* qt = creerArbreQuat((xmin+xmax)/2, (ymin+ymax)/2, xmax-xmin, ymax-ymin); */
  /* printf("%.2f %.2f et %.2f %.2f\n\n", qt->xc, qt->yc, qt->coteX, qt->coteY); */
  //showTree(qt);
  /* R->nbNoeuds = 0; */
  /* R->gamma = C->gamma; */
  /* R->noeuds = NULL; */
  /* R->commodites = NULL; */
  /* CellChaine *ch = C->chaines; */
  /* while (ch) */
  /*   { */
  /*     CellPoint *pt = ch->points; */
      /* Noeud *prev = NULL; */
      /* while (pt) */
      /* 	{ */
	  /* current = chercherNoeudArbre(pt, R, &qt, qt); */
	  //printf("Insertion noeud %.2f %.2f\n", n->x, n->y);
	  //showTree(qt);
	  //printf("\n");
	  /* 	  if (prev != NULL) */
	  /* 	    { */
	  /* 	      cn = malloc(sizeof(CellNoeud)); */
	  /* 	      cn->nd = prev; */
	  /* 	      cn->suiv = current->voisins; */
	  /* 	      current->voisins = cn; */

	  /* 	      cn = malloc(sizeof(CellNoeud)); */
	  /* 	      cn->nd = current; */
	  /* 	      cn->suiv = prev->voisins; */
	  /* 	      prev->voisins = cn; */
	  /* 	    } */
	  /* prev = current; */
    /* 	  pt = pt->suiv; */
    /* 	} */
    /*   ch = ch->suiv; */
    /* } */
  /* enleveDoublonVoisin(R->noeuds); */
  /* creeCommodite(R, C); */
  /* return R; */
  return NULL;
}
