// TIE-02200 harjoitustyo-05
// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#include "reseptit.h"
#include "reppu.h"

#include <regex>

#ifndef KOMENNOT_H
#define KOMENNOT_H

/**
 * @brief paloittelee annetun rivin materiaaleiksi ja lisää ne reppuun
 *        lisäksi tulostaa virheilmoiukset jos jokin meni pieleen
 * @param reseptit reseptilista, josta tutkitaan löytyykö materiaalia
 * @param reppu kohdereppu, johon materiaalit lisätään
 * @param rivi sisältää kaiki materiaalit yhdessä stringissä
 * @return tosi jos onnistui
 */
bool lisaa_reppuun(const Reseptit& reseptit, Reppu& reppu, string rivi);

/**
 * @brief materiaalit tulostaa halutun lopputuloksen kaikki materiaalit
 * @param reseptit reseptilista, jonka mukaan tulostetaan
 * @param materiaali etsittävä lopputulos
 * @return epätosi jos jokin meni pieleen
 */
bool materiaalit(const Reseptit& reseptit, string materiaali);

/**
 * @brief askarreltavissa tutkii löytyvätkö lopputuloksen materiaalit repusta
 * @param reseptit reseptilista, josta tutkitaan
 * @param reppu sisältää materiaalit, joista lopputulos olisi tarkoitus tehdä
 * @param askarreltava lopputulos, jonka materiaaleja tutkitaan
 * @return
 */
bool askarreltavissa(const Reseptit& reseptit, const Reppu& reppu, string askarreltava);

/**
 * @brief askarreltavissa tutkii löytyvätkö lopputuloksen materiaalit repusta rekursiivisesti
 * @param reseptit reseptilista, josta tutkitaan
 * @param reppu sisältää materiaalit, joista lopputulos olisi tarkoitus tehdä
 * @param askarreltava lopputulos, jonka materiaaleja tutkitaan
 * @return
 */
bool askarreltavissa_bonus(const Reseptit& reseptit, const Reppu& reppu, string askarreltava);

#endif // KOMENNOT_H
