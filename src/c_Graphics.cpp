#include "c_Graphics.h"
#include <stdio.h>
c_Graphics::c_Graphics()
{
    setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    setColor(1.0f, 1.0f, 1.0f, 0.0f);
}
void c_Graphics::setColor(float R, float G, float B, float A)
{ r=R; g=G; b=B; a=A;}

void c_Graphics::setClearColor(float R, float G, float B, float A)
{ cR=R; cG=G; cB=B; cA=A;}

void c_Graphics::scale(float w, float h)
{
    glScalef(w,h,0.0f);
}

void c_Graphics::moveCamera( float x, float y)
{
    glTranslatef(x,y,0);
}
void c_Graphics::restoreView()
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPushMatrix();
}


void c_Graphics::setViewPort(float x=0, float y=0, float w=768, float h=512)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0 ,1,-1);
    glViewport(x,y,w,h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void c_Graphics::drawQuad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glColor4f(r,g,b,a);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x1,y1,0);
    glBegin(GL_QUADS);
    {
            glVertex2f(0,0);
            glVertex2f(x2,0);
            glVertex2f(x2,y2);
            glVertex2f(0,y2);
    }
    glEnd();
    glPopMatrix();

}


void c_Graphics::drawSprite(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLuint tex1)
{
    glEnable(GL_TEXTURE_2D);
    glColor4f(r,g,b,a);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x1,y1,0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glBegin(GL_QUADS);
    {
            glTexCoord2f( 0, -1); glVertex2f(0,0);
            glTexCoord2f( 0, 0);  glVertex2f(x2,0);
            glTexCoord2f( 1, 0);  glVertex2f(x2,y2);
            glTexCoord2f( 1, -1);   glVertex2f(0,y2);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
void c_Graphics::drawSprite(object *tex)
{ drawSprite(tex->x, tex->y, tex->w, tex->h, tex->texture); }


void c_Graphics::clear()
{
   glClearColor(cR,cG,cB,cA);
   glClear(GL_COLOR_BUFFER_BIT );
}
c_Graphics::~c_Graphics()
{

}
