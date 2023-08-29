#include "pillar.h"
#include "bird.h"
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <stdlib.h>


Pillar::Pillar(QGraphicsItem *parent):
    botPillar(new QGraphicsPixmapItem(QPixmap("C:\\Users\\Mikovec-PC\\Desktop"
                                              "\\FJFI2\\4 semestr\\18GUI\\FlappyBird"
                                              "\\pillar.png"))),
    topPillar(new QGraphicsPixmapItem(QPixmap("C:\\Users\\Mikovec-PC\\Desktop"
                                              "\\FJFI2\\4 semestr\\18GUI\\FlappyBird"
                                              "\\pillar.png")))
{
    setX(450);
    setY(rand() % 100);
    topPillar->setPos(getX(),getY()-210);
    botPillar->setPos(getX(),getY()+90+200);


    timer = new QTimer(this);
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
        delete this;
    }
}

void Pillar::ColDestroy(bool s){
    if(s){
        scene()->removeItem(this);
        delete this;
        qDebug() << "Destroy";
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
            emit Collided();
            qDebug() << "Destroy";
            scene()->removeItem(this);
            delete this;
            return true;
        }
    }
    return false;
}


