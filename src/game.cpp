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
    setFPS(30);
    setKeyDelay(25); timer=0;
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gr_Graph->setClearColor(1.0f, 1.0f, 1.0f,0.0f);
    gr_Graph->setColor(0.0f, 0.0f, 0.0f, 0.0f);
    gr_Graph->setViewPort(0.0f, 0.0f, w_width, w_height);
    SDL_EnableKeyRepeat(1,1);
    return true;
}

void c_Game::loadTexture(char* name, char *file)
{
    GLuint texture;
    int COLOR_FLAG;
    SDL_Surface* img = IMG_Load(file);
    glGenTextures(0,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    COLOR_FLAG = (img->format->BitsPerPixel == 24)? GL_RGB:GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D,0,COLOR_FLAG,img->w, img->h,0,COLOR_FLAG,GL_UNSIGNED_BYTE,img->pixels);
    gr_Graph->saveTexture(texture,name);
    SDL_FreeSurface(img);
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
    loadTexture("one","./gfx/1.png");
    unsigned long ltFPS=0, ltKeyD=0; // count of ticks
    while(isRunning)
    {
        SDL_WaitEvent(&e);
        e_Handler->handle(&e);
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
    gr_Graph->drawSprite(0,480,32,32,"one");
    gr_Graph->drawQuad(32,480,32,32);
    gr_Graph->drawQuad(64,480,32,32);
    SDL_GL_SwapBuffers();
}



void c_Game::exit()
{
    isRunning=false;
}

void c_Game::clean()
{
    delete [] e_Handler;
    SDL_Quit();
}

c_Game::~c_Game()
{
    //dtor
}
