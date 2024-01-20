#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

// Define screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Define window
SDL_Window *window = NULL;

// Define window surface
SDL_Surface *screenSurface = NULL;

// Stretched image surface
SDL_Surface *stretchedSurface = NULL;

// Function prototypes
bool init();
SDL_Surface* loadSurface(std::string path);

/**
 * init - Initializes SDL, creates a window, surface and PNG image loading
 *
 * Returns: `true` if successful, `false` otherwise on error
*/
bool init()
{
    // Initialization flags
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window instance
        window = SDL_CreateWindow(
            "SDL Optimized surfaces",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("SDL could not create a window! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Initiaize PNG loading
            int imageFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imageFlags) & imageFlags))
            {
                printf("SDL_image could not initialize! SDL Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                // Get the window surface
                screenSurface = SDL_GetWindowSurface(window);
            }
        }
    }
    return success;
}

SDL_Surface* loadSurface(std::string path)
{
    // Final optimized image
    SDL_Surface *optimizedSurfaceImage = NULL;

    // Load image
    SDL_Surface *loadedSurfaceImage = IMG_Load(path.c_str());
    if (loadedSurfaceImage == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Convert surface to screen format
        optimizedSurfaceImage = SDL_ConvertSurface(loadedSurfaceImage, screenSurface->format, 0);
        if (optimizedSurfaceImage == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        // Get rid of the old loaded surface image
        SDL_FreeSurface(loadedSurfaceImage);
    }
    return optimizedSurfaceImage;
}

bool loadMedia()
{
    // Load success flag
    bool success = true;

    // Load stretching surface
    stretchedSurface = loadSurface("images/stretch.bmp");
    if (stretchedSurface == NULL)
    {
        printf("Failed to load stretching image!\n");
        success = false;
    }
    return success;
}

void close()
{
    // Free loaded image
    SDL_FreeSurface(stretchedSurface);
    stretchedSurface = NULL;

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystem
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("Unable to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Unable to load media!\n");
        }
        else
        {
            bool quit = false;

            // Event handler
            SDL_Event e;
            
            // While app is running
            while (!quit)
            {
                // Handle events from the queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests to exit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
                // Apply the stretched image
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled(stretchedSurface, NULL, screenSurface, &stretchRect);

                // Update the surface
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    // Free resources and close SDL
    close();

    return 0;
}