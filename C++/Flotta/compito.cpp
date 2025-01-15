//
// Created by alex on 02/06/2020.
//

#include "compito.h"

Flotta::Flotta(int n) {
    count = n <= 0 ? 1 : n;

    file = new int[count]; //creo le file

    for(int i = 0; i < count; i++) file[i] = -1; //inizialmente le file non sono formate
}

void Flotta::forma_fila(int i, int n) {
    if(i < 0 || i >= count || n < 0 || file[i] != -1) return; //check input

    file[i] += n + 1; //formo la fila
}

ostream &operator<<(ostream& os, const Flotta& f) {
    int max = int(f); //prendo il max num di aerei per la stampa

    if(max != 0) //se la fila è formata
    {
        for (int i = 0; i < f.count; i++) //ciclo tutta la flotta
        {
            if (f.file[i] != -1) //se la fila è formata
            {
                for (int j = 0; j < max - f.file[i]; j++) os << " "; //stampo spazi

                //stampo aerei
                for (int j = 0; j < f.file[i]; j++)
                {
                    os << "A ";
                }
            }
            else for(int j = 0; j < max; j++) os << "? "; //stampo fila non formata
            os << endl; //nuova riga
        }
    }
    return os;
}

Flotta::operator int()const {
    int max = 0;
    for(int i = 0; i < count; i++) //ciclo la flotta
    {
        if(file[i] > max) max = file[i]; //check e set della variabile max
    }
    return max;
}

Flotta::~Flotta() {
    delete[] file; //dealloco tutta la flotta
}

Flotta::Flotta(const Flotta& f) {
    if(f.count != count) file = new int[f.count]; //creo una nuova flotta

    for(int i = 0; i < f.count; i++)
    {
        file[i] = f.file[i]; //copio membro a membro
    }
}

Flotta operator+(const Flotta &f1, const Flotta &f2) {
    Flotta fnew(f1.count + f2.count);

    for(int i = 0; i < f1.count; i++)
        fnew.file[i] = f1.file[i];

    for(int i = 0; i < f2.count; i++)
        fnew.file[f1.count + i] = f2.file[i];

    return fnew;
}

Flotta& Flotta::operator-=(const Flotta& f) {
    if(f.count != count) return *this; //check input

    //check che nessuna delle due abbia file non complete
    for(int i = 0; i < count; i++)
    {
        if(file[i] == -1 || f.file[i] == -1) return *this;
    }

    //eseguo operazione
    for(int i = 0; i < count; i++)
    {
        if(f.file[i] == file[i]) //se hanno un numero uguale di aerei nella fila
        {
            file[i] /= 2;
        }
        else if(f.file[i] > file[i]) //se l'attacante ha più aerei della difenditrice
        {
            file[i] = 0;
        }
    }
    return *this;
}

Flotta &Flotta::operator+=(const int v[]) {
    for(int i = 0; i < count; i++) //ciclo tutto la flotta
    {
        if(file[i] != -1) file[i] += v[i]; //se la fila è formata aggiungo aerei dal vettore
    }
    return *this;
}

