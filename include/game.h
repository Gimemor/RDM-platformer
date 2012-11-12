#ifndef GAME_H
#define GAME_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <Box2D.h>
#include "Event_Handler.h"
#include "c_Graphics.h"
class c_EventHandler;
class c_Graphics;
class c_Game
{
    public:
        c_Game();
        c_Game(int w, int h);
        int run();
        bool setup();
        void exit();
        void render();
        void clean();
        GLuint loadTexture(char *file)  ;
        void setFPS(int x);
        void setKeyDelay(int x);
        virtual ~c_Game();
    protected:
    private:
        GLuint tex1;
        uint32 timer;
        int fps;
        int KeyDelay;
        int w_width;
        int w_height;
        c_EventHandler *e_Handler;
        bool isRunning;
        c_Graphics *gr_Graph;





};

#endif // GAME_H
