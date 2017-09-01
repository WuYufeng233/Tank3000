#include "tank.h"
#include<QDebug>

int Tank::steps[num]={12,12,12,12};
int Tank::lifes[num]={10000,100,200,300};
int Tank::attacks[num]={100,100,100,100};

Tank::Tank()
{
    this->pos.setX(4*SegWidth);
    this->pos.setY(12*SegHeight);
    this->calSphere();
    //0玩家，1敌人
    this->group=0;
    step=12;
    //kind: 0玩家，1、2、3敌方坦克
    this->kind=0;
    isMove=false;
    dir=Up;
    disappear=false;
    isFire=false;
    life=lifes[kind];
    attack=attacks[kind];
    missileNum=0;
    scoreForPerPlayer=0;

}

Tank::Tank(int i,int j,Direction dir,int kind,int group)
{
    this->pos.setX(j*SegWidth);
    this->pos.setY(i*SegHeight);
    calSphere();
    this->group=group;
    this->dir=dir;
    this->kind=kind;
    step=steps[kind];
    disappear=false;
    isFire=false;
    life=lifes[kind];
    attack=attacks[kind];
    missileNum=0;
    scoreForPerPlayer=0;

}

void Tank::calSphere()
{
    this->rectSphere.setRect(pos.x(),pos.y(),SegWidth,SegHeight);
}

void Tank::display(QPainter &paint)
{

    for(int i=0;i<missiles.count();++i)
    {
        if(missiles.at(i)&&!missiles.at(i)->isDisappeared())
        {
            missiles.at(i)->display(paint);
        }
        else if(missiles.at(i))
        {
            delete missiles.at(i);//回收new新建的对象空间
            missiles.removeAt(i);//将对象指针从链表中删除
            i--;
        }
    }

    if(isDisappeared())
        return;


    switch(this->kind)
    {
    case 0:
       switch(dir)
        {
        case Up:
            paint.drawImage(rectSphere,glb.playerTank[0]);
            qDebug("draw tank");
            break;
        case Down:
            paint.drawImage(rectSphere,glb.playerTank[1]);
            break;
        case Left:
            paint.drawImage(rectSphere,glb.playerTank[2]);
            break;
        case Right:
            paint.drawImage(rectSphere,glb.playerTank[3]);
            break;
        }
        break;
    case 1:
        switch(dir)
         {
         case Up:
             paint.drawImage(rectSphere,glb.enemyTank1[0]);
             break;
         case Down:
             paint.drawImage(rectSphere,glb.enemyTank1[1]);
             break;
         case Left:
             paint.drawImage(rectSphere,glb.enemyTank1[2]);
             break;
         case Right:
             paint.drawImage(rectSphere,glb.enemyTank1[3]);
             break;
         }
         break;
    case 2:
        switch(dir)
          {
         case Up:
             paint.drawImage(rectSphere,glb.enemyTank2[0]);
             break;
         case Down:
             paint.drawImage(rectSphere,glb.enemyTank2[1]);
             break;
         case Left:
             paint.drawImage(rectSphere,glb.enemyTank2[2]);
             break;
         case Right:
            paint.drawImage(rectSphere,glb.enemyTank2[3]);
            break;
         }
        break;
    case 3:
        switch(dir)
         {
        case Up:
            paint.drawImage(rectSphere,glb.enemyTank3[0]);
            break;
        case Down:
            paint.drawImage(rectSphere,glb.enemyTank3[1]);
            break;
        case Left:
            paint.drawImage(rectSphere,glb.enemyTank3[2]);
            break;
        case Right:
            paint.drawImage(rectSphere,glb.enemyTank3[3]);
            break;
         }
        break;
    }
}

void Tank::move()
{
    for(int i=0;i<missiles.count();++i)
    {
        missiles.at(i)->move();
    }

    if(isDisappeared())
    {
        return;
    }

    if(isNextCollision())//下一个碰撞就返回
    {
        return;
    }


    if(isMove)
    {
        switch(dir)
        {
        case Up:
            pos.setY(pos.y()-step);
            break;
        case Down:
            pos.setY(pos.y()+step);
            break;
        case Left:
            pos.setX(pos.x()-step);
            break;
        case Right:
            pos.setX(pos.x()+step);
            break;
        }
        calSphere();
    }
}

void Tank::move1()
{
    if(isMove==true)
    {
        switch(dir)
        {
        case Up:
            pos.setY(pos.y()-step);
            break;
        case Down:
            pos.setY(pos.y()+step);
            break;
        case Left:
            pos.setX(pos.x()-step);
            break;
        case Right:
            pos.setX(pos.x()+step);
            break;
        }
        calSphere();
    }
}

void Tank::startMove()
{
    isMove=true;
}

void Tank::stopMove()
{
    isMove=false;
}

void Tank::setDirection(Direction dir)
{
    this->dir=dir;
}

void Tank::fire()
{
    if(isDisappeared())
        return;

    if(isFire&&missileNum==0)
    {
        Missile *newMissile=new Missile(*this);
        missiles.append(newMissile);
        missileNum=1;
    }
}

bool Tank::getIsFire()const
{
    return isFire;
}

void Tank::startFire()
{
    isFire=true;
}

void Tank::stopFire()
{
    isFire=false;
}

bool Tank::isNextCollision()
{
    Tank tmp=*this;
    tmp.move1();

    //是否与地图块碰撞
    for(int i=0;i<Row;++i)
    {
        for(int j=0;j<Col;++j)
        {
            if(glb.map->getSeg(i,j)
                    &&!glb.map->getSeg(i,j)->isPenetration1()
                    &&tmp.isCollision(*glb.map->getSeg(i,j)))
            {
                qDebug("-------boom------");
                return true;
            }
        }
    }

    //是否与地图边界碰撞
    if(tmp.rectSphere.left()<0
            ||tmp.rectSphere.right()>Width
            ||tmp.rectSphere.bottom()>Height
            ||tmp.rectSphere.top()<0)
    {

        return true;
    }

    //判断坦克间是否碰撞
    //首先判定玩家坦克是否与敌方坦克碰撞
    if(this->group==0)
    {
        for(int i=0;i<glb.enemytanks.count();++i)
        {
            if(glb.enemytanks.at(i)&&tmp.isCollision(*glb.enemytanks.at(i)))
            {
                return true;
            }
        }
    }


    //判定敌方坦克与玩家坦克以及敌方坦克之间是否碰撞
    if(this->group==1)
    {
        if(tmp.isCollision(*glb.player))
        {
            return true;
        }

        for(int i=0;i<glb.enemytanks.count();++i)
        {
            if(this->kind!=glb.enemytanks.at(i)->getKind())
            {
                if(tmp.isCollision(*glb.enemytanks.at(i)))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void Tank::setMissileNum()
{
    missileNum=0;
}

int Tank::getMissileNum()const
{
    return missileNum;
}

int Tank::getKind()const
{
    return this->kind;
}

void Tank::beAttacked(int attack)
{
    //中间变量用于后面加上得分
    int tempLife=lifes[this->kind];

    life-=attack;

    if(life<=0)
    {
        bool tmp=true;
        this->setDisappear(tmp);
        life=0;
    }

    if(this->getKind()>0&&this->isDisappeared())
    {
        glb.score+=tempLife;
        glb.player->setScoreForPerPlayer(tempLife);
    }
}


bool Tank::isCollision1(Boss &boss)const
{
    if(this->rectSphere.right()+5<boss.rectSphere.left()
            ||this->rectSphere.left()>boss.rectSphere.right()+5
            ||this->rectSphere.bottom()+5<boss.rectSphere.top()
            ||this->rectSphere.top()>boss.rectSphere.bottom()+5)
    {
        return false;
    }
    else
        return true;
}

void Tank::setDisappear(bool disappear)
{
    this->disappear=disappear;

    //使全局结构体中的enemyTanksDestroyed自增
    if(this->getKind()>0)
    {
        ++glb.enemyTanksDestroyed;
    }
}

void Tank::setScoreForPerPlayer(int i)
{
    this->scoreForPerPlayer+=i;
}

int Tank::getScoreForPerPlayer()const
{
    return scoreForPerPlayer;
}

void Tank::setAttack()
{
    this->attack=200;
}
