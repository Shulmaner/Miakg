#include "draw.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)
int vertex_counter = 5;
int figures_counter = 3;
float offset_x = 0.0f;
float offset_y = 0.0f;
float scale = 1.0f;
float global_angle = 0.0f;

void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  pixels[(y * surface->w) + x] = pixel;
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[(y * surface->w) + x];
}


void draw(SDL_Surface *s) {
dsfdffsf
sdfsdfsd
dsfsdf

}

    //   float global_angle_rad = glm::radians(global_angle);
    //   glm::mat4 globalRotation = glm::rotate(glm::mat4(1.0f), global_angle_rad, glm::vec3(0, 0, 1));
    //   float a = 100.0f;
    //   float t = 0;
    //   float x = 0;
    //   float y = 0;

    // for (float angle = -100; angle < 100; angle += 0.01)         //нарисовать ограничение по а (ассиптоту)
    // {
    //   t = tanf(angle * (M_PI / 180.0));
    //   x = a * t * t / (1 + t * t);
    //   y = a * t * t * t / (1 + t * t);
    //   glm:: vec4 point = glm:: vec4(x, y, 0.0f, 1.0f);
    //   glm:: vec4 rotation = point * globalRotation;
    //   int pixel_x = (int)(rotation.x + SCREEN_WIDTH / 2.5f);
    //   int pixel_y = (int)(rotation.y + SCREEN_HEIGHT / 2.0f);
    //   if (pixel_x >= 0 && pixel_x < SCREEN_WIDTH && pixel_y >= 0 && pixel_y < SCREEN_HEIGHT) {
    //     put_pixel32(s, rotation.x + SCREEN_WIDTH/2.5, rotation.y + SCREEN_HEIGHT/2, 0x0000FFFF);

    //   }

    // }
    // x = SCREEN_WIDTH/2.5 + a;
    // for (int y = SCREEN_HEIGHT-1; y > 0; y -= 1)
    // {
    //   glm:: vec4 pointq = glm:: vec4(x, y, 0.0f, 1.0f);
    //   glm:: vec4 rotationq = pointq * globalRotation;
    //       int pixel_xq = (int)(rotationq.x + SCREEN_WIDTH / 2.5f + a);
    // int pixel_yq = (int)(rotationq.y + SCREEN_HEIGHT / 2.0f);
    //   if(pixel_xq >= 0 && pixel_xq < SCREEN_WIDTH && pixel_yq >= 0 && pixel_yq < SCREEN_HEIGHT){
    //   put_pixel32(s, (int)rotationq.x, (int)rotationq.y, 0xFF0000); //от графика на а
    // }}
