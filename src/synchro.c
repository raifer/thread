#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include "synchro.h"
#include "ensitheora.h"


bool fini;

struct MoniteurTaille {
		pthread_mutex_t mutex ;
		pthread_cond_t cond ;
		int width ;
		int height ;
};

struct MoniteurTaille moniteurTaille = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, -1, -1};
/* les variables pour la synchro, ici */



/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
	assert( pthread_mutex_lock( &moniteurTaille.mutex) == 0);
	moniteurTaille.width = buffer->width;
	moniteurTaille.height = buffer->height;
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
	sleep(2);
}

void attendreFenetreTexture() {
	sleep(2);
}

void debutConsommerTexture() {
	sleep(2);
}

void finConsommerTexture() {
	sleep(2);
}


void debutDeposerTexture() {
	sleep(2);
}

void finDeposerTexture() {
	sleep(2);
}
