//
//  Cube.cpp
//  MyTetris
//
//  Created by Ludi on 6/18/14.
//
//

#include "Cube.h"
#include "cocos2d.h"

USING_NS_CC;

Cube::Cube(int thex,int they):
x(thex)
,y(they)
,cocos2d::Sprite()
{
    
}



bool Cube::init()
{
    initWithTexture(nullptr, Rect::ZERO );
    setPosition(x * 30,  y*30);
    setTexture("blue.png");
    return true;

}

Cube* Cube::create(int x,int y)
{
    Cube *pRet = new Cube(x,y);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}