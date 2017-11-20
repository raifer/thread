#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <SDL2/SDL.h>

#include "stream_common.h"
#include "oggstream.h"


int main(int argc, char *argv[]) {
    int res;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // Initialisation de la SDL
    printf("Init SDL2...\n");
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    if( res == -1) {
    	fprintf(stderr, "SDL Init error : %s\n", SDL_GetError());
    	exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);

    // start Theora stream
pthread_t t_theoraStreamReader;
if(pthread_create(&t_theoraStreamReader, NULL, theoraStreamReader, argv[1]) == -1) {
	perror("pthread_create");
	return EXIT_FAILURE;
}

// Start Vorbis stream reader
pthread_t t_vorbisStreamReader;
if(pthread_create(&t_vorbisStreamReader, NULL, vorbisStreamReader, argv[1]) == -1) {
	perror("pthread_create");
	return EXIT_FAILURE;
}

// wait audio thread
printf("Wait audio thread\n");
pthread_join(t_vorbisStreamReader, NULL);

    // 1 seconde de garde pour le son,
printf("Sleep 1 pour le son\n");
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués
    extern pthread_t t_draw;
    pthread_cancel(t_theoraStreamReader);
    pthread_cancel(t_draw);

    // attendre les 2 threads videos
    printf("Wait thread vidéo\n");
    //fflush(stdout);
    pthread_join (t_draw, NULL);
    pthread_join (t_theoraStreamReader, NULL);


    exit(EXIT_SUCCESS);
}
