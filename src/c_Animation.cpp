#include "c_Animation.h"

c_Animation::c_Animation():atlas(0),time(0)
{
    kX=1; kY=1;
}
void c_Animation::setState(int s)
{
   CurrentState=s;
}

void c_Animation::setDir(int x, int y)
{
    kX=x; kY=y;
}

object*  c_Animation::getTexture()
{
    GLfloat *cords=new GLfloat[8];
    cords[0]=0; cords[1]=0;
    cords[2]=1; cords[3]=0;
    cords[4]=1; cords[5]=1;
    cords[6]=0; cords[7]=1;
    atlas->setTexCords(cords);
    return atlas;
}

object* c_Animation::getFrame()
{
    GLfloat *cords=new GLfloat[8];
    cords[0]=(float)CurrentFrame/count; cords[1]=0;
    cords[2]=(CurrentFrame+1.0f)/count;  cords[3]=0;
    cords[4]=(CurrentFrame+1.0f)/count;  cords[5]=1;
    cords[6]=(float)CurrentFrame/count;  cords[7]=1;
    if(kX==-1)
    {
        cords[0]=cords[6]=(CurrentFrame+1.0f)/count;
        cords[2]=cords[4]=(float)CurrentFrame/count;;
    }
    if(kY==-1)
    {
        cords[1]=cords[3]=1;
        cords[5]=cords[7]=0;
    }


    atlas->setTexCords(cords);
    return atlas;
}

GLuint   c_Animation::getFrameH()
{ return frame_h; }

GLuint   c_Animation::getFrameW()
{ return frame_w; }

void c_Animation::loadAnim(char *path)
{
    std::ifstream inp(path);
    inp >> frame_w >> frame_h >> count >> fps;
    char st[255];
    inp >> st;
    atlas=new object();
    atlas->setTexture(loadTexture(st),1);
    inp >> states;
    int state=STATE_NOTHING;
    for(int i=0; i<states; i++)
    {
            inp >> st;
            if(strcmp(st,"STATE_NOTHING")==0) state=STATE_NOTHING;
            else if(strcmp(st,"STATE_JUMP")==0) state=STATE_JUMP;
            else if(strcmp(st,"STATE_RUN")==0) state=STATE_RUN;
            inp >> frames[state][0] >> frames[state][1];
    }
    CurrentFrame=0;
    CurrentState=STATE_RUN;
    CurrentFrame=2;
    atlas->w=frame_w; atlas->h=frame_h;
    time=0;
}

void c_Animation::update(Uint64 t)
{
    if(t-time>1000/fps)
        {CurrentFrame++; time=t; }
    if(CurrentFrame>frames[CurrentState][1] || CurrentFrame<frames[CurrentState][0]) CurrentFrame=frames[CurrentState][0];
}


c_Animation::~c_Animation()
{
    //dtor
}
