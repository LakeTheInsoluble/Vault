// TIE-02200 harjoitustyo-05
// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#include <string>

#ifndef RESEPTIT_H
#define RESEPTIT_H

using namespace std;

class Reseptit {
    public:
        Reseptit();
        ~Reseptit();

        /**
         * @brief tulosta testifunktio, joka tulostaa kaikki reseptit
         */
        void tulosta() const;

        /**
         * @brief lisaa lisaa reseptilistaan uuden reseptin
         * @param tulos uden reseptin lopputulos
         * @param materiaali uuden reseptin materiaali
         */
        void lisaa(const string& tulos, const string& materiaali);

        /**
         * @brief resepti_olemassa tutkii löytyykö tutkittava resepti jo reseptilistasta
         * @param tulos tutkittavan reseptin lopputulos
         * @param materiaali tutkittavan reseptin materiaali
         * @return tosi jos löytyi
         */
        bool resepti_olemassa(const string& tulos, const string& materiaali) const;

        /**
         * @brief resepteissa tutkii löytyykö tutkittava lopputulos reseptilistasta
         * @param etsittava lopputulos, jota etsitään
         * @return tosi jos löytyi
         */
        bool resepteissa(const string &etsittava) const;

        /**
         * @brief montako_materiaalia palauttaa matriaalien määrän tutkittavassa reseptissä
         * @param tulos tutkittava reseptin lopputulos
         * @return montako materiaalia reseptissä on
         */
        int montako_materiaalia(const string& tulos) const;

        /**
         * @brief reseptin_materiaalit asettaa halutun reseptin materiaalit listaan
         * @param tulos etsittävän reseptin lopputulos
         * @param materiaalit lista, johon materiaalit talletetaan
         */
        void reseptin_materiaalit(const string& tulos, string*& materiaalit) const;

    private:
        struct Resepti_alkio {
            string tulos;
            string materiaali;
            Resepti_alkio* seuraavan_osoite;
        };
        Resepti_alkio* ensimmaisen_osoite_;
        Resepti_alkio* viimeisen_osoite_;
};

#endif // RESEPTIT_H
