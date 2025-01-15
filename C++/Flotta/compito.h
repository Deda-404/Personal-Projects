//
// Created by alex on 02/06/2020.
//

#ifndef ESAMEFLOTTA_COMPITO_H
#define ESAMEFLOTTA_COMPITO_H
#include <iostream>
using namespace std;


class Flotta {
    int* file;
    int count;
public:
    Flotta(int n);
    void forma_fila(int, int);
    friend ostream& operator<<(ostream&, const Flotta&);
    operator int()const;
    ~Flotta();
    Flotta(const Flotta&);
    friend Flotta operator+(const Flotta&, const Flotta&);
    Flotta& operator-=(const Flotta&);
    Flotta& operator+=(const int[]);
};


#endif //ESAMEFLOTTA_COMPITO_H
