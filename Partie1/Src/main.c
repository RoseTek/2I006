#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Chaine.h"
#include "Reseau.h"
#include "Hash.h"
#include "QuadTree.h"

static int my_error(char *str, int err)
{
  fprintf(stderr, "Error : %s\n", str);
  return err;
}

static int init_chaine(Chaines **chaine, char *file)
{
  FILE *f = NULL;
  Chaines *ch = NULL;

  if (!(f = fopen(file,"r")))
    return my_error("fopen failed", 1);
  ch = lectureChaine(f);
  fclose(f);
  if (!ch)
    return my_error("file lecture failed", 2);
  *chaine = ch;
  return 0;
}

static int chaine_to_txt(Chaines *chaine, char *file)
{
  FILE *f = NULL;

  if (!(f = fopen(file,"w")))
    return my_error("fopen failed", 1);
  ecrireChaineTxt(chaine, f);
  fclose(f);
  return 0;
}

int test_ecriture_lecture(char *str)
{
  Chaines *chaines = NULL;


  if (init_chaine(&chaines, str))
    return 1;
  printf("init_ok\n");
  if (chaine_to_txt(chaines, "file.txt"))
    return 2;
  printf("\n\nLongueur chaine : %.2f\nNombre de points total : %d\n", longueurTotale(chaines), comptePointsTotal(chaines));
  printf("Fichier généré avec ecrireReseauTxt:\n");
  system("cat file.txt ; rm -f file.txt");
  afficheChaineSVG(chaines, "img");
  system("firefox img.html &");
  system("sleep 2 ; rm -f img.html");
  return 0;
}

int test_reconstitue_reseau(char *str)
{
  Chaines *chaines = NULL;
  Reseau *reseau = NULL;
  int input;
  FILE *f = NULL;

  if (init_chaine(&chaines, str))
    return 1;
  printf("1 liste\n2 table de hachage\n3 graphe\n\n");
  scanf("%d", &input);
  switch (input)
    {
    case 1 :
      if ((reseau = reconstitueReseauListe(chaines)) == NULL)
	return 2;
      break;
    case 2 :
      if ((reseau = recreeReseauHachage(chaines)) == NULL)
      	return 2;
      break;
    case 3 :
      if ((reseau = recreeReseauArbre(chaines)) == NULL)
      	return 2;
      break;
    }
  printf("Init ok\n");
  if (!(f = fopen("file.txt" ,"w")))
    return my_error("fopen failed", 1);
  ecrireReseauTxt(reseau, f);
  fclose(f);
  printf("Fichier généré avec ecrireReseauTxt:\n");
  system("cat file.txt ; rm -f file.txt");
  afficheReseauSVG(reseau, "img");
  system("firefox img.html &");
  system("sleep 2 ; rm -f img.html");
}

int main(int ac, char **av)
{
  int input;

  if (ac < 2)
    return my_error("usage : ./main file (prelim)", 1);
  if (ac == 3)
    return test_ecriture_lecture(av[1]);
  return test_reconstitue_reseau(av[1]);
}
