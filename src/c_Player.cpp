#include "c_Player.h"
c_Player::c_Player():tex(0),x(0),y(0),state(0)
{}
void c_Player::setSkin(char* path, bool solid)
{
    if(tex==0) tex=new c_Animation();
    tex->loadAnim(path);
    tex->getTexture()->isSolid=solid;
}

void c_Player::setCord(int cx, int cy)
{ x=cx; y=cy; tex->getTexture()->x=cx; tex->getTexture()->y=cy; }

void c_Player::move(int kx, int ky)
{
    x+=kx;
    y+=ky;
}
object* c_Player::getTex()
{
    object *tmp=tex->getFrame();
    tmp->x=x; tmp->y=y;
    return tmp;
}

c_Player::~c_Player()
{ delete tex; tex=0; }
