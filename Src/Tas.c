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
    echanger(t,i,papa);
    monter(t,papa);
  }
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
//return un int positif si sommet trouvé
//return 0 sinon
//si sommet trouvé, dist min mise à jour
int findElem(Tas *t, int sommet, double dist, int current) {
  if (current >= t->n)
    return 0;
  if (t->tab[current].s == sommet){
    if (t->tab[current].dist > dist)
      t->tab[current].dist = dist;
    return 1;
  }
  return findElem(t, sommet, dist, filsGauche(current)) + findElem(t, sommet, dist, filsDroit(current));
}

void insereElem(Tas *t, int sommet, double dist) {

  if (!findElem(t, sommet, dist, 1)){
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

double getNextDist(Tas *tas)
{
  Elem_Tas mn = min(tas);

  return mn.dist;
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
