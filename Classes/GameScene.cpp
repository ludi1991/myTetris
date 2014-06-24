//
//  GameScene.cpp
//  MyTetris
//
//  Created by Ludi on 6/18/14.
//
//

#include "GameScene.h"
#include "Cube.h"
#include "CCEventListener.h"
#include "CCEventKeyboard.h"
#include <vector>

USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    TetrisLogic::intervalFunc func = std::bind(&GameScene::intervalCallback,this);
    tetrislogic = new TetrisLogic(1.0 , WIDTH, HEIGHT, func);
    for (int j=0 ; j<HEIGHT ; j++)
    {
        for (int i=0 ; i<WIDTH ; i++)
        {
            auto cube = Cube::create(i,j);
            cube->setPosition(i*35+50,-j*35+600);
            this->addChild(cube);
            spritevec.pushBack(cube);
        }
    }
    schedule(schedule_selector(GameScene::cubeDown),0.1f);
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->setSwallowTouches(true);
    touchlistener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

       // tetrislogic->go();
    return true;
}

void GameScene::cubeDown(float time)
{
    tetrislogic->process();
    
    //intervalCallback() is supposed to be called in tetrislogic->process().
    //but it doesn't work. ??
    intervalCallback();
}

std::string GameScene::ParseColor(GameScene::Cube_Color color)
{
    switch (color)
    {
        case Cube_blue: return BLUE_IMG;
        case Cube_green: return GREEN_IMG;
        case Cube_orange: return ORANGE_IMG;
        case Cube_pink: return PINK_IMG;
        case Cube_purple: return PURPLE_IMG;
        case Cube_yellow: return YELLOW_IMG;
        case Cube_brown: return BROWN_IMG;
        case Cube_Red: return RED_IMG;
    }
}

void GameScene::intervalCallback()
{
    for (int i=0 ; i< tetrislogic->getMetricHeight();i++)
    {
        for (int j=0 ; j<tetrislogic->getMetricWidth();j++)
        {
            Cube* cube = spritevec.at(i*tetrislogic->getMetricWidth()+j);
            cube->setTexture(ParseColor((Cube_Color)tetrislogic->getMetric(j,i)));
        }
    }
    
    auto curshape = tetrislogic->getShape();
    for (auto it=curshape.begin() ;it!=curshape.end(); it++)
    {
        auto cube = getCube(it->x,it->y);
        cube->setTexture(ParseColor((Cube_Color)tetrislogic->getCurShapeValue()));
    }
    //printf("callback!!!");
}

Cube* GameScene::getCube(int x, int y)
{
    return spritevec.at(y*tetrislogic->getMetricWidth()+x);
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
        tetrislogic->tryMove(TetrisLogic::Direction::Down);
    else if (keyCode == EventKeyboard::KeyCode::KEY_A)
        tetrislogic->tryMove(TetrisLogic::Direction::Left);
    else if (keyCode == EventKeyboard::KeyCode::KEY_D)
        tetrislogic->tryMove(TetrisLogic::Direction::Right);
    printf("get!");
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto size = Director::getInstance()->getVisibleSize();
    
  //  printf("%f,%f",touch->getLocation().x,touch->getLocation().y);
    if (touch->getLocation().y > size.height/2) {
        tetrislogic->tryRotate(true);
    }
    else if (touch->getLocation().x > size.width/2) {
        tetrislogic->tryMove(TetrisLogic::Direction::Right);
    }
    else
    {
        tetrislogic->tryMove(TetrisLogic::Direction::Left);
        return true;
    }
}