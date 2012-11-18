#ifndef C_ANIMATION_H
#define C_ANIMATION_H
#define STATES 3
#include <fstream>
#include <iostream>
#include <cstring>
#include "types.h"
#include "game.h"
#include "Functions.h"
enum {STATE_NOTHING=0, STATE_RUN, STATE_JUMP};

class c_Animation
{
    public:
        c_Animation();
        void setState(int s);
        void loadAnim(char *path);
        object* getFrame();
        object*    getTexture();
        void update(Uint64 t);
        GLuint   getFrameW();
        GLuint   getFrameH();
        void setDir(int x, int y);

        virtual ~c_Animation();
    protected:
    private:
        int states;
        int CurrentState;
        int CurrentFrame;
        int frame_w; int frame_h;
        int count;
        int frames[STATES][2];
        unsigned int fps;
        int kX; int kY;
        object *atlas;
        Uint64 time;
};

#endif // C_ANIMATION_H
