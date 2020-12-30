#ifndef GENERATOR_H
#define GENERATOR_H

#include <QtWidgets>
#include <vector>
#include "all.h"
#include "mainwindow.h"

using namespace std;

class generator
{
public:
    ///
    /// \brief generator инициализация класса генератор
    ///
    generator();
    ///
    /// \brief make создание нового рандомного лабиринта
    /// \param a ссылка на массив в которое запишется наше новое поле
    ///
    void make(vector < vector < int > > &a);
};

#endif // GENERATOR_H
