#include "../include/game.h"

c_Game::c_Game():w_width(480),w_height(320),e_Handler(0)
{}

c_Game::c_Game(int w, int h):w_width(w),w_height(h),e_Handler(0)
{}

bool c_Game::setup()
{
    e_Handler=new c_EventHandler();
    glClearColor(0.0f, 0.0f, 1.0f,0.0f);
    return true;
}

int c_Game::run()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) return -1;
    if(SDL_SetVideoMode(w_width, w_height, 0, SDL_HWSURFACE | SDL_OPENGL)==0) return -1;
    setup();
    SDL_Event e;
    while(e.type!=SDL_QUIT)
    {
        render();
        SDL_PollEvent(&e);
    }
    return 0;
}

void c_Game::render()
{
    glClear(GL_CLEAR_COLOR_BIT);
}



c_Game::~c_Game()
{
    //dtor
}
