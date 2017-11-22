#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include "synchro.h"
#include "ensitheora.h"

bool fini;
// Mutex qui protège la hashmap de theora.
pthread_mutex_t m_theora_hm = PTHREAD_MUTEX_INITIALIZER;

/******
 * Taille de la fenêtre
 *****/
struct MoniteurTaille {
		pthread_mutex_t mutex ;
		pthread_cond_t cond ;
		int width ;
		int height ;
};
struct MoniteurTaille moniteurTaille = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, -1, -1};

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


/*****
 * Fenêtre et textures prêtes
 *****/

struct Moniteur{
		pthread_mutex_t mutex;
		pthread_cond_t cond;
};
struct Moniteur mTexture = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

void signalerFenetreEtTexturePrete() {
	assert( pthread_mutex_lock( &mTexture.mutex) == 0);
	assert(pthread_cond_signal(&mTexture.cond)==0);
	assert( pthread_mutex_unlock( &mTexture.mutex) == 0);
}

void attendreFenetreTexture() {
	assert( pthread_mutex_lock( &mTexture.mutex) == 0);
	assert(pthread_cond_wait(&mTexture.cond, &mTexture.mutex)==0);
	assert( pthread_mutex_unlock( &mTexture.mutex) == 0);
}


/*****
 * Producteur consommateur de textures
 ***/
struct MoniteurTextures{
		pthread_mutex_t mutex;
		pthread_cond_t waitFree;
		pthread_cond_t waitTexture;
		int nbTextures;
};
struct MoniteurTextures moniteurTextures = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, 0};

void debutConsommerTexture() {
	assert( pthread_mutex_lock( &moniteurTextures.mutex) == 0);
	while ( !moniteurTextures.nbTextures){
		assert(pthread_cond_wait(&moniteurTextures.waitTexture, &moniteurTextures.mutex)==0);
	}
	assert( pthread_mutex_unlock( &moniteurTextures.mutex) == 0);
}

void finConsommerTexture() {
	assert( pthread_mutex_lock( &moniteurTextures.mutex) == 0);

	if(moniteurTextures.nbTextures == NBTEX-1)
		assert(pthread_cond_signal(&moniteurTextures.waitFree)==0);
	moniteurTextures.nbTextures--;
	assert( pthread_mutex_unlock( &moniteurTextures.mutex) == 0);
}

void debutDeposerTexture() {
	assert( pthread_mutex_lock( &moniteurTextures.mutex) == 0);
	while (moniteurTextures.nbTextures == NBTEX-1) {
		assert(pthread_cond_wait(&moniteurTextures.waitFree, &moniteurTextures.mutex)==0);
	}
	assert( pthread_mutex_unlock( &moniteurTextures.mutex) == 0);
}

void finDeposerTexture() {
	assert( pthread_mutex_lock( &moniteurTextures.mutex) == 0);
	if(!moniteurTextures.nbTextures) {
		assert(pthread_cond_signal(&moniteurTextures.waitTexture)==0);
	}
	moniteurTextures.nbTextures++;
	assert( pthread_mutex_unlock( &moniteurTextures.mutex) == 0);
}


/******
 * Libération des mutex
 ***/

void synchro_quit() {
	pthread_mutex_destroy( &moniteurTaille.mutex);
	pthread_mutex_destroy( &mTexture.mutex);
	pthread_mutex_destroy( &moniteurTextures.mutex);
}
