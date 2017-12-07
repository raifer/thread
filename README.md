% Projet thred
% Gautier et Mathieu
% 20 novembre 2017

# Compilation du programme

cd build
cmake ..
make 

# Execution du programme

make play

Télécharge une vidéo de teste, compile le programme et lance la vidéo.

# Explication des méthodes de synchronisations

- Nous avons créé un Mutex globale "m_theora_hm" qui protège la hashmap de theora.
- Pour la taille de la fenêtre, nous avons créé et instancié une structure de donnée qui contient le mutex, la condition et les data.
- Pour synchroniser les deux thread lorsque la fenêtre et les textures sont prêtes nous avons utilisé tout simplement un moniteur. Une structure "Monitor" a été créer et instanciée. 
- Pour la problématique de production et de consommation de textures, nous avons créée la structure "MoniteurTextures" qui permet de gérer cela à travers un tampon.

# Valgrind
## Memcheck

Le résultat de l'outil memcheck est fournis dans le fichier memcheck.txt.
On voit beaucoup de perte de mémoire.
Il semble que le programme appel les librairies de SDL pour créer divers objets, et on ne doit pas appeler les bonne méthode pour les libérer.
Nous n'avons pas chercher plus loin pour nous concentrer sur les threads.

## Helgrind

Le résultat de l'outil helgrind est visible dans le fichier helgrind.txt.

* Pour avoir le nom des variables en sortie on a essayé l'option --read-var-info=yes;
* Mais cela génère une erreur de segmentation à cause de la pile qui explose;
* Nous avons essayé d'augmenter la taille de la stack avec : --main-stacksize=50000000, mais un autre problème de mémoire survient...
* Nous avons laissé tombé cette option.
* Sans cette option l'outil Helgrind fonctionne.

* Il y a beaucoup d'erreurs race qui correspondent à des écritures dans des zones non protégées.;
* sans l'option --read-info-var, il est très difficile de voir si les erreur vienne de nos parties;
* Nous ne voyons pas d'erreurs de type : Misuses of the POSIX pthreads API;
* ni d'erreurs du type : Inconsistent Lock Orderings  


# Modification du CmakeList.txt 

pour la création d'un _make play_ qui télécharge automatiquement une vidéo, compile et exécute le programme.
NB : si la vidéo est déja téléchargé ou le programme déja compilé, la commande ne réitère pas ce qui est déja fait.
