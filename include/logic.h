#ifndef LOGIC_H
#define LOGIC_H

#define NUM_CAVALOS 5
#define DISTANCIA 100

typedef struct {
    int id;
    double tempo;
} Cavalo;

void *corrida(void *arg);
void criar();
void resultado();

#endif