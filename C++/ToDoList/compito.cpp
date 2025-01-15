#include "compito.h"
#include <cstring>
#include <iostream>
using namespace std;

ToDoList::ToDoList() {
    p0 = NULL;
}

bool ToDoList::aggiungi(char *descr, int prio) {
    if(prio <= 0 || descr == NULL || strlen(descr) > MAXCARATTERI) return false;

    Task* p;
    Task* q;
    for(q = p0; q != 0 && q->prio <= prio; q = q->pun) p = q;

    Task* r = new Task;
    r -> prio = prio;
    strcpy(r->desc, descr);
    r -> fatto = false;
    r -> pun = q;
    if(q == p0) p0 = r;
    else p->pun = r;
    return true;
}

ostream& operator<<(ostream& os, const ToDoList& tdl) {
    Task* p = tdl.p0;
    while(p != NULL)
    {
        if(p->fatto) os << "V ";
        else os << "  ";
        os << p->prio << " - " << p->desc << "\n";
        p = p->pun;
    }
    return os;
}

ToDoList::~ToDoList() {
    Task* p = p0;
    while(p0 != NULL)
    {
        p0 = p0->pun;
        delete p;
    }
}

ToDoList& ToDoList::operator+=(ToDoList &tdl) {
    if(&tdl == this) return *this;

    Task* p;
    for(p = tdl.p0; p != NULL; p=p->pun)
    {
        aggiungi(p->desc, p->prio);
    }
    return *this;
}

void ToDoList::fai(const char *descr) {
    if(descr == NULL || strlen(descr) > MAXCARATTERI) return;

    Task* p;
    for(p = p0; p != NULL && p->desc != descr; p=p->pun){
        if(strcmp(p->desc, descr) == 0 && !p->fatto)
        {
            p->fatto = true;
            return;
        }
    }
}

void ToDoList::cancella_fatti() {
    Task *p, *q, *r;
    for(p = p0; p != NULL; p = p->pun){
        if(p->fatto){
            if(p == p0){ // estrazione in testa
                r = p0->pun;
                delete p0;
                p0 = r;
            }
            else{ // estrazione in mezzo o in fondo
                r = p->pun;
                delete p;
                q->pun = r;
                p=q;
            }
        }
        q = p;
    }
}
