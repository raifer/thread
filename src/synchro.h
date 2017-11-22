#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdbool.h>
#include "ensitheora.h"

extern bool fini;

// Mutex qui protège la hashmap de theora, déclaré dans
extern pthread_mutex_t m_theora_hm ;


/* Les extern des variables pour la synchro ici */


/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre(int *width, int *height);

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();
void synchro_quit();
#endif
