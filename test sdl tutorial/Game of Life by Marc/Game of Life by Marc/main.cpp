#include "SDL2/SDL.h"
#include <iostream>
#include <vector>

using namespace std;

void log(string message) {
    cout << "[Game of life] " << message << endl;
}

void drawRect(SDL_Renderer* renderer, int x, int y, int width, int height, bool colored) {
    // Create a rect
    SDL_Rect rectangle;
    rectangle.x = x*width;
    rectangle.y = y*height;
    rectangle.w = width;
    rectangle.h = height;
    
    // Set render color to green if colored ( rect will be rendered in this color )
    if (colored) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255 );
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
    }
    
    // Render rect
    SDL_RenderFillRect(renderer, &rectangle );
}

void draw(SDL_Renderer* renderer, vector<vector<int>> board, int width,int height, int scale) {
    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255 );
    
    // Clear window
    SDL_RenderClear(renderer);
    
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            if (board[y][x]==1) {
                drawRect(renderer,x,y,scale, scale, true);
            } else {
                drawRect(renderer,x,y,scale, scale, false);
            }
        }
    }
    
    // Render the rect to the screen
    SDL_RenderPresent(renderer);
}

void poorDraw(vector<vector<int>> board, int width,int height) {
    for (int y=0; y<height; y++) {
        string text="";
        for (int x=0; x<width; x++) {
            if (board[y][x]==1) {
                text=text+"#";
            } else {
                text=text+"-";
            }
        }
        cout << text << endl;
    }
    cout << endl;
}

int neighborsCounter(int x, int y, vector<vector<int>> board, int width, int height) {
    int count=0;
    if (x+1<width)                  {if (board[y][x+1]==1)      {count++;}}
    if (x+1<width & y+1<height)     {if (board[y+1][x+1]==1)    {count++;}}
    if (y+1<height)                 {if (board[y+1][x]==1)      {count++;}}
    if (x-1>0 & y+1<height)         {if (board[y+1][x-1]==1)    {count++;}}
    if (x-1>0)                      {if (board[y][x-1]==1)      {count++;}}
    if (x-1>0 & y-1>0)              {if (board[y-1][x-1]==1)    {count++;}}
    if (y-1>0)                      {if (board[y-1][x]==1)      {count++;}}
    if (x+1<width & y-1>0)          {if (board[y-1][x+1]==1)    {count++;}}
    return count;
}


bool checkRule(int cell, int count) {
    bool alive;
    if (cell==0) {alive=false;} else {alive=true;}
    if (!alive && count==3)             {alive=true;}
    if (alive && count>=2 && count<=3)     {alive=true;} else {alive=false;}
    return alive;
}

vector<vector<int>> generate(vector<vector<int>> current_board, int width, int height) {
    vector<vector<int>> next_board(height, vector<int>(width));
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            int cell = current_board[y][x];
            int count = neighborsCounter(x, y, current_board, width, height);
            if (checkRule(cell,count)) {
                next_board[y][x]=1;
            } else {
                next_board[y][x]=0;
            }
        }
    }
    return next_board;
}

vector<vector<int>> place(int X, int Y, vector<vector<int>> board, int scale) {
    int x=X/scale;
    int y=Y/scale;
    int cell=board[y][x];
    if (cell==1) {
        board[y][x]=0;
    } else {
        board[y][x]=1;
    }
    return board;
}







//--------------------------//
// Main function starts here//
//--------------------------//

int main () {
    log("Program starting");
    
    log("Initializing variables");
    const int width = 100;
    const int height = 100;
    const int scale = 8;
    bool generating=false;
    
    log("Initializing board");
    vector<vector<int>> board(height, vector<int>(width));
    
    log("Creating window");
    SDL_Window *window = SDL_CreateWindow(
                                          "Game of Life",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width * scale,
                                          height * scale,
                                          SDL_WINDOW_RESIZABLE
                                          );
    log("Creating renderer");
    // Create renderer
    SDL_Renderer* renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    log("Creating event");
    SDL_Event event;
    
    draw(renderer, board, width, height, scale);
    

    log("Starting game loop");
    bool open=true;
    int state=0;
    while (open) {
        SDL_WaitEvent(&event);
        if (event.type==SDL_MOUSEBUTTONDOWN) {board=place(event.motion.x, event.motion.y, board, scale);}
        if (event.type==SDL_QUIT) {open=false;}
        if (event.type==SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_q) {open = false;}
            if (event.key.keysym.sym == SDLK_SPACE) {if (generating) {generating=false;} else {generating=true;}}
        }
        if (generating) {
            board=generate(board,height,width);
            state++;
            cout<<"[State]: " <<state<<endl;
            generating=false;
        }
        draw(renderer, board, width, height, scale);
    }
    
    log("Destroying SDL components");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    log("Program ended");
    return 0;
}


// if you ever want to compile this code to get it playable on android devices, here it is:
//ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk APP_PLATFORM=android-18
