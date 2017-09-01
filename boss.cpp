#include "boss.h"

Boss::Boss()
{
    bool tmp=false;
    setDisappear(tmp);

    this->pos.setX(6*SegWidth);
    this->pos.setY(12*SegHeight);
    this->calSphere();
    this->life=100;
}

void Boss::display(QPainter &paint)
{
    if(!isDisappeared())
        paint.drawImage(rectSphere,glb.bossPix);

}

void Boss::calSphere()
{
    this->rectSphere.setRect(pos.x(),pos.y(),SegWidth,SegHeight);
}

int Boss::getLife()const
{
    return this->life;
}
