#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <math.h>  //fmod

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

    class Brick {
       public:
          double h = 20;
          double w = 100;
          double x = 0;
          double y = 0;
    };

    Brick player;
    player.x = 250;
    player.y = 380;

    bool isRunning = true;
    //Generic event var for handling events
    SDL_Event event;

    while(isRunning) {

        //Ghetto update frequency
        SDL_Delay(20);

    //Event handling
        Uint8* keystate = SDL_GetKeyState(NULL);

        //continuous-response keys
        if(keystate[SDLK_LEFT]) {
            player.x -= 5;
        }
        if(keystate[SDLK_RIGHT]) {
             player.x += 5;
        }

        //On event
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    //window x button was pressed
                    isRunning = false;
                    break;
                case SDL_KEYUP:
                    //a key was released
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            isRunning = false;
                            break;
                        case SDLK_LEFT:
                            player.x -= 5;
                            break;
                        case SDLK_RIGHT:
                            player.x += 5;
                            break;
                        default:
                            //unused key, do nothing
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

    //Game Logic
        //wrap-around x axis
        if(player.x < 0) {
            player.x = fmod(player.x+600, 600);
        }
        player.x = fmod(player.x, 600);

    //Render Logic
        //Clear the screen with set color
        glClear(GL_COLOR_BUFFER_BIT);
        //Gives us the 'grid' we draw stuff on
        glPushMatrix();
        //Set the matrix size by multiplying an orthographic matrix
        glOrtho(0,600,400,0,-1,1);

        //Set the color of primitives
        glColor4f(.5,1,1,1);

        glBegin(GL_QUADS);//start drawing primitive
        glVertex2f(player.x, player.y);
        glVertex2f(player.x, player.y + player.h);
        glVertex2f(player.x + player.w, player.y + player.h);
        glVertex2f(player.x + player.w, player.y);
        glEnd(); //end drawing

        //Pops the matrix back to render on the screen
        glPopMatrix();
        //Pushes the write buffer to the screen
        SDL_GL_SwapBuffers();
    }

    //Wait on a key
    std::cin.get();
    SDL_Quit();
    return 0;
}
