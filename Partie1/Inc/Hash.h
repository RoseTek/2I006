#ifndef __HASH_H__
#define __HASH_H__	
#include<stdio.h>
#include "Reseau.h"

#define HASH_TABLE_SIZE 200

typedef struct hachage Hachage;

struct hachage {
  Noeud *nd;
  Hachage *suiv;
};

typedef struct tableHachage{
  Hachage *table[HASH_TABLE_SIZE];
} TableHachage;

Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x, double y);
Reseau *recreeReseauHachage(Chaines *C);
void creeCommodite(Reseau *R, Chaines *C);
void enleveDoublonVoisin(CellNoeud *n);

#endif	
