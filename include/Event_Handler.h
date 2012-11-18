#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include "game.h"
class c_Game;
class c_Graphics;
class c_Player;
class c_EventHandler
{
    public:
        c_EventHandler();
        c_EventHandler(c_Game *g);
        void handle(SDL_Event *e);
        void onKeyDown();
        void onKeyUp();
        void setGame(c_Game *gr, c_Player *p);
        void setGraph(c_Graphics *gr);
        void resetKeys();
        void onExit();
        virtual ~c_EventHandler();
    protected:
    private:
        bool keys[322];
        c_Game *game;
        c_Graphics *gr_Graph;
        c_Player *pl;
};

#endif // EVENT_HANDLER_H
