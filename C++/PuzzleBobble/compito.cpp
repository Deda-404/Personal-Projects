//
// Created by alex on 07/02/2020.
//

#include "compito.h"

PuzzleBobble::PuzzleBobble() {
    for(int i = 0; i < RIGHE; i++)
    {
        for(int j = 0; j < COLONNE; j++) m[i][j] = ' ';
    }
}

ostream &operator<<(ostream &os, const PuzzleBobble pb) {
    os << '=';
    for(int i = 0; i < COLONNE; i++) os << "=";
    os << "=" << endl;

    for(int i = 0; i < RIGHE; i++)
    {
        os << "|";
        for(int j = 0; j < COLONNE; j++) os << pb.m[i][j];
        os << "|" << endl;
    }

    os << '=';
    for(int i = 0; i < COLONNE; i++) os << "=";
    os << "=" << endl;

    return os;
}

PuzzleBobble &PuzzleBobble::fire(int i, char color) {
    if(i < 0 || i >= COLONNE || (color != 'R' && color != 'G' && color != 'B' && color != 'Y') || m[RIGHE-1][i] != ' ') return *this;

    for(int j = RIGHE-1; j >= 0; j--)
    {
        if(m[j][i] == ' ')
        {
            if(j == 0 || m[j-1][i] != ' ')
            {
                m[j][i] = color;
                CheckScoppio(j, i, color);
                return *this;
            }
        }
    }
}

PuzzleBobble::operator int()const {
    int count_riga = 0;
    int count_final = 0;

    for(int i = 0; i < COLONNE; i++)
    {
        for(int j = 0; j < RIGHE; j++)
        {
            if(m[j][i] != ' ') count_riga++;
            else break;
        }
        if(count_riga > count_final) count_final = count_riga;
        count_riga = 0;
    }

    return count_final;
}

void PuzzleBobble::CheckScoppio(int i, int j, char color) {

    if(i - 2 > 0 && m[i-1][j] == color && m[i-2][j] == color) //check in alto
    {
        m[i-2][j] = ' ';
        m[i-1][j] = ' ';
        m[i][j] = ' ';
    }

    int count = 0;
    int last_j = 0;
    for(int j2 = 0; j2 < COLONNE; j2++) //check della riga
    {
        if(m[i][j2] == color)
        {
            count++;
            last_j = j2;
        }
        else count = 0;
    }

    if(count >= 3)
    {
        for(int j2 = last_j; j2 >= last_j-count+1; j2--) //scoppio
        {
            m[i][j2] = ' ';
        }
    }
}

PuzzleBobble& PuzzleBobble::scroll() {
    for(int j = 0; j < COLONNE; j++)
        if(m[RIGHE-1][j] != ' ')
            return *this;

    for(int i = RIGHE-1; i >= 1; i--){
        for(int j = 0; j < COLONNE; j++)
            m[i][j] = m[i-1][j];
    }

    for(int j = 0; j < COLONNE; j++)
        m[0][j] = '=';

    return *this;
}

void PuzzleBobble::compact() {
    for(int j = 0; j < COLONNE; j++)
    {
        int move_to_row = 0;
        for(int i = 0; i < RIGHE; i++)
        {
            if(m[i][j] != ' ')
            {
                m[move_to_row][j] = m[i][j];
                move_to_row++;
            }
        }
        for(int i = move_to_row; i < RIGHE; i++)
            m[i][j] = ' ';
    }
}