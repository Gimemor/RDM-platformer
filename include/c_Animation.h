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
        void update();
        GLuint   getFrameW();
        GLuint   getFrameH();

        virtual ~c_Animation();
    protected:
    private:
        int states;
        int CurrentState;
        int CurrentFrame;
        int frame_w; int frame_h;
        int count;
        int frames[STATES][2];
        unsigned long time;
        object *atlas;
};

#endif // C_ANIMATION_H
