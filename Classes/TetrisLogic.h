//
//  TetrisLogic.h
//  MyTetris
//
//  Created by Ludi on 6/18/14.
//
//

#ifndef MyTetris_TetrisLogic_h
#define MyTetris_TetrisLogic_h

#include <vector>
#include <map>
#include <functional>
#include <thread>

class TetrisLogic
{
public:
    enum Direction
    {
        Up = 0,
        Down,
        Left,
        Right,
    };
    
    enum ShapeType
    {
        Shape_I = 1,
        Shape_J,
        Shape_L,
        Shape_O,
        Shape_S,
        Shape_Z,
        Shape_T,
        Shape_AXIBA,
    };
    
    struct Point
    {
        int x;
        int y;
        Point(int x,int y):x(x),y(y){};
    };
    
    typedef std::function<void()> intervalFunc;
    typedef std::vector<Point> Shape;
    
    
    TetrisLogic(float duration,int width,int height,intervalFunc intervalfunc);
    ~TetrisLogic();
    void init();
    bool createShape(ShapeType type);
    //bool cubeDown();
    void process();
   
    void tryRotate(bool clockwise);
    bool canRotate(Shape shape,bool clockwise);
    void rotate(bool clockwise);
    
    void tryMove(Direction direction);
    void move(Direction direction);
    bool canMove(Shape shape,Direction direction);
    
    Shape getShape();
    ShapeType getCurShapeValue(){return curshapetype;}
    bool hasShape(){return !curshape.empty();}
    
    int getMetric(int x,int y){return metric[y][x];}
    void setMetric(int x,int y,int value){metric[y][x] = value;}
    int getMetricHeight(){return metric.size();}
    int getMetricWidth(){return metric[0].size();}
    
    void stainShape();
    
    
private:
    
    void initShapeLib();
    
    intervalFunc func; 
    std::vector<std::vector<int>> metric;   //game metric
    Shape curshape;
    ShapeType curshapetype;
    float duration;
    typedef std::vector<Point> ShapeOrigin;
    typedef std::map<ShapeType,ShapeOrigin> defShapeLib;
    static defShapeLib ShapeLib;
};

#endif
