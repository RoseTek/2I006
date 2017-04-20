#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graphe.h"
#include "Struct_Liste.h"
#include "ShortPath.h"

int main(int argc,char**argv){

  char filename[205],filenameres[205];
  int chmeth;

  if(argc!=3){
    printf("usage: %s <file> <numeromethod>\n",argv[0]);
    printf("0 : generation image html\n");
    printf("1 : parcours en largeur\n");
    printf("2 : parcours en largeur avec evaluation de la solution\n");
    printf("3 : algorithme de Djikstra avec evaluation de la solution\n");
    return 1;
  }

  chmeth=atoi(argv[2]);

  strcpy(filename,"Output/\0");
  strcpy(filenameres,"Ressource/\0");
  
  strcat(filename,argv[1]);
  strcat(filenameres,argv[1]);
  strcat(filenameres,".res");

  FILE *f=fopen(filenameres,"r");
  /* FILE *f=fopen("Ressource/00014_burma.res","r"); */

  if (f==NULL){
    printf("Probleme lecture du fichier\n");
    return 1;
  }

  Graphe G;
  lecture_graphe(&G,f);
  fclose(f);

  switch (chmeth)
    {
    case 0:
      affichageGrapheSVG(&G,filename);
      break;
    case 1:
      genereCheminMinCommodite(&G, argv[1], 0);
      break;
    case 2:
      genereCheminMinCommodite(&G, argv[1], 1);
      break;
    case 3:
      djikstraMinCommodite(&G, argv[1]);
      /* djikstraMinCommodite(&G, "00014_burma"); */
      break;
    default:
      printf("No method for this number\n");
    }
  
  return 0;
}
