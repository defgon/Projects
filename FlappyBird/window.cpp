#include "window.h"
#include "bird.h"
#include "pillar.h"
#include "Score.h"




Window::Window(QWidget *parent)
    : pillarSpawn(new QTimer(this))
{
    // vytvoreni sceny
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,500,500);
    setScene(scene);
    // vytvoreni view
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    show();
    setFixedSize(500,500);
    StartBackground();
    addBird();
    addScore();
    SetUpGame();
}

void Window::StartGame()
{
    gameEnded = false;
    gameStarted = true;
    bird->stopHover();
    bird->move();
    addPillars();
}

void Window::RestartGame()
{
    gameStarted = true;
    gameEnded = false;
    score->restartScore();
    StartBackground();
    addBird();
    bird->move();
    pillarSpawn->start();
}

void Window::SetUpGame()
{
    bird->hover();
}


void Window::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_R && gameEnded){
        RestartGame();
    }
    if (event->key() == Qt::Key_Space)
    {
        bird->setY(bird->getY()-38);
        bird->setPos(bird->getX(),bird->getY());
    }
    if (event->key() == Qt::Key_Space && !gameStarted)
    {
        StartGame();
    }

}

void Window::changeBackground(){
    QImage backgroundImage(":/images/gameover.png");
    QBrush backgroundBrush(backgroundImage);
    setBackgroundBrush(backgroundBrush);
}

void Window::StartBackground(){
    QImage backgroundImage(":/images/background.png");
    QBrush backgroundBrush(backgroundImage);
    setBackgroundBrush(backgroundBrush);
}

void Window::addScore()
{
    score = new Score();
    scene->addItem(score);
}

void Window::addBird()
{
    bird = new Bird();
    scene->addItem(bird);
    bird->setFlag(QGraphicsItem::ItemIsFocusable);
    bird->setFocus();
    connect(bird,&Bird::OnGround,[=](){
        score->setTopScore();
        changeBackground();
        gameEnded = true;
        clean();
    });
}

void Window::addPillars()
{
    connect(pillarSpawn,&QTimer::timeout,[=](){
        pillar = new Pillar();
        connect(pillar,&Pillar::Collided,[=](){
            clean();
            score->setTopScore();
            changeBackground();
            gameEnded = true;
       });
       connect(pillar,&Pillar::AddScore,[=](){
            score->incScore();
       });
       scene->addItem(pillar);
    });
    pillarSpawn->start(2000);
}

void Window::clean()
{
    pillarSpawn->stop();
    scene->removeItem(bird);
    delete bird;
    cleanPillars();
}

void Window::cleanPillars(){
    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        Pillar *pillar = dynamic_cast<Pillar *>(item);
        if(pillar){
            scene->removeItem(pillar);
            pillar->deleteLater();
        }
    }
}








