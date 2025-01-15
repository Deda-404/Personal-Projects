#ifndef ESAMESNAKE_COMPITO_H
#define ESAMESNAKE_COMPITO_H
#define MAXLEN 9
#include <iostream>
using namespace std;


struct coord{
    int x;
    int y;
};

struct bodyPiece{
    int i;
    coord c;
    bodyPiece* pun;
};

class Snake {
    int** g;
    bodyPiece* p0; //questa è la tail

    int r;
    int c;

    bodyPiece* head;

    int len = 4;

    void SpostaTail();
    bool CanMove(int x, int y);
public:
    Snake(int r, int c);
    ~Snake();
    friend ostream&operator<<(ostream& os, const Snake& s);
    Snake& muovi(const char dir);
    Snake& mela(int i, int j);
    void inverti();
    Snake& operator--();
};


#endif //ESAMESNAKE_COMPITO_H
