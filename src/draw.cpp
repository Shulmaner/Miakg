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
float cursor_x = 0.0f;
float cursor_y = 0.0f;

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


void draw_line_rotated(SDL_Surface *s, glm::mat3 rotationMatrix, int x1, int y1, int x2, int y2, Uint32 color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        glm::vec3 point = glm::vec3((float)x1, (float)y1, 1.0f);
        glm::vec3 rotatedPoint = rotationMatrix * point;
        int px = (int)(rotatedPoint.x + offset_x) + SCREEN_WIDTH / 2;
        int py = (int)(rotatedPoint.y + offset_y) + SCREEN_HEIGHT / 2;

        if (px >= 0 && px < SCREEN_WIDTH && py >= 0 && py < SCREEN_HEIGHT) {
            put_pixel32(s, px, py, color);
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
}

void draw(SDL_Surface *s)
{

    int m = vertex_counter;
    int n = figures_counter;

    float R = 200.0f * scale;

    float global_angle_rad = glm::radians(global_angle);
    float c = cos(global_angle_rad);
    float s_val = sin(global_angle_rad);

    int cx = int(cursor_x) + SCREEN_WIDTH / 2;
    int cy = int(cursor_y) + SCREEN_HEIGHT / 2;
    if (cx >= 0 && cx < SCREEN_WIDTH && cy >= 0 && cy < SCREEN_HEIGHT) {
        put_pixel32(s, cx, cy, 0xFFFF0000);
        }
        glm::mat3 globalRotation(
        c,     -s_val, 0.0f,
        s_val, c, 0.0f,
        cursor_x * (1 - c) - cursor_y * s_val,  cursor_y * (1 - c) + cursor_x * s_val,  1.0f
    );

    std::vector<float> x_curr(m);
    std::vector<float> y_curr(m);

    for (int i = 0; i < m; i++) {
        float vertex_angle = (2.0f * M_PI * i) / m;
        x_curr[i] = R * cos(vertex_angle);
        y_curr[i] = R * sin(vertex_angle);
    }

    for (int k = 0; k < n; k++) {

        for (int i = 0; i < m; i++) {
            int next_i = (i + 1) % m;
            draw_line_rotated(s, globalRotation,
                              (int)x_curr[i], (int)y_curr[i],
                              (int)x_curr[next_i], (int)y_curr[next_i],
                              RGB32(0, 255, 0));
        }

        if (k < n - 1) {
            float angle_arg = k * (M_PI / (4.0f * n));
            float tan_val = tan(angle_arg);
            float mu = tan_val / (tan_val + 1.0f);

            std::vector<float> x_next(m);
            std::vector<float> y_next(m);

            for (int i = 0; i < m; i++) {
                int next_i = (i + 1) % m;
                x_next[i] = (1.0f - mu) * x_curr[i] + mu * x_curr[next_i];
                y_next[i] = (1.0f - mu) * y_curr[i] + mu * y_curr[next_i];
            }

            x_curr = x_next;
            y_curr = y_next;
        }
    }

}
