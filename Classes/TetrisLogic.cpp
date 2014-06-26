//
//  TetrisLogic.cpp
//  MyTetris
//
//  Created by Ludi on 6/18/14.
//
//

#include "TetrisLogic.h"
#include <map>
#include <time.h>
#include <random>

auto TetrisLogic::ShapeLib = TetrisLogic::defShapeLib();

TetrisLogic::TetrisLogic(float theduration,int width,int height,intervalFunc thefunc)
:metric(std::vector<std::vector<int>>(height,std::vector<int>(width,0)))
,duration(theduration)
,func(thefunc)
{
    init();
}

void TetrisLogic::init()
{
    if (ShapeLib.empty())
        initShapeLib();
}

bool TetrisLogic::createShape(TetrisLogic::ShapeType type)
{
    Shape shape;
    Point startpos(getMetricWidth()/2-2,0);
    auto it = ShapeLib.find(type);
    if (it != ShapeLib.end())
    {
        ShapeOrigin shapeorigin = it->second;
        for (auto it = shapeorigin.begin(); it!=shapeorigin.end(); it++) {
            shape.push_back(Point(startpos.x+it->x,startpos.y+it->y));
        }
    }
    curshape = shape;
    curshapetype = type;
    return true;
}

void TetrisLogic::tryMove(TetrisLogic::Direction direction)
{
    if (canMove(curshape, direction)) {
        move(direction);
    }
    else
    {
        if (direction == Down) {
            stainShape();
        }
    }
}

void TetrisLogic::initShapeLib()
{
    ShapeOrigin shapei;
    shapei.push_back(Point(0,0));
    shapei.push_back(Point(1,0));
    shapei.push_back(Point(2,0));
    shapei.push_back(Point(3,0));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_I,shapei));
    
    ShapeOrigin shapej;
    shapej.push_back(Point(0,0));
    shapej.push_back(Point(0,1));
    shapej.push_back(Point(1,1));
    shapej.push_back(Point(2,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_J,shapej));
    
    ShapeOrigin shapel;
    shapel.push_back(Point(0,0));
    shapel.push_back(Point(1,0));
    shapel.push_back(Point(2,0));
    shapel.push_back(Point(2,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_L,shapel));
    
    ShapeOrigin shapeo;
    shapeo.push_back(Point(0,0));
    shapeo.push_back(Point(0,1));
    shapeo.push_back(Point(1,0));
    shapeo.push_back(Point(1,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_O,shapeo));
    
    ShapeOrigin shapes;
    shapes.push_back(Point(1,0));
    shapes.push_back(Point(2,0));
    shapes.push_back(Point(0,1));
    shapes.push_back(Point(1,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_S,shapes));
    
    ShapeOrigin shapez;
    shapez.push_back(Point(0,0));
    shapez.push_back(Point(1,0));
    shapez.push_back(Point(1,1));
    shapez.push_back(Point(2,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_Z,shapez));
    
    ShapeOrigin shapet;
    shapet.push_back(Point(1,0));
    shapet.push_back(Point(0,1));
    shapet.push_back(Point(1,1));
    shapet.push_back(Point(2,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_T,shapet));
    
    
}

void TetrisLogic::process()
{
    if (!hasShape())
    {
        srand((unsigned)time(NULL));
        createShape((ShapeType)(rand()%6));
    }
    else
    {
        if (canMove(curshape,Down))
        {
            move(Down);
        }
        else
        {
            stainShape();
        }
    }
   
    
    func();
    
}

void TetrisLogic::stainShape()
{
    for (auto it=curshape.begin();it!=curshape.end();it++){
        setMetric(it->x,it->y,(int)curshapetype);
    }
    curshape.clear();
}

void TetrisLogic::move(TetrisLogic::Direction direction)
{
    for (auto it=curshape.begin(); it!=curshape.end();it++){
        if (direction == Down) {
            it->y++;
        }
        else if (direction == Left) {
            it->x--;
        }
        else if (direction == Right) {
            it->x++;
        }
    }
}

bool TetrisLogic::canMove(Shape shape, TetrisLogic::Direction direction)
{
    for (auto it=shape.begin(); it!=shape.end(); it++) {
        if (direction == Down) {
            it->y++;
        }
        else if (direction == Left) {
            it->x--;
        }
        else if (direction == Right) {
            it->x++;
        }
    }
    for (auto it=shape.begin(); it!=shape.end(); it++) {
        int x = it->x;
        int y = it->y;
        if (x<0 || x>= getMetricWidth() || y<0 || y>= getMetricHeight() || getMetric(x, y) != 0)
        {
            printf("ssd");
            return false;
        }
    }
    return true;
}

bool TetrisLogic::canRotate(Shape shape,bool clockwise)
{
    if (curshapetype == Shape_O) {
        return false;
    }
    
    for (auto it=shape.begin(); it!=shape.end(); it++) {
        
    }
    
    return true;
}

void TetrisLogic::rotate(bool clockwise)
{
    
}

void TetrisLogic::tryRotate(bool clockwise)
{
    
}


TetrisLogic::Shape TetrisLogic::getShape()
{
    return curshape;
}
