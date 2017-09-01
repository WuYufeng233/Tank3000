#ifndef TANK_H
#define TANK_H

#include"base.h"
#include"data.h"
#include"fullmap.h"
#include"missile.h"

//坦克种类数
const int num=4;

class Tank: public Base
{
protected:
    static int steps[num];
    static int lifes[num];
    static int attacks[num];

    int group;//坦克所在组，同一组不能相互伤害


    virtual void calSphere();

public:
    friend class Missile;
    QList<Missile*>missiles;

    Tank();//玩家坦克
    Tank(int,int,Direction=Up,int=0,int=1);//敌人坦克

    virtual void display(QPainter &paint);
    virtual void move();
    void move1();

    void startMove();//设置移动状态为开
    void stopMove();//设置移动状态为关
    void setDirection(Direction dir);

    //开火
    void fire();
    bool getIsFire()const;
    void startFire();
    void stopFire();

    //坦克下一步是否与地图块碰撞
    bool isNextCollision();

    void setMissileNum();
    int getMissileNum()const;

    int getKind()const;
    //被攻击扣血
    virtual void beAttacked(int attack);

    //判断坦克是否与boss碰撞
    bool isCollision1(Boss &boss)const;

    //设置消失状态，与大基类的同名函数不同，这里添加了使全局结构体中的
    //enemyTanksDestroyed自增的功能
    void setDisappear(bool disappear);

    void setScoreForPerPlayer(int);
    int getScoreForPerPlayer()const;

    //设置玩家攻击力
    void setAttack();

private:
    int kind;
    bool isMove;
    bool isFire;
    int missileNum;
    int scoreForPerPlayer;


};

#endif // TANK_H
