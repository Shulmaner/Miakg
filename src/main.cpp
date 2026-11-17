#include "draw.h"

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cassert>

bool init();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;
SDL_Surface *loadedSurface = NULL;
int counter = 0;

bool init()
{
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("AOKG Lab 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      }
    }
  }
  return success;
}

void close()
{
  SDL_DestroyTexture(gTexture);
  gTexture = NULL;
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    loadedSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
      0x00FF0000,// R
      0x0000FF00,// G
      0x000000FF,// B
      0x00000000);// alpha

    gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    if (NULL == gTexture) {
      printf("Failed to load media!\n");
    } else {
      bool quit = false;
      SDL_Event e;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (SDL_QUIT == e.type) {
            quit = true;
          }
          if (SDL_MOUSEBUTTONDOWN == e.type){
            if (e.button.button == SDL_BUTTON_RIGHT){
              if(counter % 2 == 0){
                global_angle = 0.0f;
                cursor_x = e.button.x - SCREEN_WIDTH / 2;
                cursor_y = e.button.y - SCREEN_HEIGHT / 2;
                counter++;
              }
              else{
                cursor_x = 0.0f;
                cursor_y = 0.0f;
                counter++;
              }
            }
          }
          if (SDL_KEYDOWN == e.type) {
            switch (e.key.keysym.scancode) {
            //увеличение количества вершин
            case SDL_SCANCODE_PERIOD:
              vertex_counter++;
              break;
            //уменьшение количества вершин
            case SDL_SCANCODE_COMMA:
              vertex_counter--;
              if (vertex_counter < 3) vertex_counter = 3; // Минимум 3
              break;
            //уменьшение количества фигур
            case SDL_SCANCODE_N:
              figures_counter--;
              if (figures_counter < 1) figures_counter = 1;
              break;
            //увеличение количества фигур
            case SDL_SCANCODE_M:
              figures_counter++;
              break;
            //перемещение
            case SDL_SCANCODE_W:
              offset_y -= 5.0f;
              break;
            case SDL_SCANCODE_S:
              offset_y += 5.0f;
              break;
            case SDL_SCANCODE_A:
              offset_x -= 5.0f;
              break;
            case SDL_SCANCODE_D:
              offset_x += 5.0f;
              break;
            //увеличение масштаба
            case SDL_SCANCODE_EQUALS:
                scale += 0.1f;
                break;
            //уменьшение масштаба
            case SDL_SCANCODE_MINUS:
                scale -= 0.1f;
                break;
            //вращение по часовой стрелке
            case SDL_SCANCODE_Q:
                global_angle += 5.0f;
                if (global_angle >= 360.0f) global_angle -= 360.0f;
                break;
            //вращение против часовой стрелки
            case SDL_SCANCODE_E:
                global_angle -= 5.0f;
                if (global_angle <= -360.0f) global_angle += 360.0f;
                break;
            case SDL_SCANCODE_ESCAPE:
              quit = true;
              break;
            default:
              break;
            }
          }
        }
        SDL_FillRect(loadedSurface, NULL, SDL_MapRGB(loadedSurface->format, 0, 0, 0));

        SDL_RenderClear(gRenderer);
        draw(loadedSurface);

        SDL_UpdateTexture(gTexture, NULL, loadedSurface->pixels, loadedSurface->pitch);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}
