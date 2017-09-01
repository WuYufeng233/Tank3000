#ifndef MAPSEG_H
#define MAPSEG_H

#include"base.h"
#include"data.h"

const int mapSegNum=7;//地图块种类：nothing 0, wall 1, steel 2, sand 3, water 4, grass 5, boss 6

class mapSeg:public Base
{
public:
    static int lifes[mapSegNum];
    static bool penetration_1[mapSegNum];//坦克能否穿透地图块
    static bool penetration_2[mapSegNum];//导弹能否穿透地图块

    mapSeg(int=0,int=0);
    void modifyMapSeg(int i,int j);

    virtual void display(QPainter &paint);//绘图
    virtual void move(){}//移动,无需移动，函数体为空

    int getKind()const;
    virtual void beAttacked(int attack);

    int kind;//地图块种类：nothing 0, wall 1, steel 2, sand 3, water 4, grass 5

    bool isPenetration1()const;
    bool isPenetration2()const;

protected:
    bool penetration1;//坦克能否穿透地图块
    bool penetration2;//导弹能否穿透地图块

    virtual void calSphere();



};

#endif // MAPSEG_H
