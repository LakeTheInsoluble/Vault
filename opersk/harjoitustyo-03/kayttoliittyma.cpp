// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -mallikoodi
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include "apufunktiot.hh"
#include "todo_rakenne.hh"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;


void suorita_lisaa(Todo& tehtavat, const vector<string>& kentat);
void suorita_listaa(Todo& tehtavat, const vector<string>& kentat);
void suorita_talleta(Todo& tehtavat, const vector<string>& kentat);
void suorita_tehtava(Todo& tehtavat, const vector<string>& kentat);


using Funktiotyyppi = decltype(&suorita_lisaa);
using Kaskyrakenne = map<string, Funktiotyyppi>;


const Kaskyrakenne TUNNETUT_KASKYT = {
    { "lisaa",   suorita_lisaa  },
    { "listaa",  suorita_listaa },
    { "talleta", suorita_talleta },
    { "suorita", suorita_tehtava }
};


void kayttoliittyma(Todo& tehtavarakenne) {
    cout << "tehtavalista> ";
    string rivi;
    if ( not getline(cin, rivi) ) {
        return;
    }

    vector<string> kentat = paloittele_sanoiksi(rivi);

    if ( kentat.empty()
           or kentat.at(0) == "lopeta"
           or kentat.at(0) == "loppu" ) {

        return;

    } else if ( TUNNETUT_KASKYT.find(kentat.at(0)) == TUNNETUT_KASKYT.end()) {
        virheilmoitus(kentat.at(0) + " on tuntematon kasky.");
        kayttoliittyma(tehtavarakenne);

    } else {

        TUNNETUT_KASKYT.at(kentat.at(0))(tehtavarakenne, kentat);
        kayttoliittyma(tehtavarakenne);
    }
}


void suorita_listaa(Todo& tehtavat, const vector<string>& kentat) {
    if ( kentat.size() != 1 ) {
        virheilmoitus("listaa: vaara maara sanoja syoterivilla.");

    } else {

        tehtavat.listaa_tehtavat();
    }
}


void suorita_lisaa(Todo& tehtavat, const vector<string>& kentat) {
    int taso = 0;

    if ( kentat.size() < 3 ) {
        virheilmoitus("lisaa: liian vahan sanoja syoterivilla.");
        return;

    } else if ( not muuta_string_intiksi(kentat.at(1), taso) ) {

        virheilmoitus("lisaa: kiireellisyystaso ei ole numero.");
        return;
    }

    string kuvaus = yhdista_valilyonneilla(kentat.begin() + 2, kentat.end());

    if ( not tehtavat.lisaa_tehtava(taso, kuvaus) ) {

        virheilmoitus("lisaa: sopimaton kiireellisyystaso.");
    }
}


void suorita_talleta(Todo& tehtavat, const vector<string>& kentat) {
    if ( kentat.size() != 2 ) {
        virheilmoitus("talleta: vaara maara sanoja syoterivilla.");
        return;
    }

    ofstream talletusvirta(kentat.at(1));
    if ( not talletusvirta
           or not tehtavat.talleta_tiedostoon(talletusvirta) ) {

        virheilmoitus("talleta: tiedostoon kirjoittaminen epaonnistui.");
    } else {


        cout << "Tiedosto talletettu." << endl;
    }
}


void suorita_tehtava(Todo& tehtavat, const vector<string>& kentat) {
    if ( kentat.size() != 1 ) {
        virheilmoitus("suorita: vaara maara sanoja syoterivilla.");
        return;
    }

    string suoritettava = tehtavat.suorita_tehtava();
    if( suoritettava == "" ) {
        virheilmoitus("suorita: todo-listalla ei olee enaa tehtavia.");
    } else {
        cout << "Suoritusvuorossa: " << suoritettava << endl;
    }
}
