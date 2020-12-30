#include "mainwindow.h"
#include "all.h"
#include "generator.h"
#include <QtWidgets>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto Generate = new QPushButton(tr("Сгенерировать"));
    auto Start = new QPushButton(tr("Старт"));
    auto Save = new QPushButton(tr("Сохранить"));
    auto Load = new QPushButton(tr("Загрузить"));

    auto label1 = new QLabel(tr("Очки = 0"));
    auto label2 = new QLabel(tr("Время = 0.0"));
    auto label3 = new QLabel(tr("Жизни = 3"));

    auto view = new all;

    auto vl = new QVBoxLayout;
    vl->addWidget(Generate);
    vl->addWidget(Start);
    vl->addWidget(Save);
    vl->addWidget(Load);
    vl->addWidget(label1);
    vl->addWidget(label2);
    vl->addWidget(label3);
    vl->addStretch();

    auto hl = new QHBoxLayout;
    hl->addLayout(vl);
    hl->addWidget(view);

    auto w = new QWidget;
    w->setLayout(hl);
    setCentralWidget(w);



    auto timer = new QTimer(this);
    timer->setInterval(200);
    view->setFocus();
    connect(timer, &QTimer::timeout, [=] {
        view->activateWindow();
        QString a = label1->text(), b = label2->text(), c = label3->text();
        view->f(a, b, c);
        label1->setText(a);
        label2->setText(b);
        label3->setText(c);
    });
    timer->start();
    connect(Generate, &QPushButton::clicked, [=] {
        view->regen();
        view->setFocus();
    });
    connect(Start, &QPushButton::clicked, [=] {
        view->start();
        view->setFocus();
    });
    connect(Save, &QPushButton::clicked, [=] {
        timer->stop();
        view->save();
        view->setFocus();
        timer->start();
    });
    connect(Load, &QPushButton::clicked, [=] {
        timer->stop();
        view->load();
        view->setFocus();
        timer->start();
    });
}
