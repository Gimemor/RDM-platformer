#ifndef C_GRAPHICS_H
#define C_GRAPHICS_H
#include "game.h"

class c_Graphics
{
    public:
        c_Graphics();
        void drawQuad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
        void setClearColor(float R, float G, float B, float A);
        void setColor(float R, float G, float B, float A);
        void scale(float w, float h);
        void moveCamera( float x, float y);
        void restoreView();
        void saveTexture(GLuint t, char *n);
        void use_texture(char* name);
        void drawSprite(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, char *name);
        void clear();
        void setViewPort(float x, float y, float w, float h);
        virtual ~c_Graphics();
    protected:
    private:
        std::map<char*, GLuint> textures;
        GLfloat r,g,b,a; // Current Color
        GLfloat cR,cG,cB,cA; // clear Color
        GLint w_width,w_height;
};

#endif // C_GRAPHICS_H
