#ifndef C_PLAYER_H
#define C_PLAYER_H
#include "game.h"
#include "c_Animation.h"
class c_Animation;
class c_Player
{
    public:
        c_Player();
        void setSkin(char *path, bool solid);
        void setCord(int cx, int cy );
        void move(int kx, int ky);
        object* getTex();
        ~c_Player();
    private:
        c_Animation *tex;
        int x; int y;
        int state;

};

#endif // C_PLAYER_H
