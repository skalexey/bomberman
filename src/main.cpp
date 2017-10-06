/*
 *  rectangles.c
 *  written by Holmes Futrell
 *  use however you want
 */

#include <chrono>
#include <time.h>
#include "SDL.h"
#include "Game.h"

Game* game;

float block_size = 20.0f;

void
render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 94, 94, 94, 255);
    SDL_RenderClear(renderer);
    game->render(renderer);
    SDL_RenderPresent(renderer);
}

void handleMouseButtonDown(SDL_Event * event)
{
    game->onMouseButtonDown();
}

/* called from main event loop */
void handleMouseButtonUp(SDL_Event * event)
{
    game->onMouseButtonUp();
}

void handleMouseMove(SDL_Event* event)
{
    game->onMouseMove();
}


int SDL_main(int argc, char *argv[])
{
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    int done;
    SDL_Event event;
    
    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL\n");
        return 1;
    }
    
    /* seed random number generator */
    srand(time(NULL));
    
    /* create window and renderer */
    window =
    SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                     SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        printf("Could not initialize Window\n");
        return 1;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Could not create renderer\n");
        return 1;
    }
    
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    block_size = mode.h / 16;
    
    SDL_Log("block_size: %f", block_size);
    
    game = new Game();
    
    /* Enter render loop, waiting for user to quit */
    done = 0;
    std::chrono::time_point<std::chrono::steady_clock> before = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> after = std::chrono::steady_clock::now();
    while (!done) {
        float dt = std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() / 1000.0f;
        before = std::chrono::steady_clock::now();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    handleMouseButtonDown(&event);
                    break;
                case SDL_MOUSEBUTTONUP:
                    handleMouseButtonUp(&event);
                    break;
                case SDL_MOUSEMOTION:
                    handleMouseMove(&event);
                    break;
                case SDL_QUIT:
                    done = 1;
                    break;
            }
        }
        game->update(dt);
        render(renderer);
        SDL_Delay(1);
        after = std::chrono::steady_clock::now();
    }
    
    delete game;
    /* shutdown SDL */
    SDL_Quit();
    
    return 0;
}
