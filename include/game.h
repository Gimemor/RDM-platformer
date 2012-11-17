#ifndef GAME_H
#define GAME_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <fstream>
#include <Box2D.h>
#include "Event_Handler.h"
#include "c_Graphics.h"
#include "Level.h"
#include "c_Player.h"
#include "types.h"
#include "Functions.h"
class c_EventHandler;
class c_Graphics;
class Level;
class c_Player;
extern GLuint loadTexture(char *path);

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
        void setFPS(int x);
        void draw_level();
        void setKeyDelay(int x);
        void setResolution(int w, int h);
        void setCaption(char *file, char *icon);
        void loadLevel(char *file);
        void unloadLevel();
        virtual ~c_Game();
    protected:
    private:
        uint32 timer;
        int fps;
        int KeyDelay;
        int w_width;
        int w_height;
        c_EventHandler *e_Handler;
        bool isRunning;
        c_Graphics *gr_Graph;
        Level *map;
        c_Player* player;

};

#endif // GAME_H
