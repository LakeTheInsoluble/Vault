// TIE-02200 harjoitustyo-05
// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

#ifndef REPPU_H
#define REPPU_H

#include <string>

using namespace std;

class Reppu {
    public:
        Reppu();
        ~Reppu();

        /**
         * @brief lisaa lisaa materiaalin reppuun
         * @param lisattava materiaali, joka lisätään reppuun
         */
        void lisaa(const string& lisattava);

        /**
         * @brief koko palauttaa repun koon
         * @return repun koko
         */
        int koko() const;

        /**
         * @brief tyhjenna tyhjentää repun
         */
        void tyhjenna();

        /**
         * @brief tulosta tulostaa kaikki repussa olevat materiaalit
         */
        void tulosta() const;

        /**
         * @brief etsi tutkii löytyykö etsittävä materaali repusta
         * @param etsittava materiaali, jota etsitään
         * @return tosi jos löytyi
         */
        bool etsi(const string& etsittava) const;

    private:
        string* reppu;
        int size;
        int max_size;
};

#endif // REPPU_H
