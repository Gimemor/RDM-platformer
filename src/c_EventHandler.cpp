#include "Event_Handler.h"

c_EventHandler::c_EventHandler():game(0),gr_Graph(0)
{
    resetKeys();
}

c_EventHandler::c_EventHandler(c_Game *g):game(g),gr_Graph(0)
{   resetKeys(); }

void c_EventHandler::resetKeys()
{
    for(int i=0; i<322; i++)
        keys[i]=0;
}

void c_EventHandler::setGame(c_Game *gr)
{
    game=gr;
}


void c_EventHandler::setGraph(c_Graphics *gr)
{
    gr_Graph=gr;
}


void c_EventHandler::handle(SDL_Event *e)
{
    switch(e->type)
    {
        case SDL_KEYDOWN:
            keys[e->key.keysym.sym]=true;  break;
        case SDL_KEYUP:
            keys[e->key.keysym.sym]=false; break;
        case SDL_QUIT:
            onExit();
    }
}

void c_EventHandler::onExit()
{
    game->exit();
}

void c_EventHandler::onKeyDown()
{
    if(keys[SDLK_UP]) gr_Graph->moveCamera(0,5);
    if(keys[SDLK_DOWN]) gr_Graph->moveCamera(0,-5);
    if(keys[SDLK_RIGHT]) gr_Graph->moveCamera(-5,0);
    if(keys[SDLK_LEFT]) gr_Graph->moveCamera(5,0);
    if(keys[SDLK_SPACE]) gr_Graph->restoreView();
}


void c_EventHandler::onKeyUp(SDL_Event *e)
{

}
c_EventHandler::~c_EventHandler()
{
     gr_Graph=0;
     game=0;
}
