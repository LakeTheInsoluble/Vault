#include <iostream>
#include <iomanip>

using namespace std;

class Kellonaika {
    public:
        Kellonaika(int tunti, int minuutti);
        void tiktok();
        int hae_tunti() const;
        int hae_minuutti() const;
        int erotus(Kellonaika) const;
        void tulosta() const;
    private:
    // Kello 00.00:sta kuluneet minuutit
        int kuluneet_minuutit_;
};

int main() {
    int tunnit1;
    int minuutit1;
    int tunnit2;
    int minuutit2;

    cout << "Anna tunnit: ";
    cin >> tunnit1;
    cout << "ja minuutit: ";
    cin >> minuutit1;

    Kellonaika aika1(tunnit1, minuutit1);

    cout << "Anna toisen ajan tunnit: ";
    cin >> tunnit2;
    cout << "ja minuutit: ";
    cin >> minuutit2;

    Kellonaika aika2(tunnit2, minuutit2);


    cout << "Kellonaikojen välillä on " << aika1.erotus(aika2) << " minuuttia" << endl;
}

Kellonaika::Kellonaika(int tunti, int minuutti):
    kuluneet_minuutit_(60 * tunti + minuutti) {
}

void Kellonaika::tiktok() {
    ++kuluneet_minuutit_;
    if ( kuluneet_minuutit_ >= 24 * 60 ) {
        kuluneet_minuutit_ = 0;
    }
}

int Kellonaika::hae_tunti() const {
    // Kun kokonaisluku jaetaan kokonaisluvulla
    // tuloksena on kokonaisluku (jakojäännös
    // heitetään menemään).
    return kuluneet_minuutit_ / 60;
}

int Kellonaika::hae_minuutti() const {
    return kuluneet_minuutit_ % 60;
}

int Kellonaika::erotus(Kellonaika toinen) const {
    int erotus = toinen.kuluneet_minuutit_ - kuluneet_minuutit_;
    if(erotus < 0){
        erotus += 1440;
    }
    return erotus;
}

void Kellonaika::tulosta() const {
    cout << setfill('0') << setw(2) << hae_tunti()
    << "."
    << setw(2) << hae_minuutti()
    << endl;
}
