#include "inc/SDL.h"
#include <stdio.h>
#include <math.h>
#undef main

void DrawCircle(SDL_Renderer *renderer, int centreX, int centreY, int radius) {
    const int diameter = (radius * 2);
    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
void DrawAxes(SDL_Renderer *renderer, int screenWidth, int screenHeight) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, 0, screenHeight / 2, screenWidth, screenHeight / 2);
    SDL_RenderDrawLine(renderer, screenWidth / 2, 0, screenWidth / 2, screenHeight);
}

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Error:SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) < 0) {
        printf("Error: Failed to create window and renderer\nSDL Error: '%s'\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 0,0, 0, 255);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);

    DrawAxes(renderer, 640, 480);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    DrawCircle(renderer, 640 / 2, 480 / 2, 100);

    SDL_RenderDrawPoint(renderer, 640 / 2, 480 / 2);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool running = true;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}