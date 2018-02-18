// TIE-02200 harjoitustyo-05
// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#include "reseptit.h"
#include "reppu.h"
#include "komennot.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

int main()
{
    string rivi;
    Reseptit reseptit;
    Reppu reppu;
    smatch tulos;
    regex RESEPTI_REGEX(
                "[[:space:]]*"
                "([a-zA-Z_]+)"
                "[[:space:]]*"
                ":"
                "[[:space:]]*"
                "([a-zA-Z_]+)"
                "[[:space:]]*"
                );
    regex OHITETTAVA_REGEX(
                "^ *(?:#.*)?$"
                );
    regex LOPETA_REGEX(
                " *loppu *"
                );
    regex KOMENTO_REGEX(
                " *"
                "([[:alpha:]_]+)"
                "(?: +([[:alpha:]_]+))?"
                " *"
                );
    regex TYHJA_REPPU_REGEX(" *reppu *");
    regex REPPU_REGEX(" *reppu +(.+) *");

    // Reseptien luku tiedostosta.
    cout << "Syotetiedosto: ";
    getline(cin, rivi);
    ifstream tiedosto(rivi);
    if (not tiedosto) {
        cout << "Virhe tiedoston avaamisessa." << endl;
        return 1;
    } else {
        while(getline(tiedosto, rivi)) {
            if(regex_match(rivi, tulos, RESEPTI_REGEX)) {
                if(reseptit.resepti_olemassa(tulos[1], tulos[2])) {
                    cout << "Virhe: Resepti jo lisatty. Ohjelman suoritus lopetetaan." << endl;
                    return 1;
                }
                reseptit.lisaa(tulos[1], tulos[2]);
            } else if(not regex_match(rivi, tulos, OHITETTAVA_REGEX)) {
                cout << "Virhe: Virheellinen rivi. Ohjelman suoritus lopetetaan." << endl;
                return 1;
            }
        }
        cout << "Tuotantoketjut luettu onnistuneesti." << endl;
    }

    // While loop käyttäjän komentojen lukemiseen ja niitä vastaavien funktioiden kutsumiseen.
    cout << "testikayttoliittyma> ";
    while(getline(cin, rivi)) {
        if(regex_match(rivi, LOPETA_REGEX)) {
            return 0;
        } else if(regex_match(rivi, tulos, TYHJA_REPPU_REGEX)) {
            reppu.tyhjenna();
            cout << "Reppu tyhjennetty." << endl;
        } else if(regex_match(rivi, tulos, REPPU_REGEX)) {
            if(lisaa_reppuun(reseptit, reppu, tulos.str(1))) {
                cout << "Repun sisalto asetettu." << endl;
            }
        } else if(regex_match(rivi, tulos, KOMENTO_REGEX)) {
            if(tulos[1] == "tulostareppu" && tulos[2] == "") {
                reppu.tulosta();
            } else if(tulos[1] == "materiaalit" && tulos[2] != "" && tulos[3] == "") {
                if(not materiaalit(reseptit, tulos[2])) {
                    cout << "Virhe: Tulosta ei reseptilistasa." << endl;
                }
            } else if(tulos[1] == "askarreltavissa" && tulos[2] != "" && tulos[3] == "") {
                if(askarreltavissa(reseptit, reppu, tulos[2])) {
                    cout << "On askarreltavissa." << endl;
                } else {
                    if(!reseptit.resepteissa(tulos[2])) {
                        cout << "Virhe: Lopputulos ei resepteissa." << endl;
                    } else {
                        cout << "Ei ole askarreltavissa." << endl;
                    }
                }
            } else if(tulos[1] == "askarreltavissa_bonus" && tulos[2] != "" && tulos[3] == "") {
                if(askarreltavissa_bonus(reseptit, reppu, tulos[2])) {
                    cout << "On askarreltavissa." << endl;
                } else {
                    if(!reseptit.resepteissa(tulos[2])) {
                        cout << "Virhe: Lopputulos ei resepteissa." << endl;
                    } else {
                        cout << "Ei ole askarreltavissa." << endl;
                    }
                }
            } else {
                cout << "Virhe: Virheellinen syöte." << endl;
            }
        }else {
            cout << "Virhe: Virheellinen syöte." << endl;
        }
        cout << "testikayttoliittyma> ";
    }
}
