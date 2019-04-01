#include <SDL2/SDL.h>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int main(int argc, char **argv)
{
    // Notre fenêtre
    
    SDL_Window* fenetre(0);
    SDL_Event evenements;
    bool terminer(false);
    
    
    // Initialisation de la SDL
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        
        return -1;
    }
    
    
    // Création de la fenêtre
    
    fenetre = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    if(fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        
        return -1;
    }
    
    
    // Boucle principale
    
    while(!terminer)
    {
        SDL_WaitEvent(&evenements);
        
        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = true;
        
        // test du pauvre
        /*
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBegin(GL_QUADS);
        glColor3ub(0,0,255);
        glVertex2d(-0.75,-0.75);
        glVertex2d(-0.75,0.75);
        glColor3ub(255,0,0);
        glVertex2d(0.75,0.75);
        glVertex2d(0.75,-0.75);
        glEnd();
        
        glFlush();
        */
        
    }
    
    
    // On quitte la SDL
    
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    return 0;
}
