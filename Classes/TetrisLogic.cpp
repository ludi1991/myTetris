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
    srand((unsigned)time(NULL));
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
    if (curshape.size() == 0 ) return;
    if (canMove(curshape, direction)) {
        move(direction);
    }
    else
    {
        if (direction == Down) {
            stainShape();
            eraseLine();
        }
    }
}

void TetrisLogic::eraseLine()
{
    
}

void TetrisLogic::initShapeLib()
{
    ShapeOrigin shapei;
    shapei.push_back(Point(1,0));
    shapei.push_back(Point(0,0));
    shapei.push_back(Point(2,0));
    shapei.push_back(Point(3,0));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_I,shapei));
    
    ShapeOrigin shapej;
    shapej.push_back(Point(1,1));
    shapej.push_back(Point(0,1));
    shapej.push_back(Point(0,0));
    shapej.push_back(Point(2,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_J,shapej));
    
    ShapeOrigin shapel;
    shapel.push_back(Point(0,1));
    shapel.push_back(Point(0,0));
    shapel.push_back(Point(0,2));
    shapel.push_back(Point(1,2));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_L,shapel));
    
    ShapeOrigin shapeo;
    shapeo.push_back(Point(0,0));
    shapeo.push_back(Point(0,1));
    shapeo.push_back(Point(1,0));
    shapeo.push_back(Point(1,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_O,shapeo));
    
    ShapeOrigin shapes;
    shapes.push_back(Point(1,1));
    shapes.push_back(Point(2,0));
    shapes.push_back(Point(0,1));
    shapes.push_back(Point(1,0));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_S,shapes));
    
    ShapeOrigin shapez;
    shapez.push_back(Point(1,1));
    shapez.push_back(Point(1,0));
    shapez.push_back(Point(0,0));
    shapez.push_back(Point(2,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_Z,shapez));
    
    ShapeOrigin shapet;
    shapet.push_back(Point(1,1));
    shapet.push_back(Point(0,1));
    shapet.push_back(Point(1,0));
    shapet.push_back(Point(2,1));
    ShapeLib.insert(std::pair<ShapeType,ShapeOrigin>(Shape_T,shapet));
    
    
}

void TetrisLogic::process()
{
    if (!hasShape())
    {
        
        curshapetype = (ShapeType)(rand()%6);
        createShape(curshapetype);
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
            eraseLine();
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
    func();
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
    
    Point centerpos(shape[0].x, shape[0].y );
    for (auto it = shape.begin(); it != shape.end(); it++){
        int originX = it->x - centerpos.x;
        int originY = it->y - centerpos.y;
        it->x = originY + centerpos.x;
        it->y = -originX + centerpos.y;
        
    }
    for (auto it=shape.begin(); it!=shape.end(); it++) {
        int x = it->x;
        int y = it->y;
        if (x<0 || x>= getMetricWidth() || y<0 || y>= getMetricHeight() || getMetric(x, y) != 0)
        {
            
            return false;
        }
    }
    return true;
}

void TetrisLogic::rotate(bool clockwise)
{

    Point centerpos(curshape[0].x, curshape[0].y );
    for (auto it = curshape.begin(); it != curshape.end(); it++){
        int originX = it->x - centerpos.x;
        int originY = it->y - centerpos.y;
        it->x = originY + centerpos.x;
        it->y = -originX + centerpos.y;
    }
    func();
    
}

void TetrisLogic::tryRotate( bool clockwise)
{
    if (curshape.size() == 0) return;
    if (canRotate( curshape, clockwise)) {
        rotate(clockwise);
    }
    
}


TetrisLogic::Shape TetrisLogic::getShape()
{
    return curshape;
}
