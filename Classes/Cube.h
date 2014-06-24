//
//  Cube.h
//  MyTetris
//
//  Created by Ludi on 6/18/14.
//
//

#ifndef MyTetris_Cube_h
#define MyTetris_Cube_h

#include "cocos2d.h"


class Cube : public cocos2d::Sprite
{
public:
    Cube(int x,int y);
    virtual bool init();
    static Cube* create(int x,int y);
    
private:
    int x;
    int y;
    
};

#endif
