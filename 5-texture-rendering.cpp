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

// Window renderer
SDL_Renderer *renderer = NULL;

// Currently displayed texture
SDL_Texture *texture = NULL;

// Function prototypes
bool init();
bool loadMedia();
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
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
        // Create window instance
        window = SDL_CreateWindow(
            "SDL Textures",
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
            // Create window renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            // Initialize renderer color
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            // Initialize PNG loading
            int imageFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imageFlags) & imageFlags))
            {
                printf("SDL_image could not initialize! SDL Error: %s\n", IMG_GetError());
                success = false;
            }
        }
    }
    return success;
}

SDL_Texture* loadTexture(std::string path)
{
    // Final texture
    SDL_Texture *myTexture = NULL;

    // Load image
    SDL_Surface *loadedSurfaceImage = IMG_Load(path.c_str());

    if (loadedSurfaceImage == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Create texture from image surface pixels
        myTexture = SDL_CreateTextureFromSurface(renderer, loadedSurfaceImage);
        if (myTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        // Get rid of the old loaded surface image
        SDL_FreeSurface(loadedSurfaceImage);
    }
    return myTexture;
}

bool loadMedia()
{
    // Load success flag
    bool success = true;

    // Load texture
    texture = loadTexture("images/viewport.png");
    if (texture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    return success;
}

void close()
{
    // Free texture image
    SDL_DestroyTexture(texture);
    texture = NULL;

    //Destroy renderer
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

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
                // Clear screen
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                // Top left viewport
                SDL_Rect topLeftViewport;
                topLeftViewport.x = 0;
                topLeftViewport.y = 0;
                topLeftViewport.w = SCREEN_WIDTH / 2;
                topLeftViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &topLeftViewport);

                // Render texture to screen
                SDL_RenderCopy(renderer, texture, NULL, NULL);

                // Top right viewport
                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH / 2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH / 2;
                topRightViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &topRightViewport);

                // Render texture to screen
                SDL_RenderCopy(renderer, texture, NULL, NULL);

                // Bottom viewport
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT / 2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT / 2;
                SDL_RenderSetViewport(renderer, &bottomViewport);

                // Render texture to screen
                SDL_RenderCopy(renderer, texture, NULL, NULL);

                // Update the screen
                SDL_RenderPresent(renderer);
            }
        }
    }
    // Free resources and close SDL
    close();

    return 0;
}