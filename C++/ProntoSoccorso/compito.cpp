//
// Created by alex on 30/06/2020.
//

#include "compito.h"
#include <cstring>

const char* msg[] = {"Audio", "Video"};

MediaPlaylist::MediaPlaylist() {
    p0 = NULL; //inizializzo lista vuota
}

void MediaPlaylist::inserisci(const char* titolo, Tipo tipo) {
    if(titolo == NULL) return; //check input

    //check se la stringa è più lunga della massima dimensione
    int i;
    char str[TITLEN+1]; //creo variabile d'appoggio
    for (i = 0; (i < TITLEN) && (i < strlen(titolo)); i++) //scandisco fino a titlen o fino alla lunghezza di titolo
        str[i] = titolo[i]; //copio il carattere
    str[i] = '\0'; //carattere di fine stringa

    //check di esistenza
    file* f = p0; //variabile di appoggio
    while(f != NULL) //standisco l'intera playlist
    {
        if((strcmp(f->titolo, str) == 0 && f->tipo == tipo)) return; //se trovo il titolo e il tipo uguali
        f = f->next; //vado al prossimo
    }

    //alloco il file
    f = new file;
    f->tipo = tipo;
    strcpy(f->titolo, str); //tronco la lunghezza a titlen
    f->next = p0; //punta a testa
    p0 = f; //la testa punta a questo
}

ostream& operator<<(ostream& os, const MediaPlaylist& mpl) {
    file* f = mpl.p0; //prendo la testa della playlist

    if(f == NULL) return os << "[-]"; //se è vuota stampo il vuoto

    //altrimenti ciclo l'intera playlist
    int i = 1;
    while(f != NULL)
    {
        os << "[" << i++ << "]<" << f->titolo << ", " << msg[f->tipo] << ">\n"; //stampo il file
        f = f->next; //stampo la prossima
    }
    return os;
}

void MediaPlaylist::elimina(const char* titolo, Tipo tipo) {
    if(titolo == NULL || p0 == NULL) return; //check input

    //ciclo l'intera playlist
    file* p;
    file* q;
    for(q = p0; q != NULL; q = q->next) {
        if(strcmp(q->titolo, titolo) == 0 && q->tipo == tipo) break; //se trovo il file esco dal ciclo
        p = q; //vado al prossimo
    }

    if(q != NULL) //se ho trovato l'elemento
    {
        if(q == p0) p0 = q->next; //se è il primo della playlist, questa puntera al file dopo
        else p->next = q->next; //altrimenti il file prima di questo punta a quello dopo

        delete q; //dealloco il file
    }
}

MediaPlaylist::~MediaPlaylist() {
    file* f = p0; //prendo la testa
    while(p0 != NULL) //ciclo l'intera lista
    {
        p0 = p0->next; //vado al prossimo
        delete f; //dealloco il file
    }
}

int MediaPlaylist::riproduci(const char* titolo, Tipo& t)const {
    if(titolo == NULL) return 0; //check input

    //scandisco l'intera lista
    file* f = p0;
    while(f != NULL)
    {
        if(strcmp(f->titolo, titolo) == 0) //se trovo l'elemento
        {
            t = f->tipo; //ritorno il tipo e 1
            return 1;
        }
        f = f->next; //vado al prossimo
    }

    return 0; //se arrivo qui vuoldire che non ho trovato l'elemento
}

MediaPlaylist::MediaPlaylist(item* vett, int n) {
    if(n < 0) exit(1);

    p0 = NULL; //inizializzo vuota

    //check se la stringa è più lunga della massima dimensione
    int i;
    char str[TITLEN+1];

    file* p;
    file* q;
    for(int i = 0; i < n; i++) //per ogni elemento di vett
    {
        for(q = p0; q != NULL; q = q->next) { //ciclo in fondo alla lista da creare
            if(strcmp(vett[i].titolo, q->titolo) == 0) exit(1); //se trovo lo stesso titolo esco
            p = q; //vado al prossimo
        }

        q = new file; //alloco il nuovo file
        strcpy(q->titolo, vett[i].titolo); //copio direttamente
        q->titolo[strlen(q->titolo)] = '\0'; //set carattere di fine stringa
        q->tipo = vett[i].tipo; //copio l'elemento da tipo
        q->next = NULL; //punta a nulla perchè è in fondo alla lista

        if(p0 == NULL) p0 = q; //testa punta all'elemento se la lista era vuota
        else p->next = q; //altrimenti quello prima punta a quello appena creato
    }
}

MediaPlaylist::MediaPlaylist(const MediaPlaylist& mpl) {
    p0 = NULL; //inizializzo vuota

    //variabili di appoggio per la lista
    file* p;
    file* q;
    file* f = mpl.p0;
    while(f != NULL) //scandisco l'intera lista di mpl
    {
        for(q = p0; q != NULL; q = q->next) p = q; //scandisco in fondo la lista da creare

        q = new file; //alloco il nuovo file
        strcpy(q->titolo, f->titolo); //copio direttamente
        q->titolo[strlen(q->titolo)] = '\0'; //set carattere di fine stringa
        q->tipo = f->tipo; //copio il tipo dato
        q->next = NULL; //punta a nulla perchè è in fondo alla lista

        if(p0 == NULL) p0 = q; //testa punta all'elemento se la lista era vuota
        else p->next = q; //altrimenti quello prima punta a quello appena creato

        f = f->next; //vado al prossimo
    }
}
