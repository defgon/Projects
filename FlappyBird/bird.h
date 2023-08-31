#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Bird:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bird(QGraphicsItem * parent = 0);
    void setY(int y0){
        y = y0;
        if(GroundHit()){
            emit OnGround();
        }
    }
    int getX(){return x;}
    int getY(){return y;}
    bool GroundHit();
    void stopHover();
private:
    int x = 150;
    int y;
    int counter = 0;
    QTimer *timer1;
    QTimer *timer2;

signals:
    void OnGround();

public slots:
    void move();
    void hover();
};

#endif // BIRD_H
