#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <QKeyEvent>

class Bird;
class Pillar;
class Score;

class Window : QGraphicsView
{
public:
    Window(QWidget *parent = nullptr);
    QGraphicsScene * scene;
    Bird * bird;
    Pillar * pillar;
    Score *score;
    QTimer *pillarSpawn;
    QTimer *time;
    QList<Pillar*> spawnedPillars;
    bool gameStarted = false;
    bool gameEnded = false;
    QString projectPath = QCoreApplication::applicationDirPath();
    void keyPressEvent(QKeyEvent * event);
    void StartBackground();
    void changeBackground();
    void StartGame();
    void RestartGame();
    void SetUpGame();
    void CheckGame();
    void addBird();
    void addScore();
    void addPillars();
    void cleanPillars();
    void clean();
};
#endif // WINDOW_H
