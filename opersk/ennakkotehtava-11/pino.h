#ifndef PINO_H
#define PINO_H

class Pino {
    public:
        Pino();
        ~Pino();

        // empty palauttaa true vain, jos rakenteeseen (private-osan
        // linkitetty lista) ei sisällä yhtään alkiota.
        bool empty() const;

        // push_front lisää parametrina saamansa kokonaisluvun
        // private-osan linkitetyn listan alkuun.
        void push_front(int lisattava_arvo);


        // pop_front poistaa listan alusta yhden luvun ja tallentaa
        // sen viiteprametriinsa.  Jos lista on tyhjä, parametrin arvo
        // ei muutu, ja funktio palauttaa false.  Jos listasta saatiin
        // poistettua arvo, paluuarvo on true.
        bool pop_front(int& poistettu_arvo);

    private:
        int* pino;
        int size;
        int max_size;
};

#endif // PINO_H
