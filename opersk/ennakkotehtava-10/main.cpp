// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#include <iostream>
#include "lista.hh"

using namespace std;

int main()
{
    Lista lista;
    lista.lisaa_alkio_loppuun("5");
    lista.poista_alkio("5");
    lista.lisaa_alkio_loppuun("4");
    lista.lisaa_alkio_loppuun("3");
    lista.tulosta();
    lista.poista_alkio("4");
    lista.poista_alkio("3");
    cout << "-----------------------------" << endl;
    lista.lisaa_alkio_loppuun("5");
    lista.lisaa_alkio_loppuun("4");
    lista.lisaa_alkio_loppuun("3");
    lista.lisaa_alkio_loppuun("2");
    lista.poista_alkio("2");
    lista.lisaa_alkio_loppuun("1");
    lista.poista_alkio("4");
    lista.lisaa_alkio_loppuun("0");
    lista.tulosta();
}
