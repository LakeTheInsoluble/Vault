// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -mallikoodi
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include "todo_rakenne.hh"
#include <fstream>
#include <string>

#include <iostream>

using namespace std;


// ----------------------------------------------------------------------------
// lue_tehtavatiedosto
// -------------------
// Funktio lukee parametrina saamansa tietovirran avulla tehtävälistatiedoston
// ja lisää sieltä saamansa tiedot tehtavarakenteeseen.  Jos tiedostossa
// on virheellisiä rivejä, funktion on palautettava false.  Jos tiedosto on
// virheetön, paluuarvon oltava true.  Tiedoston lukemin tämän funktion
// avulla EI SAA TULOSTAA NÄYTÖLLE MITÄÄN, sillä virheilmoitusten tulostuksesta
// on huolehdittu pääohjelmassa.
//
// KOKO TIEDOSTON LUKEMINEN ON TOTEUTETTAVA REKURSION AVULLA.  Tämä funktio,
// eikä sen avuksi itse toteutetut apufunktiot saa sisältää yhtään silmukka-
// rakennetta.  Silmukkarakenteet ovat tässä yhteydessä työn hylkäämisperuste.
//
// Funktion paluuarvo ja parametrien tyypit ja määrä on säilytettävä.
// ET SIIS SAA MUUTTAA LUE_TEHTAVATIEDOSTO-FUNKTION RAJAPINTAA.
// ----------------------------------------------------------------------------
bool lue_tehtavatiedosto(ifstream& virta, Todo& tehtavarakenne) {
    string rivi;
    int kiireellisyys;
    string kuvaus;

    getline(virta, rivi);

    if(rivi == "") {
        return true;
    }
    if(rivi.find_first_of(";") == rivi.npos) {
        return false;
    }
    if((!isdigit(rivi[0]) && rivi[1] == ';')) {
        return false;
    }
    kiireellisyys = stoi(rivi.substr(0,1));
    if(kiireellisyys < 1 || kiireellisyys > 5) {
        return false;
    }
    kuvaus = rivi.substr(2);
    if(kuvaus.find_first_not_of(' ') == string::npos) {
        return false;
    }

    tehtavarakenne.lisaa_tehtava(kiireellisyys, kuvaus);

    return lue_tehtavatiedosto(virta, tehtavarakenne);
}
