% Projet thred
% Gautier et Mathieu
% 20 novembre 2017
# Compilation du programme

cd build
cmake ..
make 

# Execution du programme #

make play

Télécharge une vidéo de teste, compile le programme et lance la vidéo.

# Explication des structures utilisées #

# Valgrind
## Memcheck

Le résultat de l'outil memcheck est fournis dans le fichier memcheck.txt.
On voit beaucoup de perte de mémoire.
Il semble que le programme appel les librairies de SDL pour créer des chose et on ne doit pas appeller les bonne méthode pour les ;ibérer.
Nous n'avons pas chercher plus loins pour nous concentrer sur les thread.

## Helgrind

Le résultat de l'outil helgrind est visible dans le fichier helgrind.txt.

* Pour avoir le nom des variables en sortie on a essayé l'option --read-var-info=yes;
* Mais cela génère une erreur de segmentation à cause de la pile qui explose;
* Nous avons essayé d'augmenter la taille de la stack avec : --main-stacksize=50000000, mais un autre problème de mémoire survient...
* Nous avons laissé tombé cette option.
* Sans cette option l'outil Helgrind fonctionne.

* Il y a beaucoup d'erreurs race qui corespondent à des écritures dans des zones non protégées.;
* sans l'option --read-info-var, il est très diffcile de voir si les erreur vienne de nos parties;
* Nous ne voyons pas d'erreurs de type : Misuses of the POSIX pthreads API;
* ni d'erreurs du type : Inconsistent Lock Orderings  



# Modification du CmakeList.txt 

pour la création d'un _make play_ qui télécharge automatiquement une vidéo, compile et exécute le programme.
NB : si la vidéo est déja téléchargé ou le programme déja compilé, la commande ne réitère pas ce qui est déja fait.
