#include <limits.h>
#include <float.h>
#include "Tas.h"

static int racine(){
  return 1;
}

static int hasPere(int i){
  return i!=racine();
}

static int filsGauche(int i){
  return i*2;
}

static int filsDroit(int i){
  return i*2 + 1;
}

static int pere(int i){
  return i/2;
}

int taille(Tas *tas){
  return tas->n;
}

static int isNoeud(Tas *t, int i){
  return i < taille(t);
}

static int hasFilsGauche(Tas *t, int i){
  return isNoeud(t, filsGauche(i));
}

static int hasFilsDroit(Tas *t, int i){
  return isNoeud(t, filsDroit(i));
}

static int isFeuille(Tas *t, int i){
  return !hasFilsGauche(t,i);
}

static void echanger(Tas *t, int i, int j){
  Elem_Tas tmp = t->tab[i];
  t->tab[i] = t->tab[j];
  t->tab[j] = tmp;
}

static void monter(Tas *t, int i){
  if (!hasPere(i)) return;

  int papa = pere(i);
  if (t->tab[papa].dist > t->tab[i].dist){
    /* if (papa == 0) */
    /*   { */
    /* 	printf("\toriginal\n"); */
    /* 	printf("           %d\n", t->tab[1]); */
    /* 	printf("       %d      %d\n", t->tab[2], t->tab[3]); */
    /* 	printf("%d    %d        %d     %d\n", t->tab[4], t->tab[5],t->tab[6], t->tab[7]); */
    /*   } */
    /* printf("et on monte le pt %d car %.2f > %.2f POUR %d, papa : %d\n", t->tab[i].s ,t->tab[papa].dist, t->tab[i].dist, i, papa); */
    echanger(t,i,papa);
    monter(t,papa);
    /* if (papa == 0) */
    /*   { */
    /* 	printf("\tfinal\n"); */
    /* 	printf("           %d\n", t->tab[1]); */
    /* 	printf("       %d      %d\n", t->tab[2], t->tab[3]); */
    /* 	printf("%d    %d        %d     %d\n", t->tab[4], t->tab[5],t->tab[6], t->tab[7]); */
    /*   } */
  }
  /* else */
  /*   printf("en fait non!  %.2f < %.2f\n", t->tab[papa].dist, t->tab[i].dist); */
}

static int plusPetitFils(Tas *t, int i)
{
  if (!hasFilsDroit(t,i)){
    return filsGauche(i);
  } else {
    int fg=filsGauche(i);
    int fd=filsDroit(i);
    return (t->tab[fg].dist < t->tab[fd].dist)?fg:fd;
  }
}

static void descendre(Tas *t, int i)
{
  if (isFeuille(t,i)) return;

  int fils = plusPetitFils(t,i);
  if (t->tab[i].dist > t->tab[fils].dist){
    echanger(t, fils, i);
    descendre(t, fils);
  }
}

static Elem_Tas min(Tas *t)
{
  return t->tab[racine()];
}

//cherche sommet
//return 1 si sommet trouvé
//return 0 sinon
//si sommet trouvé, dist min mise à jour
int findElem(Tas *t, int sommet, double dist) {
  int i;

  for (i=0 ; i<t->max ; i++){
    if ((t->tab[i]).s == sommet){
      if ((t->tab[i]).dist > dist)
	(t->tab[i]).dist = dist;
      return 1;
    }
  }
  return 0;
}

void insereElem(Tas *t, int sommet, double dist) {

  if (!findElem(t, sommet, dist)){
    t->n++;
    t->tab[t->n].dist = dist;
    t->tab[t->n].s = sommet;
  }
  monter(t,t->n);
}

static void suppMin(Tas *t) {
  if (!t || t->n == 0) return;
  echanger(t,t->n, racine());
  t->n--;
  descendre(t,racine());
}

void creationTas(Tas *tas, Graphe *G)
{
  int i;
  
  tas->tab = malloc(sizeof(Elem_Tas) * (G->nbsom + 1));
  tas->n = 0;
  tas->max = G->nbsom;
  for (i=0 ; i<tas->max ; i++)
    {
      tas->tab[i].s = -1;
      tas->tab[i].dist = DBL_MAX;
    }
}

int popElem(Tas *tas)
{
  Elem_Tas mn = min(tas);
  suppMin(tas);
  return mn.s;
}

void libereTas(Tas *tas)
{
  free(tas->tab);
}
