#include <QtWidgets>
#include "mainwindow.h"
#include "generator.h"
#include "all.h"
#include <random>
#include <time.h>

using namespace std;

generator::generator()
{
}

const int n = 31;
const vector < int > X = {0, 0, 1, -1};
const vector < int > Y = {1, -1, 0, 0};

vector < vector < int > > a(n, vector < int > (n, 0)), us(n, vector < int > (n, 0));
vector < pair < int, int > > p;

bool good(int i, int j){
    if (i > 0 && j > 0 && i < n / 2 && j < n / 2){
        return true;
    } else {
        return false;
    }
}

inline void check(pair < int, int > lst){
    if (us[lst.first][lst.second] == 0 && a[lst.first][lst.second] == 0){
        us[lst.first][lst.second] = 1;
        for (int i(0); i < int(p.size()); ++i){
            if (lst == p[i]){
                swap(p[i], p.back());
                p.pop_back();
                break;
            }
        }
    }
    if (a[lst.first][lst.second] == 1){
        a[lst.first][lst.second] = 0;
        us[lst.first][lst.second] = 1;
    }
}

void generator::make(vector < vector < int > > &b){
    mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            a[i][j] = 1;
        }
    }
    vector < int > heh;
    for (int i = 0; i * 2 + 1 < n - 1; ++i){
        if (i * 2 + 1 != 10 && i * 2 + 1 != 11 && i * 2 + 1 != 12) heh.push_back(i * 2 + 1);
        for (int j = 0; j * 2 + 1 < (n - 1) / 2; ++j){
            a[i * 2 + 1][j * 2 + 1] = 0;
            us[i * 2 + 1][j * 2 + 1] = 0;
            p.push_back({i * 2 + 1, j * 2 + 1});
        }
    }

    pair < int, int > lst = p[0];
    us[p[0].first][p[0].second] = 1;
    swap(p[0], p.back());
    p.pop_back();
    while (p.size() > 0){
        int z = gen() % int(p.size());
        pair < int, int > fin = p[z];
        if (gen() % 2){
            while (lst.second != fin.second){
                if (lst.second < fin.second){
                    ++lst.second;
                } else {
                    --lst.second;
                }
                check(lst);
            }
            while (lst.first != fin.first){
                if (lst.first < fin.first){
                    ++lst.first;
                } else {
                    --lst.first;
                }
                check(lst);
            }
        } else {
            while (lst.first != fin.first){
                if (lst.first < fin.first){
                    ++lst.first;
                } else {
                    --lst.first;
                }
                check(lst);
            }
            while (lst.second != fin.second){
                if (lst.second < fin.second){
                    ++lst.second;
                } else {
                    --lst.second;
                }
                check(lst);
            }
        }
        lst = fin;
    }
    for (int i = 0; i < n - 1; ++i){
        for (int j = 0; j < (n - 1) / 2; ++j){
            a[i][n - j - 1] = a[i][j];
        }
    }
    a[9][14] = 0, a[9][15] = 0, a[9][16] = 0;
    a[11][15] = 0;
    a[10][15] = 2;
    int k = gen() % (heh.size() - 3) + 3;
    shuffle(heh.begin(), heh.end(), gen);
    for (int i(0); i < k; ++i){
        a[heh[i]][14] = 0;
        a[heh[i]][15] = 0;
        a[heh[i]][16] = 0;
    }
    for (int i(1); i < n - 1; ++i){
        for (int j(1); j < n - 1; ++j){
            if (a[i][j] == 0){
                int k = 0;
                if (a[i - 1][j] == 1){
                    ++k;
                }
                if (a[i + 1][j] == 1){
                    ++k;
                }
                if (a[i][j + 1] == 1){
                    ++k;
                }
                if (a[i][j - 1] == 1){
                    ++k;
                }
                if (k == 3){
                    a[i][j] = 3;
                }
            }
        }
    }
    //a[10][15] = 2;
    a[10][15] = 6;
    a[11][15] = 2;
    //a[11][15] = 7;
    //a[12][15] = 8;
    //a[13][15] = 9;
    //a[11][14] = 1, a[11][16] = 1;
    //a[12][14] = 1, a[12][16] = 1;
    //a[13][14] = 1, a[13][16] = 1;
    while (true){
        int x = gen() % 30, y = gen() % 30;
        if (a[x][y] == 0){
            a[x][y] = 5;
            break;
        }
    }
    b = a;
}
