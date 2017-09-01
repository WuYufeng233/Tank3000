#ifndef BASE_H
#define BASE_H
//大基类，可以派生出各种其他模块

#include<QPoint>
#include<QRect>
#include<QPainter>
enum Direction{Up,Down,Left,Right};

class Base
{
public:
    friend class Missile;
    friend class Tank;
    Base(){}

    virtual void display(QPainter &paint)=0;//纯虚函数，用于绘制图片
    virtual void move()=0;//纯虚函数，用于移动
    bool isDisappeared() const;//判断是否存在
    bool isCollision(const Base &base) const;//判断两物体是否碰撞
    virtual void setDisappear(bool disappear);//设置存在状态
    QPoint getPos() const;//获取左上角点坐标
    virtual void beAttacked(int attack);//被攻击扣血

protected:
    QPoint pos;//左上角点坐标
    QRect rectSphere;//所及范围
    Direction dir;//前进方向
    bool disappear;//存在状态
    int step;//步进长
    int life;//血量
    int attack;//攻击力

    virtual void calSphere()=0;


};

#endif // BASE_H
