//
//  GameScene.h
//  MyTetris
//
//  Created by Ludi on 6/18/14.
//
//

#ifndef MyTetris_GameScene_h
#define MyTetris_GameScene_h

#include "cocos2d.h"
#include "TetrisLogic.h"
#include "CCEventListener.h"
#include "CCEventKeyboard.h"
#include "Cube.h"

const std::string BLUE_IMG = "blue.png";
const std::string ORANGE_IMG = "orange.png";
const std::string GREEN_IMG = "green.png";
const std::string YELLOW_IMG = "yellow.png";
const std::string PINK_IMG = "pink.png";
const std::string PURPLE_IMG = "purple.png";
const std::string BROWN_IMG = "orange.png";
const std::string RED_IMG = "red.png";

const int WIDTH = 10;
const int HEIGHT = 15;

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    enum Cube_Color
    {
        Cube_blue = 0,
        Cube_green,
        Cube_purple,
        Cube_pink,
        Cube_yellow,
        Cube_orange,
        Cube_brown,
        Cube_Red,
    };
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void intervalCallback();
    std::string ParseColor(Cube_Color color);
    CREATE_FUNC(GameScene);
    void cubeDown(float time);
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    bool onTouchBegan(Touch* touch, Event  *event);
    Cube* getCube(int x,int y);
    
    
private:
    TetrisLogic* tetrislogic;
    Vector<Cube*> spritevec;
    
    
    
};

#endif
