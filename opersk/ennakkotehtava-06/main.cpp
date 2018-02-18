#include <iostream>
#include <map>

using namespace std;

int laske_nimet(const map<string, string>& puhelinluettelo, char nimen_alkukirjain);

// tämä toteutus on typerä, mutta en keksinyt muuta jos tahdoin pitää funktion kutsun samanlaisena
int laske_nimet_rekursiivisesti_1(const map<string, string>& puhelinluettelo, char nimen_alkukirjain);

// tämä taas on mielestäni ihan järkevä ratkaisu ja se pitää alkuperäien puhelinluetelon kivasti oikeanlaisena
// mitä const muuttujilla taidettiin hakea
// periaatteessahan tämä tekee saman kuin ylempikin, mutta paljon siistimmin
int laske_nimet_rekursiivisesti_2(map<string, string> puhelinluettelo, char nimen_alkukirjain);

// dynaamisesti asetettua muuttujaa ei voi asettaa staticicsi, koska static muuttujan arvo tulee olla tiedossa käännettäessä
int laske_nimet_rekursiivisesti_3(const map<string, string>& puhelinluettelo, char nimen_alkukirjain);

// tämä on viimeisin versio ja kaikista "kivoin" omasta mielestäni
int laske_nimet_rekursiivisesti_3(const map<string, string>& puhelinluettelo, char nimen_alkukirjain);

int main()
{
    map<string, string> pl = {
        {"pena", "1"},
        {"pertti", "2"},
        {"simo", "3"},
        {"pirjo", "4"},
        {"pauliina", "5"},
        {"siiri", "6"}
    };
    cout << laske_nimet(pl, 'p') << endl;
    cout << laske_nimet_rekursiivisesti_1(pl, 'p') << endl;
    cout << laske_nimet_rekursiivisesti_2(pl, 'p') << endl;
    cout << laske_nimet_rekursiivisesti_3(pl, 'p') << endl;
}

int laske_nimet_rekursiivisesti_1(const map<string, string>& puhelinluettelo, char nimen_alkukirjain)
{
    int lukumaara = 0;

    map<string, string>::const_iterator iter = puhelinluettelo.begin();
    map<string, string> upl = puhelinluettelo;

    if(puhelinluettelo.size() == 0)
    {
        return 0;
    }

    if(iter->first[0] == nimen_alkukirjain)
    {
        lukumaara++;
    }

    upl.erase(iter->first);

    lukumaara += laske_nimet_rekursiivisesti_1(upl, nimen_alkukirjain);

    return lukumaara;
}

int laske_nimet_rekursiivisesti_2(map<string, string> puhelinluettelo, char nimen_alkukirjain)
{
    int lukumaara = 0;

    map<string, string>::const_iterator iter = puhelinluettelo.begin();

    if(puhelinluettelo.size() == 0)
    {
        return 0;
    }

    if(iter->first[0] == nimen_alkukirjain)
    {
        lukumaara++;
    }

    puhelinluettelo.erase(iter->first);

    lukumaara += laske_nimet_rekursiivisesti_2(puhelinluettelo, nimen_alkukirjain);

    return lukumaara;
}

int laske_nimet_rekursiivisesti_3(const map<string, string>& puhelinluettelo, char nimen_alkukirjain)
{
    int lukumaara = 0;

    static map<string, string>::const_iterator iter = puhelinluettelo.begin();

    if(iter == puhelinluettelo.end())
    {
        return 0;
    }

    if(iter->first[0] == nimen_alkukirjain)
    {
        lukumaara++;
    }

    iter++;

    lukumaara += laske_nimet_rekursiivisesti_3(puhelinluettelo, nimen_alkukirjain);

    return lukumaara;
}

int laske_nimet(const map<string, string>& puhelinluettelo, char nimen_alkukirjain)
{
    int lukumaara = 0;

    map<string, string>::const_iterator iter = puhelinluettelo.begin();

    while ( iter != puhelinluettelo.end() )
    {
        if ( iter->first.at(0) == nimen_alkukirjain )
        {
            ++lukumaara;
        }

        ++iter;
    }

    return lukumaara;
}
