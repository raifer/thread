#include <pthread.h>
#include <assert.h>
#include "synchro.h"
#include "ensitheora.h"


bool fini;

struct MoniteurTaille {
		pthread_t mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
		int width = -1;
		int height = -1;
};

struct MoniteurTaille moniteurTaille;
/* les variables pour la synchro, ici */



/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
	assert( pthread_mutex_lock( &moniteurTaille.mutex) == 0);
	moniteurTaille.width = th_ycbcr_buffer.width;
	moniteurTaille.height = th_ycbcr_buffer.height;
	assert(pthread_cond_signal(&moniteurTaille.cond)==0);
	assert( pthread_mutex_unlock( &moniteurTaille.mutex) == 0);
}

void attendreTailleFenetre(int *width, int *height) {
	assert( pthread_mutex_lock( &moniteurTaille.mutex) == 0);
	while(moniteurTaille.width == -1 && moniteurTaille.height == -1) {
			assert(pthread_cond_wait(&moniteurTaille.cond, &moniteurTaille.mutex)==0);
	}
	*width = moniteurTaille.width;
	*height = moniteurTaille.height;
	assert( pthread_mutex_unlock( &moniteurTaille.mutex) == 0);
}

void signalerFenetreEtTexturePrete() {
}

void attendreFenetreTexture() {
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
