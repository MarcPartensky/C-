#ifndef game_h
#define game_h

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>

class Game {
public:
    Game();
    ~Game();
    void loop();
    void update() {}
    void input()  {}
    void render;
private:
    SDL_Renderer* ren;
    SDL_Window* win;
    bool running;
    int count;
    int frameCount, timerFPS, lastFrame;
};

#endif /* game_h */
