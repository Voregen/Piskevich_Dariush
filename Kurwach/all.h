#ifndef ALL_H
#define ALL_H


#include "mainwindow.h"
#include "generator.h"
#include <set>

using namespace std;


class all : public QGraphicsView
{

public:
    ///
    /// \brief n сделать размер клеток меньше
    ///
	void n();
    ///
    /// \brief f функция которая вызывается каждые 200мс для обновления поля и совершения действий
    /// \param a параметр для количества очков
    /// \param b параметр для состояния игры, паузы, победы или поражения
    /// \param c параметр для количества жизней
    ///
    void f(QString &a, QString &b, QString &c);
    ///
    /// \brief m функция для увеличения размера клеток
    ///
	void m();
    ///
    /// \brief updateScale функция для обновления картинки
    ///
	void updateScale();
    ///
    /// \brief regen функция для новой генерации поля
    ///
    void regen();
    ///
    /// \brief start функция для старта игры
    ///
    void start();
    ///
    /// \brief stop функция для снятия или начала паузы
    ///
    void stop();
    ///
    /// \brief good фукнция для проверки хорошая или плохая позиция (входит ли она в ограничения, или не стоит ли на плохой клетке -- клетке которую нельзя посетить)
    /// \param x Х позиция клетки
    /// \param y Y позиция клетки
    /// \return возвращает хорошая ли клетка
    ///
    bool good(int x, int y);
    ///
    /// \brief rotate функция для перемещения пакмена или ИИ
    /// \param who кто именно перемещается, 0 - значит пакмен, 1 - 4 значит ИИ
    /// \param i в какую сторону перемещается, 0 -- вверх, 1 -- вниз, 2 -- вправо, 3 -- влево
    ///
    void rotate(int who, int i);
    ///
    /// \brief all инициализация класса
    ///
    explicit all();
    ///
    /// \brief save функция для сохранения поля
    ///
    void save();
    ///
    /// \brief load функция для загрузки поля
    ///
    void load();
    ///
    /// \brief out функция для вывода всего поля на экран
    ///
    void out();
    ///
    /// \brief stratR выбор куда пойти красному призраку
    ///
    void stratR();
    ///
    /// \brief stratB выбор куда пойти синему призраку
    ///
    void stratB();
    ///
    /// \brief stratG выбор куда пойти зеленому призраку
    ///
    void stratG();
    ///
    /// \brief stratP выбор куда пойти фиолетовому призраку
    ///
    void stratP();
    ///
    /// \brief die функция которая переписывает все, если пакмен зашел на одну клетку с ИИ при неактивном бонусе
    ///
    void die();
    ///
    /// \brief ok фукнция для проверки хорошая или плохая позиция (входит ли она в ограничения, или не стоит ли на плохой клетке -- клетке которую нельзя посетить)
    /// \param x Х позиция клетки
    /// \param y Y позиция клетки
    /// \return возвращает хорошая ли клетка
    ///
    bool ok(int x, int y);
    ///
    /// \brief kill функция если вдруг пакмен с активным бонусом становится в клетку с призраком и убивает его
    /// \param who номер призрака который именно умер
    ///
    void kill(int who);
    ///
    /// \brief norm фукнция для проверки хорошая или плохая позиция (входит ли она в ограничения, или не стоит ли на плохой клетке -- клетке которую нельзя посетить)
    /// \param x Х позиция клетки
    /// \param y Y позиция клетки
    /// \return возвращает хорошая ли клетка
    ///
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
    int napravlenie[5];
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
    QString way = "@";
    QGraphicsScene *scene;
    vector < vector < int > > pole;
    vector < vector < vector < int > > > saved;
};

#endif // ALL_H
