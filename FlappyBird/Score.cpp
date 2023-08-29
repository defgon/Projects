#include "Score.h"
#include <QFont>
#include <QGraphicsTextItem>
#include <QTextOption>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    // nastaveni score = 0
    score = 0;
    TopScore = 0;

    // vykresli text
    setPlainText(QString("Score: ") + QString::number(getScore()));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",20));
    setPos(0,0);

}

void Score::restartScore(){
    score = 0;
    setPlainText(QString("Score: ") + QString::number(getScore()));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",20));
    setPos(0,0);
}

void Score::incScore(){
    score++;
    setPlainText(QString("Score: ") + QString::number(getScore()));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",20));
}

void Score::setScore0(){
    score = 0;
}

void Score::setTopScore(){
    if(score > TopScore){
        TopScore = score;
    }
    QTextOption(Qt::AlignCenter);
    setPlainText(QString("Top Score: ") +
                 QString::number(getTopScore()) +
                 QString("\nYour Score: ") +
                 QString::number(getScore()));
    setDefaultTextColor(Qt::red);
    QFont font("times", 28);
    font.setBold(true);
    setFont(font);
    setPos(140,320);
}

int Score::getScore(){
    return score;
}

int Score::getTopScore(){
    return TopScore;
}
