//
// Created by alex on 06/02/2020.
//

#include "compito.h"

Snake::Snake(int r1, int c1) {
    if(r1 < 4) r = 4;
    if(c1 < 4) c = 4;
    r = r1;
    c = c1;

    g = new int*[r];
    for(int i = 0; i < r; i++)
    {
        g[i] = new int[c];
    }

    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++) g[i][j] = -1; //-1 = vuoto
    }

    head = new bodyPiece;

    bodyPiece* p;
    p0 = 0;
    for(int i = 0; i < 4; i++)
    {
        p = new bodyPiece;
        p->c.x = r-4+i;
        p->c.y = 0;
        p->pun = p0;
        p->i = i+1;
        g[p->c.x][p->c.y] = p->i;
        p0 = p;
        if(i == 0) head = p;
    }
}

ostream &operator<<(ostream &os, const Snake &s) {
    os << "|";
    for(int i = 0; i < s.c; i++) os << "-";
    os << "|" << endl;

    for(int i = 0; i < s.r; i++)
    {
        os << "|";
        for(int j = 0; j < s.c; j++)
        {
            switch(s.g[i][j]){
                case -1: os << " "; break;
                case 0: os << "*"; break;
                default: os << s.g[i][j]; break;
            }
        }
        os << "|" << endl;
    }

    os << "|";
    for(int i = 0; i < s.c; i++) os << "-";
    os << "|" << endl;

    return os;
}

void Snake::SpostaTail() {
    bodyPiece* p = p0;
    g[p0->c.x][p0->c.y] = -1;
    p0=p0->pun;
    delete p;
}


Snake &Snake::muovi(const char dir) {
    if(dir != 'n' && dir != 'o' && dir != 's' && dir != 'e') return *this; //check dell'input

    coord new_coord; //salvo le coordinate della testa dello snake
    new_coord.x = head->c.x;
    new_coord.y = head->c.y;

    switch(dir) //in base alla direzione modifico la variabile
    {
        case 'n': new_coord.x--; break;
        case 'o': new_coord.y--; break;
        case 's': new_coord.x++; break;
        case 'e': new_coord.y++; break;
    }

    if(!CanMove(new_coord.x, new_coord.y)) return *this; //infine checko se posso muovere in tale direzione

    if(g[new_coord.x][new_coord.y] != 0 || len == MAXLEN) SpostaTail(); //se non mangi una mela o lem == maxlen
    else len++; //se mangi una mela allora non sposti la tail (aggiungi una testa = aumenti la lunghezza)

    //da qui in poi è algoritmo per aggingere una testa
    bodyPiece* p;
    bodyPiece* q;

    for(q = p0; q != NULL; q=q->pun)
    {
        q->i++;
        g[q->c.x][q->c.y] = q->i;
        p = q;
    }

    q = new bodyPiece;
    q->i = 1;
    q->pun = 0;
    q->c.x = new_coord.x;
    q->c.y = new_coord.y;
    head = q;
    p->pun = q;
    g[head->c.x][head->c.y] = 1;

    return *this;
}

bool Snake::CanMove(int x, int y) {
    return x != -1 && y != -1 && x != r && y != c && (g[x][y] == 0 || g[x][y] == -1);
}

Snake &Snake::mela(int i, int j) {
    if(i < 0 || j < 0 || i >= r || j >= c || g[i][j] != -1) return *this;

    g[i][j] = 0;
    return *this;
}

void Snake::inverti() {
    bodyPiece* q;
    bodyPiece* r;
    bodyPiece* new_p0 = 0;

    for(q = p0; q != NULL; q=q->pun)
    {
        r = new bodyPiece;
        r->c.x = q->c.x;
        r->c.y = q->c.y;
        r->pun = new_p0;
        r->i = len+1 - q->i;
        g[r->c.x][r->c.y] = r->i;
        new_p0 = r;
        if(q->i == 1) head = r;
    }

    q = p0;
    while(p0 != NULL)
    {
        p0 = p0->pun;
        delete q;
    }

    p0 = new_p0;
}

Snake& Snake::operator--() {
    if(len == 4) return *this;

    SpostaTail();
    len--;
    return *this;
}

Snake::~Snake() {
    for(int i = 0; i < r; i++)
    {
        delete[] g[i];
    }
    delete[] g;

    bodyPiece* p;
    while(p0 != NULL)
    {
        p = p0;
        p0=p0->pun;
        delete p;
    }
}