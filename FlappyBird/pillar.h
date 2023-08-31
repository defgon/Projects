#ifndef PILLAR_H
#define PILLAR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsItemGroup>
#include <QTimer>

class Pillar:public QObject,public QGraphicsItemGroup{
    Q_OBJECT
public:
    Pillar(QGraphicsItem *parent = 0);
    ~Pillar();
    void setX(int x0){
        x = x0;
        if(Collision()){
            emit Collided();
        }
        if(x < 150 && !Collision() && !added){
            added = true;
            emit AddScore();
        }
    }
    void setY(int y0){y = y0;}
    int getY(){return y;}
    int getX(){return x;}
    bool Collision();
    void setStop(){timer->stop();}
signals:
    void Collided();
    void AddScore();
private:
    int x,y;
    bool added = false;
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *botPillar;
    QTimer *timer;
public slots:
    void move();
};

#endif // PILLAR_H
