#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsItem * parent = 0);
    void incScore();
    void setScore0();
    void setTopScore();
    void restartScore();
    int getScore();
    int getTopScore();
private:
    int score;
    int TopScore;
};


#endif // SCORE_H
