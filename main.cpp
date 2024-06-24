#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include <cstdio>
#include <iostream>

#define BLOCKSIZE 32
#define WMAPA 50
#define HMAPA 25
#define SCREENWIDTH BLOCKSIZE*WMAPA
#define SCREENHEIGHT BLOCKSIZE*HMAPA

using namespace std;

enum KEYS{UP, DOWN, LEFT, RIGHT , W, S, A, D};
ALLEGRO_BITMAP *bloco2 = NULL;
ALLEGRO_BITMAP *bloco1 = NULL;
int mapaAtual = 0;

int mapa0[HMAPA][WMAPA] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int mapa1[HMAPA][WMAPA] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int mapa2[HMAPA][WMAPA] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void DrawMap0(){
    for(int i=0; i<HMAPA; i++){
        for(int j=0; j<WMAPA; j++){
            if(mapa0[i][j] == 0){
                al_draw_bitmap(bloco2, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else{
                al_draw_bitmap(bloco1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
        }
    }
    }
}

void DrawMap1(){
    for(int i=0; i<HMAPA; i++){
        for(int j=0; j<WMAPA; j++){
            if(mapa1[i][j] == 0){
                al_draw_bitmap(bloco2, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else{
                al_draw_bitmap(bloco1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
        }
    }
    }
}

void DrawMap2(){
    for(int i=0; i<HMAPA; i++){
        for(int j=0; j<WMAPA; j++){
            if(mapa2[i][j] == 0){
                al_draw_bitmap(bloco2, j * BLOCKSIZE, i * BLOCKSIZE, 0);
            }
            else{
                al_draw_bitmap(bloco1, j * BLOCKSIZE, i * BLOCKSIZE, 0);
        }
      }
    }
  }

bool colisao(int px, int py){
   int x1=py/BLOCKSIZE;
   int y1=px/BLOCKSIZE;
   int x2=(py+30)/BLOCKSIZE;
   int y2=(px+30)/BLOCKSIZE;

   switch(mapaAtual){
    case 0:
        if(mapa0[x1][y1]==1 || mapa0[x1][y2]==1 ||
           mapa0[x2][y1]==1 || mapa0[x2][y2]==1)
          { return true; }
        else
          { return false; }
    case 1:
        if(mapa1[x1][y1]==1 || mapa1[x1][y2]==1 ||
           mapa1[x2][y1]==1 || mapa1[x2][y2]==1)
          { return true; }
        else
          { return false; }
    case 2:
        if(mapa2[x1][y1]==1 || mapa2[x1][y2]==1 ||
           mapa2[x2][y1]==1 || mapa2[x2][y2]==1)
          { return true; }
        else
          { return false; }
    }
}

int main(){

    ALLEGRO_DISPLAY *display;

    const float FPS = 60.0;
    bool done = false;
    bool redesenha=true;
    int posX = 32;
    int posY = 32;
    int posX2 = 27 * BLOCKSIZE;
    int posY2 = 3 * BLOCKSIZE;

    bool keys[8] = {false, false, false, false, false, false, false, false};

    al_init();
    display = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    al_set_window_position(display, 300, 200);

    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    ALLEGRO_BITMAP *player = al_load_bitmap("medico1.png");
    ALLEGRO_BITMAP *player2 = al_load_bitmap("medico2.png");
    ALLEGRO_BITMAP *pacienteAmarelo = al_load_bitmap("paciente_amarelo.png");
    ALLEGRO_BITMAP *pacienteRoxo = al_load_bitmap("paciente_roxo.png");
    ALLEGRO_BITMAP *pacienteVerde = al_load_bitmap("paciente_verde.png");
    ALLEGRO_BITMAP *pacienteVermelho = al_load_bitmap("paciente_vermelho.png");
    ALLEGRO_BITMAP *pacienteLaranja = al_load_bitmap("paciente_laranja.png");
    ALLEGRO_BITMAP *pacienteRosa = al_load_bitmap("paciente_rosa.png");
    ALLEGRO_BITMAP *pacienteCurado = al_load_bitmap("paciente_curado.png");


    ALLEGRO_BITMAP *seringaAmarela = al_load_bitmap("seringa_amarela.png");
    ALLEGRO_BITMAP *seringaRoxa = al_load_bitmap("seringa_roxa.png");
    ALLEGRO_BITMAP *seringaVerde = al_load_bitmap("seringa_verde.png");
    ALLEGRO_BITMAP *seringaVermelha = al_load_bitmap("seringa_vermelha.png");
    ALLEGRO_BITMAP *seringaLaranja = al_load_bitmap("seringa_laranja.png");
    ALLEGRO_BITMAP *seringaRosa = al_load_bitmap("seringa_rosa.png");

    //ALLEGRO_BITMAP *bloco2 = NULL;
    //ALLEGRO_BITMAP *bloco1 = NULL;

    bloco2 = al_load_bitmap("Bloco2.bmp");
    bloco1 = al_load_bitmap("Bloco1.bmp");

    al_start_timer(timer);

    int cont = 0;
    bool p1 = true, p2 = true, p3 = true, p4 = true, p5 = true, p6 = true, p7 = false, p8 = false, p9 = false, p10 = false, p11 = false, p12 = false;
    bool concluiu = false;

    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        ALLEGRO_EVENT_TYPE tipoEvento=events.type;


    if(mapaAtual == 1 || mapaAtual == 0){
        switch (tipoEvento) {
          case ALLEGRO_EVENT_TIMER: { redesenha=true; break;}
          case ALLEGRO_EVENT_DISPLAY_CLOSE: { done = true; break;}

          case ALLEGRO_EVENT_KEY_DOWN: {
            int tecla = events.keyboard.keycode;
            switch(tecla){
                case ALLEGRO_KEY_UP: {keys[UP] = true; break;}
                case ALLEGRO_KEY_DOWN: {keys[DOWN] = true; break;}
                case ALLEGRO_KEY_LEFT: {keys[LEFT] = true; break;}
                case ALLEGRO_KEY_RIGHT: {keys[RIGHT] = true; break;}
            }
            break;
          }
          case ALLEGRO_EVENT_KEY_UP: {
            int tecla = events.keyboard.keycode;
            switch(tecla){
                case ALLEGRO_KEY_UP: {keys[UP] = false; break;}
                case ALLEGRO_KEY_DOWN: {keys[DOWN] = false;break; }
                case ALLEGRO_KEY_LEFT: {keys[LEFT] = false; break;}
                case ALLEGRO_KEY_RIGHT: {keys[RIGHT] = false; break;}
            }
            break;
          }
        }
        if (!colisao(posX, posY - 2)){
           posY -= keys[UP] * 2;
        }
        if (!colisao(posX, posY + 2)){
           posY += keys[DOWN] * 2;
        }
        if (!colisao(posX - 2, posY)){
           posX -= keys[LEFT] * 2;
        }
        if (!colisao(posX + 2, posY)){
           posX += keys[RIGHT] * 2;
        }
    }else{

        switch (tipoEvento) {
    case ALLEGRO_EVENT_TIMER: {
        redesenha = true;
        break;
    }
    case ALLEGRO_EVENT_DISPLAY_CLOSE: {
        done = true;
        break;
    }
    case ALLEGRO_EVENT_KEY_DOWN: {
        int tecla = events.keyboard.keycode;
        switch (tecla) {
            case ALLEGRO_KEY_W: {
                keys[W] = true;
                break;
            }
            case ALLEGRO_KEY_S: {
                keys[S] = true;
                break;
            }
            case ALLEGRO_KEY_A: {
                keys[A] = true;
                break;
            }
            case ALLEGRO_KEY_D: {
                keys[D] = true;
                break;
            }
        }
        break;
    }
    case ALLEGRO_EVENT_KEY_UP: {
        int tecla = events.keyboard.keycode;
        switch (tecla) {
            case ALLEGRO_KEY_W: {
                keys[W] = false;
                break;
            }
            case ALLEGRO_KEY_S: {
                keys[S] = false;
                break;
            }
            case ALLEGRO_KEY_A: {
                keys[A] = false;
                break;
            }
            case ALLEGRO_KEY_D: {
                keys[D] = false;
                break;
            }
        }
        break;
    }
}


if (!colisao(posX2, posY2 - 2)) {
    posY2 -= keys[W] * 2;
}
if (!colisao(posX2, posY2 + 2)) {
    posY2 += keys[S] * 2;
}
if (!colisao(posX2 - 2, posY2)) {
    posX2 -= keys[A] * 2;
}
if (!colisao(posX2 + 2, posY2)) {
    posX2 += keys[D] * 2;
}
    }


        if (redesenha && cont < 1) {
            DrawMap0();

            al_draw_bitmap(player, posX, posY, 0);

            if (posX >= (4 * BLOCKSIZE) && posX <= (5 * BLOCKSIZE) && posY >= (18 * BLOCKSIZE) && posY <= (19 * BLOCKSIZE) && p1) {
                p1 = false;
                cont++;
            }
            if (p1) {
                al_draw_bitmap(pacienteAmarelo, (4 * BLOCKSIZE), (18 * BLOCKSIZE), 0);
            }

            if (posX >= (7 * BLOCKSIZE) && posX <= (8 * BLOCKSIZE) && posY >= (6 * BLOCKSIZE) && posY <= (7 * BLOCKSIZE) && p2) {
                p2 = false;
                cont++;
            }
            if (p2) {
                al_draw_bitmap(pacienteRoxo, (7 * BLOCKSIZE), (6 * BLOCKSIZE), 0);
            }

            if (posX >= (18 * BLOCKSIZE) && posX <= (19 * BLOCKSIZE) && posY >= (18 * BLOCKSIZE) && posY <= (19 * BLOCKSIZE) && p3) {
                p3 = false;
                cont++;
            }
            if (p3) {
                al_draw_bitmap(pacienteVerde, (18 * BLOCKSIZE), (18 * BLOCKSIZE), 0);
            }

            if (posX >= (29 * BLOCKSIZE) && posX <= (30 * BLOCKSIZE) && posY >= (6 * BLOCKSIZE) && posY <= (7 * BLOCKSIZE) && p4) {
                p4 = false;
                cont++;
            }
            if (p4) {
                al_draw_bitmap(pacienteVermelho, (29 * BLOCKSIZE), (6 * BLOCKSIZE), 0);
            }

            if (posX >= (43 * BLOCKSIZE) && posX <= (44 * BLOCKSIZE) && posY >= (9 * BLOCKSIZE) && posY <= (10 * BLOCKSIZE) && p5) {
                p5 = false;
                cont++;
            }
            if (p5) {
                al_draw_bitmap(pacienteLaranja, (43 * BLOCKSIZE), (9 * BLOCKSIZE), 0);
            }

            if (posX >= (41 * BLOCKSIZE) && posX <= (42 * BLOCKSIZE) && posY >= (19 * BLOCKSIZE) && posY <= (20 * BLOCKSIZE) && p6) {
                p6 = false;
                cont++;
            }
            if (p6) {
                al_draw_bitmap(pacienteRosa, (41 * BLOCKSIZE), (19 * BLOCKSIZE), 0);
            }


            colisao(posX, posY);

            al_flip_display();
            redesenha = false;
        }   else if (redesenha && cont == 1) {

            if(concluiu == false){
            mapaAtual = 1;
          DrawMap1();
          colisao(posX, posY);

          al_draw_bitmap(player, posX, posY, 0);

          al_flip_display();
          redesenha=false;

          if (posX >= 48 * BLOCKSIZE) {
          mapaAtual = 2;
          DrawMap2();
          posX2 = BLOCKSIZE * 24;
          posY2 = BLOCKSIZE * 3;

          colisao(posX, posY);

          al_flip_display();
          redesenha=false;
          concluiu = true;
          p1 = true, p2 = true, p3 = true, p4 = true, p5 = true, p6 = true, p7 = false, p8 = false, p9 = false, p10 = false, p11 = false, p12 = false;
                    }
                }else{
                    bool amarelo = false, roxo = false, verde = false, vermelho = false, laranja = false, rosa = false;
                    int contCurado = 0;
                        DrawMap2();

                      colisao(posX2, posY2);

                      al_draw_bitmap(player2, posX2, posY2, 0);

                      if (posX2 >= (4 * BLOCKSIZE) && posX2 <= (5 * BLOCKSIZE) && posY2 >= (21 * BLOCKSIZE) && posY2 <= (22 * BLOCKSIZE) && p1) {
                            p1 = false;
                        }
                        if (p1 && amarelo == false) {
                            al_draw_bitmap(pacienteAmarelo, (5 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                        } else if (!p1 && p7) {
                            al_draw_bitmap(pacienteCurado, (5 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                            amarelo = true;
                            contCurado++;
                        } else if (amarelo) {
                            al_draw_bitmap(pacienteCurado, (5 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                        } else {
                            al_draw_bitmap(pacienteAmarelo, (5 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                        }



                        if (posX2 >= (5 * BLOCKSIZE) && posX2 <= (6 * BLOCKSIZE) && posY2 >= (14 * BLOCKSIZE) && posY2 <= (15 * BLOCKSIZE) && p2) {
                            p2 = false;
                        }
                        if (p2 && roxo == false) {
                            al_draw_bitmap(pacienteRoxo, (5 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                        } else if (!p2 && p8) {
                            al_draw_bitmap(pacienteCurado, (5 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                            roxo = true;
                            contCurado++;
                        } else if (roxo) {
                            al_draw_bitmap(pacienteCurado, (5 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                        } else {
                            al_draw_bitmap(pacienteRoxo, (5 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                        }


                        if (posX2 >= (21 * BLOCKSIZE) && posX2 <= (22 * BLOCKSIZE) && posY2 >= (22 * BLOCKSIZE) && posY2 <= (23 * BLOCKSIZE) && p3) {
                            p3 = false;
                        }
                        if (p3 && verde == false) {
                            al_draw_bitmap(pacienteVerde, (21 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                        } else if (!p3 && p9) {
                            al_draw_bitmap(pacienteCurado, (21 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                            verde = true;
                            contCurado++;
                        } else if (verde) {
                            al_draw_bitmap(pacienteCurado, (21 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                        } else {
                            al_draw_bitmap(pacienteVerde, (21 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                        }

                        if (posX2 >= (31 * BLOCKSIZE) && posX2 <= (32 * BLOCKSIZE) && posY2 >= (22 * BLOCKSIZE) && posY2 <= (23 * BLOCKSIZE) && p4) {
                            p4 = false;
                        }
                        if (p4 && vermelho == false) {
                            al_draw_bitmap(pacienteVermelho, (31 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                        } else if (!p4 && p10) {
                            al_draw_bitmap(pacienteCurado, (31 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                            vermelho = true;
                            contCurado++;
                        } else if (vermelho) {
                            al_draw_bitmap(pacienteCurado, (31 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                        } else {
                            al_draw_bitmap(pacienteVermelho, (31 * BLOCKSIZE), (22 * BLOCKSIZE), 0);
                        }

                        if (posX2 >= (45 * BLOCKSIZE) && posX2 <= (46 * BLOCKSIZE) && posY2 >= (14 * BLOCKSIZE) && posY2 <= (15 * BLOCKSIZE) && p5) {
                            p5 = false;
                        }
                        if (p5 && laranja == false) {
                            al_draw_bitmap(pacienteLaranja, (45 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                        } else if (!p5 && p11) {
                            al_draw_bitmap(pacienteCurado, (45 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                            laranja = true;
                            contCurado++;
                        } else if (laranja) {
                            al_draw_bitmap(pacienteCurado, (45 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                        } else {
                            al_draw_bitmap(pacienteLaranja, (45 * BLOCKSIZE), (14 * BLOCKSIZE), 0);
                        }

                        if (posX2 >= (45 * BLOCKSIZE) && posX2 <= (46 * BLOCKSIZE) && posY2 >= (21 * BLOCKSIZE) && posY <= (22 * BLOCKSIZE) && p6) {
                            p6 = false;
                        }
                        if (p6 && rosa == false) {
                            al_draw_bitmap(pacienteRosa, (45 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                        } else if (!p6 && p12) {
                            al_draw_bitmap(pacienteCurado, (45 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                            rosa = true;
                            contCurado++;
                        } else if (rosa) {
                            al_draw_bitmap(pacienteCurado, (45 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                        } else {
                            al_draw_bitmap(pacienteRosa, (45 * BLOCKSIZE), (21 * BLOCKSIZE), 0);
                        }




            //seringas


            if (posX2 >= (20 * BLOCKSIZE) && posX2 <= (21 * BLOCKSIZE) && posY2 >= (5 * BLOCKSIZE) && posY2 <= (6 * BLOCKSIZE) && !p7) {
                p7 = true;
                p1 = true;
            }
            if (!p7) {
                al_draw_bitmap(seringaAmarela, (20 * BLOCKSIZE), (5 * BLOCKSIZE), 0);
            }

            if (posX2 >= (20 * BLOCKSIZE) && posX2 <= (21 * BLOCKSIZE) && posY2 >= (8 * BLOCKSIZE) && posY2 <= (9 * BLOCKSIZE) && !p8) {
                p8 = true;
                p2 = true;
            }
            if (!p8) {
                al_draw_bitmap(seringaRoxa, (20 * BLOCKSIZE), (8 * BLOCKSIZE), 0);
            }

            if (posX2 >= (23 * BLOCKSIZE) && posX2 <= (24 * BLOCKSIZE) && posY2 >= (8 * BLOCKSIZE) && posY2 <= (9 * BLOCKSIZE) && !p9) {
                p9 = true;
                p3 = true;
            }
            if (!p9) {
                al_draw_bitmap(seringaVerde, (23 * BLOCKSIZE), (8 * BLOCKSIZE), 0);
            }

            if (posX2 >= (26 * BLOCKSIZE) && posX2 <= (27 * BLOCKSIZE) && posY2 >= (8 * BLOCKSIZE) && posY2 <= (9 * BLOCKSIZE) && !p10) {
                p10 = true;
                p4 = true;
            }
            if (!p10) {
                al_draw_bitmap(seringaVermelha, (26 * BLOCKSIZE), (8 * BLOCKSIZE), 0);
            }

            if (posX2 >= (29 * BLOCKSIZE) && posX2 <= (30 * BLOCKSIZE) && posY2 >= (5 * BLOCKSIZE) && posY2 <= (6 * BLOCKSIZE) && !p11) {
                p11 = true;
                p5 = true;
            }
            if (!p11) {
                al_draw_bitmap(seringaLaranja, (29 * BLOCKSIZE), (5 * BLOCKSIZE), 0);
            }

            if (posX2 >= (29 * BLOCKSIZE) && posX2 <= (30 * BLOCKSIZE) && posY2 >= (8 * BLOCKSIZE) && posY2 <= (9 * BLOCKSIZE) && !p12) {
                p12 = true;
                p6 = true;
            }
            if (!p12) {
                al_draw_bitmap(seringaRosa, (29 * BLOCKSIZE), (8 * BLOCKSIZE), 0);
            }


                al_flip_display();
                redesenha=false;

                if(contCurado == 6){
                    cout << "aewwwww caraleouuuuu" << endl;
                }
            }
        }
    }


    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;
}


