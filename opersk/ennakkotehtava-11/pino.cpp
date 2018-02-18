#include "pino.h"

Pino::Pino(): size(0), max_size(2) {
    pino = new int[2];
}

Pino::~Pino() {
    delete [] pino;
}

bool Pino::empty() const{
    if(size == 0) {
        return true;
    } else {
        return false;
    }
}

void Pino::push_front(int lisattava_arvo) {
    if(size == max_size - 1) {
        int * new_pino = new int[max_size * 2];
        for(int i = 0; i < max_size; i++) {
            new_pino[i] = pino[i];
        }
        max_size = max_size * 2;
        delete [] pino;
        pino = new_pino;
    }
    size++;
    pino[size - 1] = lisattava_arvo;
}

bool Pino::pop_front(int &poistettu_arvo) {
    if(size == 0) {
        return false;
    } else {
        poistettu_arvo = pino[size];
        size--;
        return true;
    }
}
