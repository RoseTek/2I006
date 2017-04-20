#! /bin/bash

make re
make clean

# parcours largeur, genere ncha pour tous les fichiers
# for file in `ls Ressource` ; do
#     ./MainGraphe $(basename $file .res) 1
# done

# parcours largeur + evaluation sur les 3 fichiers
# ./MainGraphe "00783_rat" 2
# ./MainGraphe "05934_rl" 2
# ./MainGraphe "07397_pla" 2

# echo ""

# court chemin avec algo de Djikstra + evaluation sur les 3 fichiers
# ./MainGraphe "00783_rat" 3
# ./MainGraphe "05934_rl" 3
# ./MainGraphe "07397_pla" 3


# ./MainGraphe "00014_burma" 3
# echo ""
# ./MainGraphe "00014_burma" 2
