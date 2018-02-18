// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -mallikoodi
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


void virheilmoitus(const string& teksti) {
    cout << "Virhe: " << teksti << endl;
}


vector<string> paloittele_sanoiksi(const string& teksti) {
    istringstream virta(teksti);
    vector<string> tulos = { };

    string sana;
    while ( virta >> sana ) {
        tulos.push_back(sana);
    }

    return tulos;
}


bool muuta_string_intiksi(const string& mjono, int& tulos) {
    istringstream virta(mjono);

    int aputulos;

    virta >> aputulos;
    if ( not virta ) {
        return false;
    }

    virta >> ws;
    virta.get();

    if ( not virta.eof() ) {
        return false;

    } else {

        tulos = aputulos;

        return true;
    }
}


string yhdista_valilyonneilla(vector<string>::const_iterator it,
                              vector<string>::const_iterator loppu) {
    if ( it == loppu ) {
        return "";

    } else if ( it + 1 == loppu ) {
        return *it;

    } else {

        return *it + " " + yhdista_valilyonneilla(it + 1, loppu);
    }
}
