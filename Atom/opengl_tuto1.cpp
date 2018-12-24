#include <SDL2/SDL.h>
#include <iostream>


int main(int argc, char **argv)
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return -1;
    }


    // On quitte la SDL

    SDL_Quit();

    return 0;
}
