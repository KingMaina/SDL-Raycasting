#include <SDL2/SDL.h>
#include <stdio.h>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Startup SDL and create a window
bool init();

// Loads media
bool loadMedia();

// Deallocates media memory and shuts down SDL
void close();

// Window to render to
SDL_Window *window = NULL;

// Surface contained by the window
SDL_Surface *screenSurface = NULL;

// Image to show and load on screen
SDL_Surface *helloWorld = NULL;

bool init()
{
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL couldn't initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if ( window == NULL )
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get the window surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    helloWorld = SDL_LoadBMP("images/hello_world.bmp");
    if (helloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(helloWorld);
    helloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystem
    SDL_Quit();
}

int main(int argc, char* args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Apply the image
            SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
            // Update the surface
            SDL_UpdateWindowSurface(window);
            // Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false){ while( SDL_PollEvent( &e)){ if (e.type == SDL_QUIT) quit = true;}}
        }
    }
    // Free resources and close SDL
    close();
    return 0;
}