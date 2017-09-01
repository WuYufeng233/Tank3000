#ifndef MISSILE_H
#define MISSILE_H

#include"base.h"
#include"tank.h"
#include"data.h"
#include"boss.h"

class Missile: public Base
{
public:
    friend class Tank;
    Missile(const Tank&tank);

    virtual void display(QPainter&paint);
    virtual void move();

    int getKind()const;

    bool isCollision1(Boss &boss)const;

protected:
    virtual void calSphere();

private:
    int kind;
    int group;//导弹所在组
};

#endif // MISSILE_H
