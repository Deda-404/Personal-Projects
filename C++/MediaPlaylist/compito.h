#ifndef ESAMEMEDIAPLAYLIST_COMPITO_H
#define ESAMEMEDIAPLAYLIST_COMPITO_H

#include <iostream>
using namespace std;
#define TITLELEN 20

enum Tipo{AUDIO, VIDEO};

struct File{
    Tipo tipo;
    char* titolo;
    File* pun;
};

class MediaPlaylist {
    File* p0;
    void InserisciInFondo(const char *titolo, const Tipo tipo);
public:
    MediaPlaylist();
    MediaPlaylist(File* vett, int n);
    MediaPlaylist(const MediaPlaylist& mp2);
    ~MediaPlaylist();
    friend ostream& operator<<(ostream& os, const MediaPlaylist mpl);
    void inserisci(const char* titolo, const Tipo tipo);
    void elimina(const char* titolo, const Tipo tipo);
    int riproduci(const char* titolo, Tipo& tipo)const;
};


#endif //ESAMEMEDIAPLAYLIST_COMPITO_H
