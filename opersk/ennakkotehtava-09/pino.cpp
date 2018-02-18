#include "pino.h"

Pino::Pino(): ensimmainen(nullptr), viimeinen(nullptr) {
}

Pino::~Pino() {
    int temp = 0;
    while(pop_front(temp));
}

bool Pino::empty() const{
    if(ensimmainen == nullptr) {
        return true;
    } else {
        return false;
    }
}

void Pino::push_front(int lisattava_arvo) {
    alkio* temp_ptr = ensimmainen;
    alkio* uusi = new alkio{lisattava_arvo, temp_ptr};
    ensimmainen = uusi;
}

bool Pino::pop_front(int &poistettu_arvo) {
    alkio* poistettava = ensimmainen;

    if(ensimmainen == nullptr) { return false; }

    poistettu_arvo = poistettava->luku;
    ensimmainen = poistettava->seuraava;

    delete poistettava;

    return true;
}
