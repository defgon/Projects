#include "window.h"
#include "bird.h"
#include "pillar.h"
#include "Score.h"




Window::Window(QWidget *parent)
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
    StartBackground();
    gameEnded = false;
    gameStarted = true;
    bird->stopHover();
    bird->move();
    addPillars();
}

void Window::RestartGame()
{
    gameEnded = false;
    score->restartScore();
    StartBackground();
    addBird();
    bird->move();
    addPillars();
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
    QImage backgroundImage("C:\\Users\\Mikovec-PC"
    "\\Desktop\\FJFI2\\4 semestr\\18GUI\\FlappyBird"
    "\\gameover.png");
    QBrush backgroundBrush(backgroundImage);
    setBackgroundBrush(backgroundBrush);
}

void Window::StartBackground(){
    QImage backgroundImage("C:\\Users\\Mikovec-PC"
    "\\Desktop\\FJFI2\\4 semestr\\18GUI\\FlappyBird"
    "\\background.png");
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
    pillarSpawn = new QTimer(this);
    connect(pillarSpawn,&QTimer::timeout,[=](){
        pillar = new Pillar();
        pillar->ColDestroy(gameEnded);
        connect(pillar,&Pillar::Collided,[=](){
            score->setTopScore();
            changeBackground();
            gameEnded = true;
            pillar->ColDestroy(gameEnded);
            clean();
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
}

void Window::cleanPillars(){
    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem *item, sceneItems){
        Pillar *pillar = dynamic_cast<Pillar *>(item);
        if(pillar){
            scene->removeItem(pillar);
            delete pillar;
        }
    }
}








