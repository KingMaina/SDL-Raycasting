// Render geometry shapes in SDL
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

//  screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool loadMedia()
{
    bool success = true;
    // No loading special graphics needed
    return success;
}

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL unable to initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow(
            "Geometry Rendering",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Unable to create a window. SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("SDL unable to create renderer! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }
    return success;
}

void close()
{
    // Destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystem
    SDL_Quit();
}

int main(int argc, char *args[])
{
    if (!init())
    {
        printf("Failed to initialize");
    }
    else
    {
        bool quit = false;
        SDL_Event e;
        // While app is running
        while (!quit)
        {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                // User exits application
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            // Draw a filled color rectangle
            SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xCB, 0x05, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);

            // Draw a green horizontal line
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
            SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

            // Draw an outline rectangle
            SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT * 2/3};
            SDL_SetRenderDrawColor(renderer, 0x05, 0x00, 0xDC, 0xFF);
            SDL_RenderDrawRect(renderer, &outlineRect);

            // Render
            SDL_RenderPresent(renderer);
        }
    }
    close();
    return 0;
}
