#include "mapseg.h"
#include<QImage>

//mapSegNum=7
int mapSeg::lifes[mapSegNum]={0,400,100000,0,0,0,100};
bool mapSeg::penetration_1[mapSegNum]={true,false,false,true,false,true,false};
bool mapSeg::penetration_2[mapSegNum]={true,false,false,true,true,true,false};

mapSeg::mapSeg(int i,int j)
{
    this->pos.setX(SegWidth*j);
    this->pos.setY(SegHeight*i);
    this->calSphere();
    this->disappear=false;
    this->kind=0;
    this->life=lifes[this->kind];
    this->penetration1=penetration_1[this->kind];
    this->penetration2=penetration_2[this->kind];
}

void mapSeg::modifyMapSeg(int i, int j)
{
    this->pos.setX(SegWidth*j);
    this->pos.setY(SegHeight*i);
    this->calSphere();
    this->disappear=false;
    this->life=lifes[this->kind];
    this->penetration1=penetration_1[this->kind];
    this->penetration2=penetration_2[this->kind];
}


void mapSeg::display(QPainter &paint)
{
    if(this->isDisappeared())
        return;

    switch(this->kind)
    {
    case 0:
        break;
    case 1:
        paint.drawImage(rectSphere,glb.images[0]);
        break;
    case 2:
        paint.drawImage(rectSphere,glb.images[1]);
        break;
    case 3:
        paint.drawImage(rectSphere,glb.images[2]);
        break;
    case 4:
        paint.drawImage(rectSphere,glb.images[3]);
        break;
    case 5:
        paint.drawImage(rectSphere,glb.images[4]);
        break;
    default:
        break;
    }



}

int mapSeg::getKind()const
{
    return this->kind;
}

void mapSeg::calSphere()
{
    this->rectSphere.setRect(pos.x(),pos.y(),
                             SegWidth,SegHeight);
}

void mapSeg::beAttacked(int attack)
{
    if(life>0)
        life-=attack;

    if(life<=0)
    {
        this->disappear=true;
        life=0;
    }


}

bool mapSeg::isPenetration1()const
{
    return penetration1;
}

bool mapSeg::isPenetration2()const
{
    return penetration2;
}
