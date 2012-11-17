#include "types.h"

void object::setTexture(GLuint t, bool solid=false)
{
    texture=t;
    isSolid=solid;
    cords=new float[8];
    cords[0]=cords[1]=cords[3]=cords[6]=0;
    cords[2]=cords[4]=cords[5]=cords[7]=1;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
}

void object::setCord(int x1, int y1)
{ x=x1; y=y1; }

void object::setTexCords(float *t)
{ if(cords!=0) delete [] cords; cords=t; }
