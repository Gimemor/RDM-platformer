#include "types.h"

void object::setTexture(GLuint t, bool solid=false)
{
    texture=t;
    isSolid=solid;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
}

void object::setCord(int x1, int y1)
{ x=x1; y=y1; }
