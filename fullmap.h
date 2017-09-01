#ifndef FULLMAP_H
#define FULLMAP_H

#include"mapseg.h"
#include"data.h"
#include<QRect>
#include<QPainter>

class fullMap
{
public:
    fullMap();
    ~fullMap();

    void loadMap();

    mapSeg *getSeg(int,int)const;//返回一根指针：mapSeg类型的
    virtual void display(QPainter &paint);

private:
    mapSeg *segs[Row][Col];//指针数组，每一个元素都是一枚指针，指向类型为mapSeg的变量
    int stages;

};

#endif // FULLMAP_H
