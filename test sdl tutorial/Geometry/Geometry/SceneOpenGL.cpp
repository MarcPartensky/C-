//
//  SceneOpenGL.cpp
//  Geometry
//
//  Created by Marc Partensky on 13/12/2019.
//  Copyright © 2019 Marc Partensky. All rights reserved.
//

#include "SceneOpenGL.hpp"

#include <iostream>


SceneOpenGL::SceneOpenGL(std::string title, int width, int height) {
    SceneOpenGL::title = title;
    SceneOpenGL::width = width;
    SceneOpenGL::height = height;
}

SceneOpenGL::~SceneOpenGL () {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool SceneOpenGL::init() {
    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
         std::cout << stderr << std::endl;
         std::cout << "Sdl couldn't be initialized." << std::endl;
         std::cout << SDL_GetError() << std::endl;
         SDL_Quit();
         return false;
     }

    // Creating Window
    window = SDL_CreateWindow("main",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << stderr << std::endl;
        std::cout << "The window couldn't be created." << std::endl;
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Creating context
    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cout << stderr << std::endl;
        std::cout << "The context couldn't be created." << std::endl;
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    // OpenGL Version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    // Switching from legacy profile to core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    return true;
}


void SceneOpenGL::main() {
//    vector<double> position(3, 0);
//    vector<double> rotation(3, 0);

    open = true;
    SDL_Event ev;
    while (open) {
        while (SDL_WaitEventTimeout(&ev, 15)) {
            switch (ev.type) {
                case SDL_QUIT:
                    open = false;
            }
        }
        show();
    }
}


void SceneOpenGL::draw() {
    glUseProgram(colorShader.getProgramID());
    
    glm::mat4 projection;
    glm::mat4 modelview;
    
    projection = glm::perspective(70.0, (double) width/height, 1.0, 100.0);
    modelview = glm::mat4(1.0);

    
//    // verticies
//    float vs1[] = {0.0, 0.0,   0.5, 0.0,   0.0, 0.5,          // Triangle 1
//                        -0.8, -0.8,   -0.3, -0.8,   -0.8, -0.3};   // Triangle 2
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vs1);
//    glEnableVertexAttribArray(0);

    // colors
    float colors[] = {0.0, 204.0 / 255.0, 1.0,    0.0, 204.0 / 255.0, 1.0,    0.0, 204.0 / 255.0, 1.0};
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(1);
    
    float vertices[] = {-0.5, -0.5, -1.0,   0.0, 0.5, -1.0,   0.5, -0.5, -1.0};
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);
    // On envoie les matrices au shader
    
    // Transformations of the matrix modelview
    modelview = translate(modelview, glm::vec3(0.4, 0.0, 1.0));
    modelview = rotate(modelview, 60.0f, glm::vec3(0.0, 0.0, 1.0));
    
    glUniformMatrix4fv(glGetUniformLocation(colorShader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
    glUniformMatrix4fv(glGetUniformLocation(colorShader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);

}

void SceneOpenGL::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void SceneOpenGL::swap() {
    SDL_GL_SwapWindow(window);
}

void SceneOpenGL::show() {
    clear();
    draw();
    swap();
}

bool SceneOpenGL::loadColorShader() {
    Shader colorShader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
    std::cout << "Shaders loaded successfully" << std::endl;
    return colorShader.load();
}

