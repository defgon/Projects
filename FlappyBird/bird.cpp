#include "bird.h"
#include "pillar.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>


Bird::Bird(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap("C:\\Users\\Mikovec-PC"
                      "\\Desktop\\FJFI2\\4 semestr"
                      "\\18GUI\\FlappyBird\\bird.png"));
    setY(250);
    setPos(x,getY());
}


void Bird::hover()
{
    timer2 = new QTimer(this);
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
    timer1 = new QTimer(this);
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

