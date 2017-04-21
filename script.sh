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
# valgrind ./MainGraphe "00783_rat" 3
# valgrind ./MainGraphe "05934_rl" 3
# valgrind ./MainGraphe "07397_pla" 3



# echo "parcours largeur"
# time ./MainGraphe "00783_rat" 2
# echo "Djikstra"
# time ./MainGraphe "00783_rat" 3

# echo "*-------------------------------------------------------------*"
# echo "parcours largeur"
# time ./MainGraphe "05934_rl" 2
# echo "Djikstra"
# time ./MainGraphe "05934_rl" 3

# echo "*-------------------------------------------------------------*"
# echo "parcours largeur"
# time ./MainGraphe "07397_pla" 2
# echo "Djikstra"
# time ./MainGraphe "07397_pla" 3




# ------------------- TEST TEMPS ------------------ #
# echo "               DJIKSTRA
# real    0m0.037s
# user    0m0.032s
# sys     0m0.000s
# -----------------"
# time ./MainGraphe "00783_rat" 4

# echo "______________________________________________________
#                DJIKSTRA
# real    0m13.062s
# user    0m13.036s
# sys     0m0.008s
# -----------------"
# time ./MainGraphe "05934_rl" 4

# echo "______________________________________________________
#                DJIKSTRA
# real    0m23.793s
# user    0m23.744s
# sys     0m0.032s
# -----------------"
# time ./MainGraphe "07397_pla" 4


# ------------------ TEST EVALUATION -------------------- #
echo "       parcours largeur
Total size : 111541.67  Gamma max : 50
evaluation 00783_rat : 52.73/100
        Djikstra
Total size : 92070.96   Gamma max : 68
evaluation 00783_rat : 23.98/100
-----------------"
./MainGraphe "00783_rat" 4

echo "______________________________________________________
        parcours largeur
Total size : 33467313.90        Gamma max : 300
evaluation 05934_rl : 47.02/100
        Djikstra
Total size : 20907102.22        Gamma max : 223
evaluation 05934_rl : 79.76/100
-----------------"
./MainGraphe "05934_rl" 4

echo "______________________________________________________
        parcours largeur
Total size : 2602531252.73      Gamma max : 1318
evaluation 07397_pla : 24.44/100
        Djikstra
Total size : 1852477205.87      Gamma max : 1312
evaluation 07397_pla : 34.63/100
-----------------"
./MainGraphe "07397_pla" 4
