#include "bird.h"
#include "pillar.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>


Bird::Bird(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
    timer2(new QTimer(this)), timer1(new QTimer(this))
{
    setPixmap(QPixmap(":/images/bird.png"));
    setY(250);
    setPos(x,getY());
}



void Bird::hover()
{
    connect(timer2,&QTimer::timeout,[=](){
        if(counter == 0)
        {
            setPos(x,getY()+4);
            counter = 1;
        }else
        {
            setPos(x,getY()-4);
            counter = 0;
        }
    });
    timer2->start(150);
}

void Bird::stopHover(){
    timer2->stop();
}

void Bird::move()
{
    connect(timer1,&QTimer::timeout,[=](){
        setY(getY()+1.5);
        setPos(x,getY());
    });
    timer1->start(15);
}


bool Bird::GroundHit()
{
    if(getY() >= 450){
        timer1->stop();
        return true;
    }
    return false;
}

