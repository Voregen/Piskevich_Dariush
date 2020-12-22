#include <QtWidgets>
#include "all.h"
#include "generator.h"
#include "mainwindow.h"
#include <QDebug>
#include <QString>
#include <QChar>
#include <QFile>
#include <QByteArray>
#include <random>

using namespace std;

void all::out(){
    for (int i(0); i < int(pole.size()); ++i){
        for (int j(0); j < int(pole[i].size()); ++j){
            auto k = pole[i][j];
            if (k < pixmaps.size())
                items[i][j]->setPixmap(pixmaps[k]);
        }
    }
    return;
}

vector < int > chX = {0, 0, -1, 1};
vector < int > chY = {1, -1, 0, 0};

bool all::good(int x, int y){
    if (x >= 0 && y >= 0 && x < 30 && y < 30){
        if (pole[x][y] == 0 || pole[x][y] == 3 || pole[x][y] == 4 || pole[x][y] == 5){
            return true;
        }
    }
    return false;
}

bool all::norm(int x, int y){
    if (pole[x][y] == 0 || pole[x][y] == 3 || pole[x][y] == 4){
        return true;
    }
    return false;
}

void all::die(){
    mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
    pause = true;
    --lives;
    while (true){
        int x = gen() % 30, y = gen() % 30;
        if (x == 10 && y == 15) continue;
        if (pole[x][y] == 4){
            pole[x][y] = 5;
            nowX[0] = x, nowY[0] = y;
            items[x][y]->setPixmap(QPixmap(":/images/pacman.png"));
            break;
        }
    }
    for (int i(1); i < 5; ++i){
        if (nowX[i] != 0){
            if (was.count({nowX[i], nowY[i]})){
                pole[nowX[i]][nowY[i]] = 4;
                items[nowX[i]][nowY[i]]->setPixmap(QPixmap(":/images/clear.png"));
            } else {
                pole[nowX[i]][nowY[i]] = 0;
                items[nowX[i]][nowY[i]]->setPixmap(QPixmap(":/images/point.png"));
            }
            nowX[i] = 0, nowY[i] = 0;
            dead[i] = 0;
        }
    }
    nowX[1] = 10, nowY[1] = 15;
    pole[nowX[1]][nowY[1]] = 6;
    items[nowX[1]][nowY[1]]->setPixmap(QPixmap(":/images/pink.png"));
}

void all::kill(int who){
    dead[who] = 50;
    nowX[who] = 0, nowY[who] = 0;
    score += 50;
}

void all::rotate(int who, int i){
    if (pause) return;
    int nX = nowX[who] + chX[i];
    int nY = nowY[who] + chY[i];
    if (good(nX, nY)){
        bool f = 0;
        if (pole[nowX[who]][nowY[who]] == 3){
            f = 1;
        }
        if (was.count({nowX[who], nowY[who]})){
            pole[nowX[who]][nowY[who]] = 4;
            items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/clear.png"));
        } else {
            pole[nowX[who]][nowY[who]] = 0;
            items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/point.png"));
        }
        if (f && who != 0){
            pole[nowX[who]][nowY[who]] = 3;
            items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/eat.png"));
        }
        nowX[who] += chX[i];
        nowY[who] += chY[i];
        if (who == 0){
            was.insert({nowX[who], nowY[who]});
            if (pole[nowX[who]][nowY[who]] == 0){
                ++score;
                del.erase({nowX[who], nowY[who]});
                ++eat;
                if (int(del.size()) == 0){
                    win = true;
                }
            }
            if (pole[nowX[who]][nowY[who]] == 3){
                bonus += 60;
            }
            if (pole[nowX[who]][nowY[who]] == 6){
                kill(1);
            }
            if (pole[nowX[who]][nowY[who]] == 7){
                kill(2);
            }
            if (pole[nowX[who]][nowY[who]] == 8){
                kill(3);
            }
            if (pole[nowX[who]][nowY[who]] == 9){
                kill(4);
            }
            items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/pacman.png"));
        } else {
            if (nowX[0] == nowX[who] && nowY[0] == nowY[who]){
                if (bonus > 0){
                    kill(who);
                } else {
                    die();
                }
                return;
            }
            if (who == 1){
                items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/pink.png"));
            }
            if (who == 2){
                items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/red.png"));
            }
            if (who == 3){
                items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/green.png"));
            }
            if (who == 4){
                items[nowX[who]][nowY[who]]->setPixmap(QPixmap(":/images/blue.png"));
            }
        }
        pole[nowX[who]][nowY[who]] = who + 5;
    }
}

void all::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_N){
        n();
    }
    if (event->key() == Qt::Key_M){
        m();
    }
    if (event->key() == Qt::Key_W){
        napravlenie = 1;
    }
    if (event->key() == Qt::Key_A){
        napravlenie = 2;
    }
    if (event->key() == Qt::Key_S){
        napravlenie = 0;
    }
    if (event->key() == Qt::Key_D){
        napravlenie = 3;
    }
    if (event->key() == Qt::Key_P){
        stop();
    }
}

void all::stratP(){
    int best = -1;
    int otv = 100000;
    if (bonus > 0){
        otv = -100000;
    }
    pair < int, int > H = {nowX[1], nowY[1]};
    for (int i(0); i < 4; ++i){
        int nX = H.first + chX[i], nY = H.second + chY[i];
        if (good(nX, nY)){
            if (bonus > 0){
                if (best == -1 || (nowX[0] - nX) * (nowX[0] - nX) + (nowY[0] - nY) * (nowY[0] - nY) > otv){
                    best = i;
                    otv = (nowX[0] - nX) * (nowX[0] - nX) + (nowY[0] - nY) * (nowY[0] - nY);
                }
            } else {
                if (best == -1 || (nowX[0] - nX) * (nowX[0] - nX) + (nowY[0] - nY) * (nowY[0] - nY) < otv){
                    best = i;
                    otv = (nowX[0] - nX) * (nowX[0] - nX) + (nowY[0] - nY) * (nowY[0] - nY);
                }
            }
        }
    }
    if (best != -1){
        rotate(1, best);
    }
}

void all::stratR(){
    int best = -1;
    int otv = 100000;
    if (bonus > 0){
        otv = -100000;
    }
    pair < int, int > h = {nowX[0] + 4 * chX[napravlenie], nowY[0] + 4 * chY[napravlenie]};
    pair < int, int > H = {nowX[2], nowY[2]};
    for (int i(0); i < 4; ++i){
        int nX = H.first + chX[i], nY = H.second + chY[i];
        if (good(nX, nY)){
            if (bonus > 0){
                if (best == -1 || (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY) > otv){
                    best = i;
                    otv = (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY);
                }
            } else {
                if (best == -1 || (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY) < otv){
                    best = i;
                    otv = (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY);
                }
            }
        }
    }
    if (best != -1){
        rotate(2, best);
    }
}

void all::stratG(){
    int best = -1;
    int otv = 100000;
    if (bonus > 0){
        otv = -100000;
    }
    pair < int, int > h = {nowX[1] + (nowX[1] - nowX[0]) * 2, nowY[1] + (nowY[1] - nowY[0]) * 2};
    pair < int, int > H = {nowX[3], nowY[3]};
    for (int i(0); i < 4; ++i){
        int nX = H.first + chX[i], nY = H.second + chY[i];
        if (good(nX, nY)){
            if (bonus > 0){
                if (best == -1 || (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY) > otv){
                    best = i;
                    otv = (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY);
                }
            } else {
                if (best == -1 || (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY) < otv){
                    best = i;
                    otv = (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY);
                }
            }
        }
    }
    if (best != -1){
        rotate(3, best);
    }
}

void all::stratB(){
    if ((nowX[0] - nowX[4]) * (nowX[0] - nowX[4]) + (nowY[0] - nowY[4]) * (nowY[0] - nowY[4]) > 40){
        int best = -1;
        int otv = 100000;
        if (bonus > 0){
            otv = -100000;
        }
        pair < int, int > h = {nowX[0], nowY[0]};
        pair < int, int > H = {nowX[4], nowY[4]};
        for (int i(0); i < 4; ++i){
            int nX = H.first + chX[i], nY = H.second + chY[i];
            if (good(nX, nY)){
                if (bonus > 0){
                    if (best == -1 || (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY) > otv){
                        best = i;
                        otv = (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY);
                    }
                } else {
                    if (best == -1 || (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY) < otv){
                        best = i;
                        otv = (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY);
                    }
                }
            }
        }
        if (best != -1){
            rotate(4, best);
        }
    } else {
        int best = -1;
        int otv = 100000;
        pair < int, int > h = {0, 0};
        pair < int, int > H = {nowX[4], nowY[4]};
        for (int i(0); i < 4; ++i){
            int nX = H.first + chX[i], nY = H.second + chY[i];
            if (good(nX, nY)){
                if (best == -1 || (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY) < otv){
                    best = i;
                    otv = (h.first - nX) * (h.first - nX) + (h.second - nY) * (h.second - nY);
                }
            }
        }
        if (best != -1){
            rotate(4, best);
        }
    }
}


void all::f(QString &a, QString &b, QString &c) {
    b = "Pause";
    if (win || int(del.size()) == 0){
        b = "Win";
        return;
    }
    if (pause || lives == 0) return;
    bonus = max(0, bonus - 1);
    for (int i(0); i < 5; ++i){
        dead[i] = max(0, dead[i] - 1);
    }
    rotate(0, napravlenie);
    b = "Not in Pause";
    int x = score;
    if (x == 0){
        a = "Score = 0";
    } else {
        a = "";
        while(x){
            a += QString(1, QChar((x % 10) + '0'));
            x /= 10;
        }
        reverse(a.begin(), a.end());
        a = "Score = " + a;
    }
    if (!pause && dead[1] == 0) {
        if (nowX[1] == 0 && nowY[1] == 0 && norm(10, 15)){
            pole[10][15] = 6;
            nowX[1] = 10, nowY[1] =15;
        }
        if (nowX[1] != 0){
            stratP();
        }
    }
    if (score > 10 && !pause && dead[2] == 0){
        if (nowX[2] == 0 && nowY[2] == 0 && norm(10, 15)){
            pole[10][15] = 7;
            nowX[2] = 10, nowY[2] =15;
        }
        if (nowX[2] != 0){
            stratR();
        }
    }
    if (score > 50 && !pause && dead[3] == 0){
        if (nowX[3] == 0 && nowY[3] == 0 && norm(10, 15)){
            pole[10][15] = 8;
            nowX[3] = 10, nowY[3] =15;
        }
        if (nowX[3] != 0){
            stratG();
        }
    }
    if (score > sum / 2 && !pause && dead[4] == 0){
        if (nowX[4] == 0 && nowY[4] == 0 && norm(10, 15)){
            pole[10][15] = 9;
            nowX[4] = 10, nowY[4] =15;
        }
        if (nowX[4] != 0){
            stratB();
        }
    }
    c = "Lives = ";
    if (lives == 1){
        c += "1";
    }
    if (lives == 2){
        c += "2";
    }
    if (lives == 3){
        c += "3";
    }
    if (lives == 0){
        c = "No lives :(";
        b = "Lose";
    }
}

void all::n() {
    sz = max(sz - 5, 10);
    updateScale();
}

void all::m() {
    sz  = min(sz + 5, 80);
    updateScale();
}

void all::updateScale() {
    const int pixmapSize = pixmaps.front().width();
    double s = sz;
    s /= pixmapSize;
    QTransform m(s, 0, 0, s, 0, 0);
    setTransform(m);
}

void all::regen() {
    score = 0;
    lives = 3;
    sum = 0;
    need = 0;
    eat = 0;
    pause = true;
    generator b;
    b.make(pole);
    was.clear();
    del.clear();
    for (int i(0); i < 5; ++i){
        nowX[i] = 0;
        nowY[i] = 0;
        dead[i] = 0;
    }
    for (int i(0); i < int(pole.size()); ++i){
        for (int j(0); j < int(pole[i].size()); ++j){
            if (pole[i][j] > 4){
                nowX[pole[i][j] - 5] = i, nowY[pole[i][j] - 5] = j;
            }
            if (pole[i][j] == 0){
                del.insert({i, j});
            }
        }
    }
    was.insert({nowX[0], nowY[0]});
    was.insert({10, 15});
    del.erase({nowX[0], nowY[0]});
    const int pixmapSize = pixmaps.front().width();
    scene->clear();
    for (int i(0); i < int(pole.size()); ++i){
        for (int j(0); j < int(pole[i].size()); ++j){
            items[i][j] = new QGraphicsPixmapItem;
            scene->addItem(items[i][j]);
            items[i][j]->setPos(i * pixmapSize, j * pixmapSize);
        }
    }

    out();
}

void all::start() {
    pause = false;
    win = false;
    tme = 1.0 * clock() / CLOCKS_PER_SEC;
}

void all::stop() {
    pause ^= 1;
}

void all::save() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Save Game"), "/", tr("Saves (*.txt)"));
    QFile fileOut(fileName);
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream writeStream(&fileOut);
    for (int i(0); i < int(pole.size()); ++i){
        QString s = "";
        for (int j(0); j < int(pole[i].size()); ++j){
            s += QString(1, char(pole[i][j] + '0'));
            s += QString(1, ' ');
        }
        s += QString(1, '\n');
        writeStream << s;
    }
    fileOut.close();
    return;
}

void all::load() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Game"), "/", tr("Saves (*.txt)"));
    QFile fileIn(fileName);
    fileIn.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream readStream(&fileIn);
    for (int i(0); i < int(pole.size()); ++i){
        QString s = "";
        for (int j(0); j < int(pole[i].size()); ++j){
            readStream >> s;
            QChar x = s[0];
            if (x == QChar('0')){
                pole[i][j] = 0;
            }
            if (x == QChar('1')){
                pole[i][j] = 1;
            }
            if (x == QChar('2')){
                pole[i][j] = 2;
            }
            if (x == QChar('3')){
                pole[i][j] = 3;
            }
            if (x == QChar('4')){
                pole[i][j] = 4;
            }
            if (x == QChar('5')){
                pole[i][j] = 5;
            }
            if (x == QChar('6')){
                pole[i][j] = 6;
            }
            if (x == QChar('7')){
                pole[i][j] = 7;
            }
            if (x == QChar('8')){
                pole[i][j] = 8;
            }
            if (x == QChar('9')){
                pole[i][j] = 9;
            }
        }
    }
    fileIn.close();
    score = 0;
    lives = 3;
    sum = 0;
    need = 0;
    eat = 0;
    pause = true;
    was.clear();
    del.clear();
    for (int i(0); i < 5; ++i){
        nowX[i] = 0;
        nowY[i] = 0;
        dead[i] = 0;
    }
    for (int i(0); i < int(pole.size()); ++i){
        for (int j(0); j < int(pole[i].size()); ++j){
            if (pole[i][j] > 4){
                nowX[pole[i][j] - 5] = i, nowY[pole[i][j] - 5] = j;
            }
            if (pole[i][j] == 0){
                del.insert({i, j});
            }
        }
    }
    was.insert({nowX[0], nowY[0]});
    was.insert({10, 15});
    del.erase({nowX[0], nowY[0]});
    const int pixmapSize = pixmaps.front().width();
    scene->clear();
    for (int i(0); i < int(pole.size()); ++i){
        for (int j(0); j < int(pole[i].size()); ++j){
            items[i][j] = new QGraphicsPixmapItem;
            scene->addItem(items[i][j]);
            items[i][j]->setPos(i * pixmapSize, j * pixmapSize);
        }
    }
    out();
    return;
}

all::all() {
    pixmaps = {
        QPixmap(":/images/point.png"),
        QPixmap(":/images/block.png"),
        QPixmap(":/images/gate.png"),
        QPixmap(":/images/eat.png"),
        QPixmap(":/images/clear.png"),
        QPixmap(":/images/pacman.png"),
        QPixmap(":/images/pink.png"),
        QPixmap(":/images/red.png"),
        QPixmap(":/images/green.png"),
        QPixmap(":/images/blue.png"),
    };
    scene= new QGraphicsScene();
    scene->setBackgroundBrush(QColor(230, 200, 167));
    resize(1200, 600);
    setScene(scene);
    updateScale();
    regen();
}


