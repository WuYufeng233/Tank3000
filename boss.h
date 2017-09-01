#ifndef BOSS_H
#define BOSS_H

#include"base.h"
#include"data.h"
class Boss: public Base
{
public:
    Boss();
    virtual void display(QPainter&paint);
    virtual void move(){}

    int getLife()const;

protected:
    virtual void calSphere();
};

#endif // BOSS_H
