#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "enigme.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    /* font is loaded inside initEnigme when needed */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window *window = SDL_CreateWindow(
        "Sous Menu Enigme",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,1024,0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,-1,SDL_RENDERER_ACCELERATED
    );

    EnigmeMenu e;
    initEnigme(&e, renderer);

    int running = 1;
    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = 0;

            handleInputEnigme(&e, event, &running);
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        updateEnigme(&e, mouseX, mouseY);

        SDL_RenderClear(renderer);
        renderEnigme(&e, renderer);
        SDL_RenderPresent(renderer);
    }

    freeEnigme(&e);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
