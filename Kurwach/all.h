#ifndef ALL_H
#define ALL_H


#include "mainwindow.h"
#include "generator.h"
#include <set>

using namespace std;


class all : public QGraphicsView
{

public:
	void n();
    void f(QString &a, QString &b, QString &c);
	void m();
	void updateScale();
    void regen();
    void start();
    void stop();
    bool good(int x, int y);
    void rotate(int who, int i);
    explicit all();
    void save();
    void load();
    void out();
    void stratR();
    void stratB();
    void stratG();
    void stratP();
    void die();
    void kill(int who);
    bool norm(int x, int y);

    QVector<QPixmap> pixmaps;
    QGraphicsPixmapItem *items[50][50];
    set < pair < int, int > > was;
    int h = 31;
    int lives = 3;
    int sum = 0;
    int eat = 0;
    int need = 0;
    int w = 31;
    int sz = 20;
    int score = 0;
    int napravlenie = 0;
    int bonus = 12;
    bool pause = true;
    set < pair < int, int > > del;
    int nowX[5];
    int nowY[5];
    int dead[5];
    long double tme = 0.0;
    long double ril = 0.0;
    bool win = false;
    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene *scene;
    vector < vector < int > > pole;
    vector < vector < vector < int > > > saved;
};

#endif // ALL_H
