#pragma once
#include <SDL.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
extern int vertex_counter;
extern int figures_counter;
extern float offset_x;
extern float offset_y;
extern float scale;
extern float global_angle;
extern float cursor_x;
extern float cursor_y;

void draw(SDL_Surface *s);
