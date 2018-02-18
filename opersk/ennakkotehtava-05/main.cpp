#include "splitter.hh"
#include "laskin.hh"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    string input;
    Splitter paloittelija;
    double tulos;

    cout << setprecision(3);

    while(1)
    {
        cout << "Laskin> ";
        getline (cin, input);
        if(input == "")
        {
            break;
        }
        paloittelija.aseta_paloiteltava_merkkijono(input);
        paloittelija.paloittele(' ', true);

        if(paloittelija.hae_kentta(1) == "+")
        {
            tulos = yhteen(stod(paloittelija.hae_kentta(0)), stod(paloittelija.hae_kentta(2)));
            cout << tulos << endl;
        }
        else if(paloittelija.hae_kentta(1) == "-")
        {
            tulos = vahennys(stod(paloittelija.hae_kentta(0)), stod(paloittelija.hae_kentta(2)));
            cout << tulos << endl;
        }
        else if(paloittelija.hae_kentta(1) == "*")
        {
            tulos = kerto(stod(paloittelija.hae_kentta(0)), stod(paloittelija.hae_kentta(2)));
            cout << tulos << endl;
        }
        else if(paloittelija.hae_kentta(1) == "/")
        {
            tulos = jako(stod(paloittelija.hae_kentta(0)), stod(paloittelija.hae_kentta(2)));
            cout << tulos << endl;
        }
    }
    cout << "Kiitos ja näkemiin!" << endl;
}
