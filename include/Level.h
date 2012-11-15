#ifndef LEVEL_H
#define LEVEL_H
#include "game.h"
#include "types.h"
struct object;
class Level
{
    public:
        Level();
        void setLevel( int w, int h, object *map[]);
        object* getBlock(int x, int y);
        void unload();
        GLuint getBackground();
        void setBackground(GLuint b);
        int getW(); int getH();
        virtual ~Level();
    private:
        GLuint background;
        object **map;
        int w; int h;  // size of level ( tiles );
};

#endif // LEVEL_H
