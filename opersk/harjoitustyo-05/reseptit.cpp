// TIE-02200 harjoitustyo-05
// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#include "reseptit.h"

#include <iostream>

using namespace std;

Reseptit::Reseptit(): ensimmaisen_osoite_(nullptr), viimeisen_osoite_(nullptr)
{
}

Reseptit::~Reseptit() {
    Resepti_alkio* vapautettavan_osoite;
    while(ensimmaisen_osoite_ != nullptr) {
        vapautettavan_osoite = ensimmaisen_osoite_;
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
        delete vapautettavan_osoite;
    }
}

void Reseptit::tulosta() const {
    Resepti_alkio* tulostettavan_osoite = ensimmaisen_osoite_;
    while(tulostettavan_osoite != nullptr) {
        cout << tulostettavan_osoite->tulos << ":" << tulostettavan_osoite->materiaali << endl;
        tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
    }
}

void Reseptit::lisaa(const string& tulos, const string& materiaali) {
    Resepti_alkio* uuden_osoite = new Resepti_alkio{tulos, materiaali, nullptr};
    if(ensimmaisen_osoite_ == nullptr) {
        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    } else {
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
}

bool Reseptit::resepti_olemassa(const string &tulos, const string& materiaali) const {
    if(ensimmaisen_osoite_ == nullptr) {
        return false;
    }
    Resepti_alkio* etsin = ensimmaisen_osoite_;
    while(etsin != nullptr) {
        if(etsin->tulos == tulos && etsin->materiaali == materiaali) {
            return true;
        }
        etsin = etsin->seuraavan_osoite;
    }
    return false;
}

bool Reseptit::resepteissa(const string &etsittava) const {
    if(ensimmaisen_osoite_ == nullptr) {
        return false;
    }
    Resepti_alkio* etsin = ensimmaisen_osoite_;
    while(etsin != nullptr) {
        if(etsin->tulos == etsittava || etsin->materiaali == etsittava) {
            return true;
        }
        etsin = etsin->seuraavan_osoite;
    }
    return false;
}

int Reseptit::montako_materiaalia(const string &tulos) const {
    if(ensimmaisen_osoite_ == nullptr) {
        return 0;
    }
    Resepti_alkio* etsin = ensimmaisen_osoite_;
    int montako = 0;
    while(etsin != nullptr) {
        if(etsin->tulos == tulos) {
            montako++;
        }
        etsin = etsin->seuraavan_osoite;
    }
    return montako;
}

void Reseptit::reseptin_materiaalit(const string& tulos, string*& materiaalit) const {
    Resepti_alkio* etsin = ensimmaisen_osoite_;
    int i = 0;
    while(etsin != nullptr) {
        if(etsin->tulos == tulos) {
            materiaalit[i] = etsin->materiaali;
            i++;
        }
        etsin = etsin->seuraavan_osoite;
    }
}
