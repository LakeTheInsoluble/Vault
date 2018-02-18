#ifndef SPLITTER_HH
#define SPLITTER_HH

#include <string>
#include <vector>

using namespace std;

// unsigned int -tyypin avulla voidaan käsitellä arvoja,
// jotka ovat suurempia tai yhtäsuuria kuin nolla (etumerkittömiä),
// eli siis luonnollisia lukuja (?).
const unsigned int SPLITTER_VIRHE = 0;

class Splitter {
  public:
    Splitter(const string& paloiteltava_merkkijono = "");

    // Asetetaan merkkijono, joka halutaan paloitella.
    // Idea on se, että sama Splitter-tyyppistä oliota
    // voidaan käyttää muidenkin kuin rakentajan parametrina
    // annettujen merkkijonojen paloitteluun.
    void aseta_paloiteltava_merkkijono(const string& merkkijono);

    // Paloitellaan merkkijono parametrina annetun
    // erotinmerkin kohdalta osiin. Paluuarvona tieto
    // siitä, montako kenttää rivillä oli.
    // Jos ohita_tyhjat-parametrin arvo on true,
    // paloittelun tuloksena mahdollisesti syntyvät tyhjät kentät
    // jätetään pois lopputuloksesta.  Tämä on hyödyllinen ominaisuus,
    // jos halutaan jakaa merkkijono sanoiksi, mutta ei olla täysin
    // varmoja siitä, onko sanojen välissä yksi vai useampia
    // välilyöntejä: paloittelijaolio.paloittele(' ', true);
    unsigned int paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    // Palauttaa tiedon siitä, montako kenttää aiemmin
    // suoritetun paloittelun tuloksena syntyi.  Käytännössä
    // paluuarvo on siis sama kuin paloittele-metodin paluuarvo
    // edellä.  Erona se, että paluuarvo on SPLITTER_VIRHE,
    // jos paloittele-metodia ei ole kutsuttu sen jälkeen,
    // kun paloiteltava merkkijono on viimeksi asetettu
    // (rakentajassa tai aseta_paloiteltava_merkkijono-metodissa).
    unsigned int kenttien_lukumaara() const;

    // Kun merkkijono on paloiteltu, tällä metodilla
    // voidaan pyytää Splitter-oliolta tietty kenttä.
    // Oletetaan että kentät on numeroitu vasemmalta
    // oikealle alkaen nollasta.  Jos paloittele-metodia
    // ei ole kutsuttu tai kentan_numero on liian
    // suuri rivillä olleiden kenttien lukumäärään
    // verrattuna, metodi tuottaa out_of_range-tyyppisen
    // poikkeuksen:
    //
    //     #include
    //     ...
    //     throw out_of_range("virheellinen kentan_numero");
    //
    string hae_kentta(unsigned int kentan_numero) const;

  private:
    // Lähtötieto: tätä merkkijonoa paloittele-metodi pätkiin osiin.
    string paloiteltava_;

    // paloittele-metodi tallentaa tuloksen tähän vektoriin, niin
    // että kun merkkijono on kerran paloiteltu, sen kenttiin päästään
    // käsiksi nopeasti.
    vector<string> kentat_;
};

#endif // SPLITTER_HH
