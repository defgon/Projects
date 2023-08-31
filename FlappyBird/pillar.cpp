#include "pillar.h"
#include "bird.h"
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <stdlib.h>


Pillar::Pillar(QGraphicsItem *parent):
    botPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),
    timer(new QTimer(this))
{
    setX(450);
    setY(rand() % 100);
    topPillar->setPos(getX(),getY()-210);
    botPillar->setPos(getX(),getY()+90+200);

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(15);

    addToGroup(topPillar);
    addToGroup(botPillar);
}

Pillar::~Pillar()
{
    delete topPillar;
    delete botPillar;
}

void Pillar::move(){
    setX(getX()-2);
    topPillar->setPos(getX(),getY()-205);
    botPillar->setPos(getX(),getY()+100+205);
    if(getX() < -50)
    {
        scene()->removeItem(this);
        deleteLater();
    }
}


bool Pillar::Collision()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(botPillar->collidingItems());
    for(QGraphicsItem *item : collidingItems)
    {
        Bird *bird = dynamic_cast<Bird*>(item);
        if(bird){
            deleteLater();
            return true;
        }
    }
    return false;
}


