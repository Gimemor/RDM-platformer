#include "c_Graphics.h"
#include <stdio.h>
c_Graphics::c_Graphics()
{
    cam_x=cam_y=0;
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
void c_Graphics::setSize(GLint w_wid, GLint w_heig, GLint t_wid=32, GLint t_heig=32, GLint t_x=32, GLint t_y=32)
{
    w_height=w_heig; tiles_x=t_x;
    w_width=w_wid;   tiles_y=t_y;
    tile_width=t_wid;
    tile_height=t_heig;
}
void c_Graphics::setTilesCount(GLint t_x, GLint t_y)
{
    tiles_x=t_x; tiles_y=t_y;
}


void c_Graphics::moveCamera( float x, float y)
{
   if(cam_x-x>=0 && cam_x-x<=tile_width*tiles_x-w_width && cam_y-y>=0 && cam_y-y<=(tile_height*tiles_y)-w_height )
    {

        cam_x-=x;
        cam_y-=y;
        glTranslatef(x,y,0);
    }
}

void c_Graphics::setCamCords( float x, float y)
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPushMatrix();
    cam_x=x;
    cam_y=y;
    glTranslatef(-x,-y,0);
}
int  c_Graphics::getWinWidth()
{ return w_width; }

int  c_Graphics::getWinHeight()
{ return w_height; }



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
            glTexCoord2f( 0, 0); glVertex2f(0,0);
            glTexCoord2f( 1, 0);  glVertex2f(x2,0);
            glTexCoord2f( 1, 1);  glVertex2f(x2,y2);
            glTexCoord2f( 0, 1);   glVertex2f(0,y2);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void c_Graphics::drawSprite(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLuint tex1, GLfloat *cord)
{
    glEnable(GL_TEXTURE_2D);
    glColor4f(r,g,b,a);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x1,y1,0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glBegin(GL_QUADS);
    {
            glTexCoord2f( cord[0], cord[1]);  glVertex2f(0,0);
            glTexCoord2f( cord[2], cord[3]);  glVertex2f(x2,0);
            glTexCoord2f( cord[4], cord[5]);  glVertex2f(x2,y2);
            glTexCoord2f( cord[6], cord[7]);  glVertex2f(0,y2);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}



void c_Graphics::drawSprite(object *tex)
{ drawSprite(tex->x, tex->y, tex->w, tex->h, tex->texture, tex->cords); }



int c_Graphics::getTileW()
{ return tile_width; }
int c_Graphics::getTileH()
{ return tile_height; }
int c_Graphics::getCamX()
{ return cam_x; }
int c_Graphics::getCamY()
{ return cam_y; }
void c_Graphics::clear()
{
   glClearColor(cR,cG,cB,cA);
   glClear(GL_COLOR_BUFFER_BIT );
}
c_Graphics::~c_Graphics()
{

}
