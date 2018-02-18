// TIE-02200 harjoitustyo-05
// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#include "reseptit.h"
#include "reppu.h"

#include <iostream>
#include <regex>
#include <algorithm>

bool lisaa_reppuun(const Reseptit& reseptit, Reppu& reppu, string rivi) {
    regex MATERIAALI_REGEX("[[:alpha:]_]+");
    sregex_iterator it(rivi.begin(), rivi.end(), MATERIAALI_REGEX);
    sregex_iterator end;

    reppu.tyhjenna();
    while(it != end) {
        if(reppu.etsi(it->str())) {
            cout << "Virhe: Materiaali tai esine loytyy jo repusta! Reppu tyhjennetty." << endl;
            reppu.tyhjenna();
            return false;
        } else if(not reseptit.resepteissa(it->str())) {
            cout << "Virhe: Materiaalia tai esinetta ei loydy reseptilistasta! Reppu tyhjennetty." << endl;
            reppu.tyhjenna();
            return false;
        }else {
            reppu.lisaa(it->str());
        }
        it++;
    }
    return true;
}

bool materiaalit(const Reseptit& reseptit, string materiaali) {
    int koko = reseptit.montako_materiaalia(materiaali);
    if(koko == 0 && not reseptit.resepteissa(materiaali)) {
        return false;
    }
    string* materiaalit = new string[koko];

    reseptit.reseptin_materiaalit(materiaali, materiaalit);

    sort(materiaalit, materiaalit+koko);
    for(int i = 0; i < koko; i++) {
        cout << materiaalit[i] << endl;
    }
    delete [] materiaalit;
    return true;
}

bool askarreltavissa(const Reseptit& reseptit, const Reppu& reppu, string askarreltava) {
    if(reppu.koko() > 0) {
        if(reppu.etsi(askarreltava)) {
            return true;
        }
        int koko = reseptit.montako_materiaalia(askarreltava);
        if(koko == 0) {
            return false;
        }
        string* materiaalit = new string[koko];
        bool askarreltavissa = true;

        reseptit.reseptin_materiaalit(askarreltava, materiaalit);

        for(int i = 0; i < koko; i++) {
            if(not reppu.etsi(materiaalit[i])) {
                askarreltavissa = false;
            }
        }
        delete [] materiaalit;
        if(askarreltavissa) {
            return true;
        }
    }
    return false;
}

bool askarreltavissa_bonus(const Reseptit& reseptit, const Reppu& reppu, string askarreltava) {
    if(reppu.koko() > 0) {
        if(reppu.etsi(askarreltava)) {
            return true;
        }
        int koko = reseptit.montako_materiaalia(askarreltava);
        if(koko == 0) {
            return false;
        }
        string* materiaalit = new string[koko];
        bool askarreltavissa = true;

        reseptit.reseptin_materiaalit(askarreltava, materiaalit);

        for(int i = 0; i < koko; i++) {
            if(not reppu.etsi(materiaalit[i])) {
                if(not askarreltavissa_bonus(reseptit, reppu, materiaalit[i])) {
                    askarreltavissa = false;
                }
            }
        }
        delete [] materiaalit;
        if(askarreltavissa) {
            return true;
        }
    }
    return false;
}
