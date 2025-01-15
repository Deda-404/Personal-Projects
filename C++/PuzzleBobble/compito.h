//
// Created by alex on 07/02/2020.
//

#ifndef ESAMEPUZZLEBOBBLE2_COMPITO_H
#define ESAMEPUZZLEBOBBLE2_COMPITO_H
#include <iostream>
using namespace std;
#define COLONNE 6
#define RIGHE 10

class PuzzleBobble {
    char m[RIGHE][COLONNE];
    void CheckScoppio(int i, int j, char color);
public:
    PuzzleBobble();
    friend ostream& operator<<(ostream& os, const PuzzleBobble pb);
    PuzzleBobble& fire(int i, char color);
    operator int()const;
    PuzzleBobble& scroll();
    void compact();
};


#endif //ESAMEPUZZLEBOBBLE2_COMPITO_H
