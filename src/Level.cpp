#include "Level.h"

Level::Level():map(0)
{}

void Level::setLevel(int lw, int lh, object **m)
{
    map=m;
    w=lw; h=lh;
}

object* Level::getBlock(int x, int y)
{
    return &map[x][y];
}

int Level::getW()
{ return w; }
int Level::getH()
{ return h; }

void Level::unload()
{

    for(int i=0; i<w; i++)
        delete [] map[i];
    delete [] map;
    map=0;
}


Level::~Level()
{

    delete [] map;
    map=0;
}
