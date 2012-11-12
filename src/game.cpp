#include "game.h"
#include <iostream>
c_Game::c_Game():w_width(768),w_height(512),e_Handler(0), isRunning(0),gr_Graph(0)
{}

c_Game::c_Game(int w, int h):w_width(w),w_height(h),e_Handler(0), isRunning(0),gr_Graph(0)
{}

bool c_Game::setup()
{
    isRunning=true;
    e_Handler=new c_EventHandler();
    gr_Graph=new c_Graphics();
    e_Handler->setGraph(gr_Graph);
    e_Handler->setGame(this);
    setFPS(30);
    setKeyDelay(25); timer=0;
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gr_Graph->setClearColor(1.0f, 1.0f, 1.0f,1.0f);
    gr_Graph->setColor(0.0f, 0.0f, 0.0f, 1.0f);
    gr_Graph->setViewPort(0.0f, 0.0f, w_width, w_height);
    SDL_EnableKeyRepeat(1,1);
    return true;
}

GLuint c_Game::loadTexture(char *file)
{

        SDL_Surface* surface = IMG_Load(file);
        GLuint texture;
        glPixelStorei(GL_UNPACK_ALIGNMENT,4);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        SDL_PixelFormat *format = surface->format;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        if (format->Amask)
        {
                gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
                surface->w, surface->h, GL_RGBA,GL_UNSIGNED_BYTE, surface->pixels);
        }
        else
        {
                gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        }
        SDL_FreeSurface(surface);
        return texture;

}


void c_Game::setFPS(int x)
{ fps=x ; }
void c_Game::setKeyDelay(int x)
{ KeyDelay=x; }

int c_Game::run()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) return -1;
    if(SDL_SetVideoMode(w_width, w_height, 0, SDL_HWSURFACE | SDL_OPENGL)==0) return -1;
    setup();
    SDL_Event e;
    tex1=loadTexture("1.png");

    unsigned long ltFPS=0, ltKeyD=0; // count of ticks
    while(isRunning)
    {
        while(SDL_PollEvent(&e))
         {
            e_Handler->handle(&e);
         }
        timer=SDL_GetTicks();
        if(timer/fps>ltFPS)
         { render(); ltFPS=timer/fps; }
        if(timer/KeyDelay>ltKeyD)
         { e_Handler->onKeyDown(); ltKeyD=timer/KeyDelay; }

    }



    clean();
    return 0;
}

void c_Game::render()
{
    gr_Graph->clear();
    for(int i=0;i<12;i++)
        for(int j=5;j<8;j++)
            gr_Graph->drawSprite(i*64,j*64,64,64,tex1);
    SDL_GL_SwapBuffers();
}



void c_Game::exit()
{
    isRunning=false;
}

void c_Game::clean()
{
    e_Handler->setGraph(0); e_Handler->setGame(0);
    delete   e_Handler;
    delete   gr_Graph;
    gr_Graph=0; e_Handler=0;
    SDL_Quit();
    glDeleteTextures(GL_TEXTURE_2D, &tex1);
}

c_Game::~c_Game()
{
}
