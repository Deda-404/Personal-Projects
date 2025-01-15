#ifndef ESAMEPRONTOSOCCORSO2_COMPITO_H
#define ESAMEPRONTOSOCCORSO2_COMPITO_H
#include <iostream>
using namespace std;

const int TITLEN = 20;

enum Tipo {AUDIO, VIDEO};

struct file{
    char titolo[TITLEN+1];
    Tipo tipo;
    file* next;
};

struct item{
    Tipo tipo;
    char titolo[TITLEN+1];
};

class MediaPlaylist {
    file* p0;
public:
    //PRIMA PARTE
    MediaPlaylist();
    void inserisci(const char*, Tipo);
    void elimina(const char*, Tipo);
    friend ostream& operator<<(ostream&, const MediaPlaylist&);
    //SECONDA PARTE
    int riproduci(const char*, Tipo&)const;
    MediaPlaylist(item*, int);
    MediaPlaylist(const MediaPlaylist&);
    ~MediaPlaylist();
};


#endif //ESAMEPRONTOSOCCORSO2_COMPITO_H
