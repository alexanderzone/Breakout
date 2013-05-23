#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

int main (int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    //Set the size of components for OpenGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Set title of application
    SDL_WM_SetCaption("Breakout", NULL);
    //Set dimensions, colors, renderer
    SDL_SetVideoMode(600,400,32, SDL_OPENGL);

    //Set the screen's clear color
    //Double values 0-1
    //Red, Green, Blue, Alpha(transparency)
    glClearColor(1,1,1,1); //white

    //Set the lower left corner of viewport in pixels,
    //as well as the dimensions of the window
    glViewport(0,0,600,400);

    //Set OpenGL to smooth shading so things like gradients look nice
    glShadeModel(GL_SMOOTH);

    //Leting OpenGL know we're using 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  //saves this option

    //Since 2D, we can disable depth checking
    glDisable(GL_DEPTH_TEST);


    std::cout << "OpenGL is running\n";

    //Wait on a key
    std::cin.get();
    SDL_Quit();
    return 0;
}
