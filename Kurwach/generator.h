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
    generator();
    void make(vector < vector < int > > &a);
};

#endif // GENERATOR_H
