#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "logic.h"


void *corrida(void *arg) {
    Cavalo* cavalo = (Cavalo*)arg;
    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    int distancia = DISTANCIA; 
    int progresso = 0;
    while (progresso < distancia) {
        progresso += rand() % 10 + 1;
        usleep(100000);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);

    cavalo->tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    pthread_exit(NULL);
}



void criar(Cavalo cavalos[]) {
    pthread_t threads[NUM_CAVALOS];

    srand(time(NULL));

    for (int i = 0; i < NUM_CAVALOS; i++) {
        cavalos[i].id = i + 1;
        cavalos[i].tempo = 0.0;
        if (pthread_create(&threads[i], NULL, corrida, &cavalos[i]) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_CAVALOS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void resultado(Cavalo cavalos[]) {
    Cavalo vencedor = cavalos[0];

    for (int i = 1; i < NUM_CAVALOS; i++) {
        if (cavalos[i].tempo < vencedor.tempo) {
            vencedor = cavalos[i];
        }
    }

    printf("Resultados da corrida:\n");
    for (int i = 0; i < NUM_CAVALOS; i++) {
        printf("Cavalo %d - Tempo: %.3f segundos\n", cavalos[i].id, cavalos[i].tempo);
    }
    printf("\nO vencedor é o Cavalo %d com um tempo de %.3f segundos!\n", vencedor.id, vencedor.tempo);
}

