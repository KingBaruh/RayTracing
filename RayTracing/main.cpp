#include <stdio.h>
#include <SDL.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define COLOR_RAY 0xffd43b
#define COLOR_RAY_BLUR 0xbd6800
#define RAYS_NUMBER 600
#define RAY_THICKNESS 2

struct Circle {
    double x;
    double y;
    double r;
};

struct Ray {
    double x_start, y_start;
    double angle;
};

void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    int r_int = (int)circle.r;
    int cx = (int)circle.x;
    int cy = (int)circle.y;

    for (int dy = -r_int; dy <= r_int; dy++) {
        for (int dx = -r_int; dx <= r_int; dx++) {
            if (dx * dx + dy * dy <= r_int * r_int) {
                int px = cx + dx;
                int py = cy + dy;
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    Uint32* pixels = (Uint32*)surface->pixels;
                    pixels[py * (surface->pitch / sizeof(Uint32)) + px] = color;
                }
            }
        }
    }
}

void generate_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER]) {
    for (int i = 0; i < RAYS_NUMBER; i++) {
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        rays[i].x_start = circle.x;
        rays[i].y_start = circle.y;
        rays[i].angle = angle;


    }
}

void FillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 color, struct Circle object) {
    double radius_squared = object.r * object.r;

    for (int i = 0; i < RAYS_NUMBER; i++) {
        struct Ray ray = rays[i];
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;
        double step = 1.0;

        while (x_draw >= 0 && x_draw < WIDTH && y_draw >= 0 && y_draw < HEIGHT) {
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            int x_int = (int)x_draw;
            int y_int = (int)y_draw;

            if (x_int < 0 || x_int >= WIDTH || y_int < 0 || y_int >= HEIGHT) break;

            Uint32* pixels = (Uint32*)surface->pixels;
            pixels[y_int * (surface->pitch / sizeof(Uint32)) + x_int] = color;

            if ((x_draw - object.x) * (x_draw - object.x) + (y_draw - object.y) * (y_draw - object.y) < radius_squared) {
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface) {
        printf("Failed to get window surface: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    struct Circle circle = { 200, 200, 40 };
    struct Circle shadow_circle = { 550, 300, 140 };
    SDL_Rect erase_rect = { 0, 0, WIDTH, HEIGHT };

    struct Ray rays[RAYS_NUMBER];
    generate_rays(circle, rays);

    double obstacle_speed_y = 4;
    int simulation_running = 1;
    SDL_Event event;

    Uint32 start_time, frame_time;
    const int FRAME_DELAY = 16;  // Targeting ~60 FPS

    while (simulation_running) {
        start_time = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                generate_rays(circle, rays);
            }
        }

        SDL_FillRect(surface, &erase_rect, COLOR_BLACK);
        FillRays(surface, rays, COLOR_RAY, shadow_circle);
        FillCircle(surface, circle, COLOR_WHITE);
        FillCircle(surface, shadow_circle, COLOR_WHITE);

        shadow_circle.y += obstacle_speed_y;
        if (shadow_circle.y - shadow_circle.r < 0 || shadow_circle.y + shadow_circle.r > HEIGHT)
            obstacle_speed_y = -obstacle_speed_y;

        SDL_UpdateWindowSurface(window);

         // Frame rate capping
        frame_time = SDL_GetTicks() - start_time;
        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
