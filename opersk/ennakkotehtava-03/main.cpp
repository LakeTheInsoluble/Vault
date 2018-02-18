#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;


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
        //     #include <stdexcept>
        //     ...
        //     throw out_of_range("virheellinen kentan_numero");
        //
        string hae_kentta(unsigned int kentan_numero) const;

    private:
        string merkkijono_;
        vector<string> paloittelu = {};
};

int main(int argc, char *argv[])
{
    Splitter paloittelija("a::bc:def::hijlkm");

    paloittelija.paloittele(':');  // Huomaa heittomerkit

    cout << "kenttia: " << paloittelija.kenttien_lukumaara() << endl;  // 6

    cout << paloittelija.hae_kentta(0) << endl;  // a
    cout << paloittelija.hae_kentta(4) << endl;  // (tyhjä)
    cout << paloittelija.hae_kentta(5) << endl;  // hijlkm

    for ( unsigned int i = 0; i < paloittelija.kenttien_lukumaara(); ++i ) {
        string kasiteltava_kentta = paloittelija.hae_kentta(i);
        cout << i << ": [" << kasiteltava_kentta << "]" << endl;
    }

    paloittelija.aseta_paloiteltava_merkkijono(" A B  C   D    E     ");
    unsigned int kenttia = paloittelija.paloittele(' ', true);

    cout << "kenttia: " << kenttia << endl;  // 5

    for ( unsigned int i = 0; i < kenttia; ++i ) {
        string kasiteltava_kentta = paloittelija.hae_kentta(i);
        cout << i << ": [" << kasiteltava_kentta << "]" << endl;
    }

    cout << paloittelija.hae_kentta(5) << endl;  // out_of_range
}

Splitter::Splitter(const string& merkkijono):
    merkkijono_(merkkijono) {
}

void Splitter::aseta_paloiteltava_merkkijono(const string& merkkijono){
    merkkijono_ = merkkijono;
    paloittelu.clear();
}

unsigned int Splitter::paloittele(char erotinmerkki, bool ohita_tyhjat){
    unsigned int kenttia = 0;
    string kentta;

    for(int i = 0; i < merkkijono_.size(); i++){
        if(merkkijono_[i] == erotinmerkki){
            if(kentta != "" || ohita_tyhjat == 0){
                paloittelu.push_back(kentta);
                kentta = "";
                kenttia ++;
            }
        }else{
            kentta += merkkijono_[i];
        }
    }
    if(kentta != ""){
        paloittelu.push_back(kentta);
        kenttia ++;
    }

    return kenttia;
}

unsigned int Splitter::kenttien_lukumaara() const{
    return paloittelu.size();
}

string Splitter::hae_kentta(unsigned int kentan_numero) const{
    if(kentan_numero > paloittelu.size()){
        throw out_of_range("virheellinen kentan_numero");
    }else{
        return paloittelu.at(kentan_numero);
    }
}
