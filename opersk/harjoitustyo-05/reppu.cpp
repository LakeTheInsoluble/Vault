// TIE-02200 harjoitustyo-05
// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#include "reppu.h"

#include <iostream>

using namespace std;

Reppu::Reppu(): size(0), max_size(2) {
    reppu = new string[2];
}

Reppu::~Reppu() {
    delete [] reppu;
}

void Reppu::lisaa(const string& lisattava) {
    if(size == max_size - 1) {
        string * new_reppu = new string[max_size * 2];
        for(int i = 0; i < max_size; i++) {
            new_reppu[i] = reppu[i];
        }
        max_size = max_size * 2;
        delete [] reppu;
        reppu = new_reppu;
    }
    size++;
    reppu[size - 1] = lisattava;
}

int Reppu::koko() const {
    return size;
}

void Reppu::tyhjenna() {
    delete [] reppu;
    reppu = new string[2];
    size = 0;
    max_size = 2;
}

void Reppu::tulosta() const {
    for(int i = 0; i < size; i++) {
        cout << reppu[i] << endl;
    }
}

bool Reppu::etsi(const string& etsittava) const{
    for(int i = 0; i < size; i++) {
        if(reppu[i] == etsittava) {
            return true;
        }
    }
    return false;
}
