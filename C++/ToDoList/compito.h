#ifndef ESAMETODOLIST_COMPITO_H
#define ESAMETODOLIST_COMPITO_H


#include <iostream>

using namespace std;

const int MAXCARATTERI = 40;

struct Task {
    char desc[MAXCARATTERI+1];
    int prio;
    bool fatto;
    Task* pun;
};

class ToDoList {
    Task* p0;
public:
    ToDoList();
    ~ToDoList();
    bool aggiungi(char* descr, int prio);
    friend ostream& operator<<(ostream&, const ToDoList&);
    ToDoList& operator+=(ToDoList& tdl);
    void fai(const char* descr);
    void cancella_fatti();
};



#endif //ESAMETODOLIST_COMPITO_H
