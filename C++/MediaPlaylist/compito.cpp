//
// Created by alex on 05/02/2020.
//

#include "compito.h"
#include <cstring>

const char* msg[2] = {"Audio", "Video"};

MediaPlaylist::MediaPlaylist() {
    p0 = NULL;
}

ostream &operator<<(ostream &os, const MediaPlaylist mpl) {
    if(mpl.p0 == 0) return os << "[-]";

    File* p = mpl.p0;
    int i = 1;
    while(p != NULL)
    {
        os << "[" << i++ << "]" << "<" << p->titolo << ", " << msg[p->tipo] << ">" << endl;
        p=p->pun;
    }
    return os;
}

void MediaPlaylist::inserisci(const char *titolo, const Tipo tipo) {
    if(titolo == NULL || (tipo != AUDIO && tipo != VIDEO)) return;

        File *q = p0;

        while(q != NULL)
        {
            if (strcmp(q->titolo, titolo) == 0 && q->tipo == tipo) return;
            q=q->pun;
        }

        q = new File;

        if(strlen(titolo) > TITLELEN) {
            q->titolo = new char[TITLELEN+1];
            strncpy(q->titolo, titolo, TITLELEN);
            q->titolo[TITLELEN] = '\0';
        }
        else {
            q->titolo = new char[strlen(titolo)+1];
            strcpy(q->titolo, titolo);
            q->titolo[strlen(titolo)] = '\0';
        }

        q->tipo = tipo;
        q->pun = p0;
        p0 = q;
}

void MediaPlaylist::elimina(const char *titolo, const Tipo tipo) {
    File* p;
    File* q;

    for(q = p0; q != NULL; q=q->pun)
    {
        if (strcmp(q->titolo, titolo) == 0 && q->tipo == tipo)
        {
            if(q == p0)
            {
                p0 = q->pun;
            }
            else p->pun = q->pun;

            delete[] q->titolo;
            delete q;
            return;
        }
        p = q;
    }
}

MediaPlaylist::MediaPlaylist(File* vett, int n) {
    p0 = NULL;
    for(int i = n-1; i >= 0; i--)
    {
        inserisci(vett[i].titolo, vett[i].tipo);
    }
}


MediaPlaylist::MediaPlaylist(const MediaPlaylist& mp2) {
    p0 = NULL;
    File* p = mp2.p0;

    while(p != NULL)
    {
        InserisciInFondo(p->titolo, p->tipo);
        p=p->pun;
    }
}

void MediaPlaylist::InserisciInFondo(const char *titolo, const Tipo tipo) {
    if(titolo == NULL || (tipo != AUDIO && tipo != VIDEO)) return;

    File *p;
    File *q = p0;

    while(q != NULL)
    {
        if (strcmp(q->titolo, titolo) == 0 && q->tipo == tipo) return;
        p = q;
        q=q->pun;
    }

    q = new File;

    //si può fare questo?
    if(strlen(titolo) > TITLELEN) {
        q->titolo = new char[TITLELEN+1];
        strncpy(q->titolo, titolo, TITLELEN);
        q->titolo[TITLELEN] = '\0'; //è giusto?
    }
    else {
        q->titolo = new char[strlen(titolo)+1];
        strcpy(q->titolo, titolo);
        q->titolo[strlen(titolo)] = '\0';
    }

    q->tipo = tipo;
    q->pun = 0;
    if(p0 == 0) p0 = q;
    else p->pun = q;
}

int MediaPlaylist::riproduci(const char *titolo, Tipo &tipo) const {
    File* p = p0;
    while(p != NULL)
    {
        if (strcmp(p->titolo, titolo) == 0)
        {
            tipo = p->tipo;
            return 1;
        }
        p = p->pun;
    }
    return 0;
}

MediaPlaylist::~MediaPlaylist() {
    File* p;

    while(p0 != 0)
    {
        p = p0;
        p0 = p0->pun;
        delete[] p->titolo;
        delete p;
    }
}
