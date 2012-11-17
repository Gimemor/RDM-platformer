#include "Functions.h"

GLuint loadTexture(char *file)
{
        SDL_Surface* surface = IMG_Load(file);
        GLuint texture;
        glPixelStorei(GL_UNPACK_ALIGNMENT,4);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        SDL_PixelFormat *format = surface->format;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        if (format->Amask)
        {
                gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
                surface->w, surface->h, GL_RGBA,GL_UNSIGNED_BYTE, surface->pixels);
        }
        else
        {
                gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
                surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        }
        SDL_FreeSurface(surface);
        return texture;

}
