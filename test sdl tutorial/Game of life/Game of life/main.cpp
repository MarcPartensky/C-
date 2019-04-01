#include "SDL2/SDL.h"
#include <iostream>

void draw(SDL_Renderer *renderer) {
    // Create a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 50;
    rectangle.w = 50;
    rectangle.h = 50;
    
    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255 );
    // Render rect
    SDL_RenderFillRect(renderer, &rectangle );
    // Render the rect to the screen
    SDL_RenderPresent(renderer);
}


int main (int argc, char** argv)
{
    // Create window
    SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
    if (window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    // Create window
    SDL_Renderer* renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 );
    
    // Clear window
    SDL_RenderClear(renderer);
    
    draw(renderer);
    
   
    
    // Check window events
    SDL_Event event;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            if (event.type == SDL_KEYDOWN){
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }
    
    // Quit window
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
