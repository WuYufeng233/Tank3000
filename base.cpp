#include "base.h"

bool Base::isDisappeared()const
{
    return disappear;
}

bool Base::isCollision(const Base &base) const
{
    //返回true为碰撞，返回false为不碰撞
    if(disappear==true||base.disappear==true
            ||base.rectSphere.left()>rectSphere.right()
            ||base.rectSphere.right()<rectSphere.left()
            ||base.rectSphere.top()>rectSphere.bottom()
            ||base.rectSphere.bottom()<rectSphere.top())
    {
        return false;
    }
    else
        return true;
}

void Base::setDisappear(bool disappear)
{
    this->disappear=disappear;
}

QPoint Base::getPos()const
{
    return pos;
}

void Base::beAttacked(int attack)
{
    life-=attack;

    if(life<=0)
    {
        disappear=true;
        life=0;
    }
}
