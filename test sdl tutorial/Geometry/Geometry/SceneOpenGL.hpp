//
//  SceneOpenGL.hpp
//  Geometry
//
//  Created by Marc Partensky on 13/12/2019.
//  Copyright © 2019 Marc Partensky. All rights reserved.
//

#ifndef SceneOpenGL_hpp
#define SceneOpenGL_hpp


// Includes OpenGL
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

// Includes Glm
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Includes autres

#include <stdio.h>
#include <string>
#include <iostream>
#include <SDL.h>
#include "Shader.h" // Shaders


class SceneOpenGL
{
    // Methods
public:
    SceneOpenGL(std::string title, int width, int height);
    ~SceneOpenGL();
    bool init();
    void main();
    void show();
    void clear();
    void swap();
    void draw();
    bool loadColorShader();
    
    // Attributes
public:
    std::string title;
    int width;
    int height;
    bool open;
protected:
    SDL_Window* window;
    SDL_GLContext context;
    SDL_Event event;
    glm::mat4 projection;
    glm::mat4 modelview;
    Shader colorShader;
};


#endif /* SceneOpenGL_hpp */
