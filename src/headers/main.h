#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "raylib.h"



typedef struct Timer {
    int time;
    int max;
    // bool only_once;
} Timer;

typedef struct Game {
    int screen_width;
    int screen_height;
    int fps;

    bool paused;

    char directions[4];


    // void (*init)();
    // void (*update)();
    // void (*render)();
} Game;

extern struct Game game;



typedef struct DOTS {
    int valid;
    Vector2 pos;

    int* up_dot;
    int* right_dot;
    int* down_dot;
    int* left_dot;
} DOT;



#include "maze.h"
#include "pacman.h"

