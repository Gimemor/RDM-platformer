#include "game.h"
#include <iostream>



c_Game::c_Game():w_width(768),w_height(512),e_Handler(0), isRunning(0),gr_Graph(0),map(0),player(0)
{}

c_Game::c_Game(int w, int h):w_width(w),w_height(h),e_Handler(0), isRunning(0),gr_Graph(0),map(0),player(0)
{}

bool c_Game::setup()
{
    isRunning=true;
    e_Handler=new c_EventHandler();
    gr_Graph=new c_Graphics();
    player=new c_Player();
    e_Handler->setGraph(gr_Graph);
    e_Handler->setGame(this,player);
    setFPS(60);
    setKeyDelay(25); timer=0;
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_LIGHTING);
    glAlphaFunc(GL_GREATER, 0.5);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    setCaption("Game","");
    gr_Graph->setClearColor(0.0f, 0.0f, 0.0f,0.0f);
    gr_Graph->setColor(1.0f, 1.0f,  1.0f, 1.0f);
    gr_Graph->setViewPort(0.0f, 0.0f, w_width, w_height);
    loadLevel("level1/config.ini");
    player->setSkin("gfx/player.anim",1);
    player->setCord(8*32,31*32);
    SDL_EnableKeyRepeat(1,1);

    return true;
}

void c_Game::setCaption(char *file, char *icon)
{  SDL_WM_SetCaption(file, icon);  }

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
    Uint64 ltFPS=0, ltKeyD=0; // count of ticks
    timer=0;
   // setKeyDelay(2);
    while(isRunning)
    {
        while(SDL_PollEvent(&e))
         {
            e_Handler->handle(&e);
         }
        timer=SDL_GetTicks(); 
        if(timer-ltFPS>1000/fps)
        {render(); ltFPS=timer; }
        if(timer-ltKeyD>1000/KeyDelay)
         {  e_Handler->onKeyUp(); e_Handler->onKeyDown(); ltKeyD=timer; }
    }
    clean();
    return 0;
}

void c_Game::render()
{
    gr_Graph->clear();
    draw_level();
    gr_Graph->setColor(1.0, 1.0f, 1.0f, 1.0f);
    gr_Graph->drawSprite(player->getTex());
 player->update(SDL_GetTicks());
    SDL_GL_SwapBuffers();
}


void c_Game::draw_level()
{
    int camx=gr_Graph->getCamX();
    int camy=gr_Graph->getCamY();
    int tile_w=gr_Graph->getTileW();
    int tile_h=gr_Graph->getTileH();
    int max_x=camx/tile_w+w_width/tile_w;
    int max_y=camy/tile_h+w_height/tile_h;
    if(max_x>map->getW()) max_x=map->getW();
    if(max_y>map->getH()) max_y=map->getH();
    gr_Graph->setColor(5.0, 5.0f, 5.0f, 1.0f);
  //  gr_Graph->drawSprite(camx,camy, w_width, w_height, map->getBackground());
    gr_Graph->drawSprite(0,0, map->getW()*tile_w, map->getH()*tile_h, map->getBackground());
    gr_Graph->setColor(0.5, 0.5f, 0.5f, 1.0f);
    for(int i=camx/tile_w; i<max_x+1; i++)
    {
        for(int j=camy/tile_h; j<max_y+1; j++)
        {
            object *tmp=map->getBlock(i,j);
            if(tmp->texture==0) continue;
            gr_Graph->drawSprite(i*tmp->w, j*tmp->h, tmp->w, tmp->h, tmp->texture);
        }
    }

}

void c_Game::exit()
{ isRunning=false; }


void  c_Game::setResolution(int w, int h)
{
    w_width=w;
    w_height=h;
    if(SDL_SetVideoMode(w_width, w_height, 0, SDL_HWSURFACE | SDL_OPENGL)==0) return;
    gr_Graph->setViewPort(0.0f, 0.0f, w_width, w_height);
    setup();
}






void c_Game::loadLevel(char *file)
{
        std::ifstream in(file);
        std::cout << file << std::endl;
        if(map>0) map->unload();
        int w,h,n;
        char path[255]; bool type;
        in >> n >> w >> h;
        n++;
        object tex[n]; tex[0].texture=0;
        gr_Graph->setSize(w_width,w_height,w,h,w,h);
        for(int i=1; i<n;i++)
        {
           in >> path >> type;
            std::cout << path << std::endl;
           tex[i].setTexture(loadTexture(path),type);
           tex[i].w=w; tex[i].h=h;
        }
        map=new Level();
        in >> n;
        if(n==1)
        {
            in >> path;
            map->setBackground(loadTexture(path));
        }
        else map->setBackground(0);
        std::cout << path << std::endl;

        object **a=0;
        in >> w >> h;
        gr_Graph->setTilesCount(w,h);
        w+=2; h+=2;
        a=new object *[w];
        for(int i=0; i<w; i++)
            a[i]=new object[h];
        w-=2; h-=2;
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
            {
                in >> n;
                a[j][i]=tex[n];
            }
        map->setLevel(w,h,a);
        in.close();
}

void c_Game::unloadLevel()
{
   if(map==0) return;
   map->unload();
   delete [] map;
   map=0;
}

void c_Game::clean()
{
    if(map>0) map->unload();
    e_Handler->setGraph(0); e_Handler->setGame(0,0);
    delete   e_Handler;
    delete   gr_Graph;
    gr_Graph=0; e_Handler=0;
    SDL_Quit();
}

c_Game::~c_Game()
{
}
