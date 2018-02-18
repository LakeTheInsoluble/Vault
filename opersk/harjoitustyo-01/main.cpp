/* Henri Laakso
 * 240062
 * henri.m.laakso@student.tut.fi
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

/* paloittele ottaa vastaan string tyyppisen mekkijonon ja paloittelee sen osat komennoiksi
 * komento[0] sisältää tekstiosan
 * komento[1] ja eteenpäin sisältävät komennon lisäargumentit
 * input sisältää paloiteltavan komennon
 * return paloiteltu komento vektorimuodossa
 */
vector<string> paloittele(string input);

class Pankkitili{
    public:
        Pankkitili(string tilinumero, double saldo, string asiakasnumero);

        // Tulostaa pankkitilin tiedot.
        void tulosta();

        // Asettaa tilin tiedot halutuiksi
        // Tarkistus ennen aseta kutsumista
        void aseta(string tilinumero, double saldo, string asiakasnumero);

        // Lisää halutun määrän tilille
        void pano(double maara);

        // Vähentää halutun määrän tililtä ja palauttaa true jos onnistui.
        // Jos tilillä ei tarpeeksi rahaa ei tee mitään ja palauttaa false.
        bool otto(double maara);

        // Vähentää halutun määrän tililtä, lisää määrän toiselle tilille ja palauttaa true jos onnistui.
        // Jos tilillä ei tarpeeksi rahaa ei tee mitään ja palauttaa false.
        bool siirto(Pankkitili tili, double maara);
    private:
        string tilinumero_;
        double saldo_;
        string asiakasnumero_;
};

int main() {
    string input;
    vector<string> komento;
    vector<Pankkitili> tilit;

    double maara;
    string tilinumero;
    double saldo;
    string asiakasnumero;


    // Luodaan tyhjät pankkitilit valmiiksi
    tilit.push_back(Pankkitili("FI01", 0, "1"));
    tilit.push_back(Pankkitili("FI02", 0, "2"));
    tilit.push_back(Pankkitili("FI03", 0, "3"));

    do
    {
        komento.clear();

        cout << "pankkitilitesti> ";
        getline(cin, input);
        komento = paloittele(input);

        if(komento[0] == "tulosta" && komento.size() == 2 && stoul(komento[1])-1 < tilit.size())
        {
            tilit[stoi(komento[1])-1].tulosta();
        }
        else if(komento[0] == "aseta" && komento.size() == 2 && stoul(komento[1])-1 < tilit.size())
        {
            cout << "Syötä tilinumero: ";
            getline(cin, tilinumero);
            cout << "Syötä saldo: ";
            getline(cin, input);
            saldo = stod(input);
            cout << "Syötä asiakasnumero: ";
            getline(cin, input);
            asiakasnumero = input;

            if(saldo >= 0)
            {
                tilit[stoi(komento[1])-1].aseta(tilinumero, saldo, asiakasnumero);
                cout << "Tilin " << komento[1] << " tiedot asetettu." << endl;
            }
            else
            {
                cout << "Virhe: Tilin saldo ei voi olla negativinen." << endl;
            }
        }
        else if(komento[0] == "pano" && komento.size() == 2 && stoul(komento[1])-1 < tilit.size())
        {
            cout << "Syötä rahamäärä: ";
            getline(cin, input);
            maara = stod(input);

            if(maara >= 0)
            {
                tilit[stoi(komento[1])-1].pano(maara);
                cout << "Pano suoritettu tilille " << komento[1] << "." << endl;
            }
            else
            {
                cout << "Virhe: Pano epäonnistui." << endl;
            }
        }
        else if(komento[0] == "otto" && komento.size() == 2 && stoul(komento[1])-1 < tilit.size())
        {
            cout << "Syötä rahamäärä: ";
            getline(cin, input);
            maara = stod(input);

            if(tilit[stoi(komento[1])-1].otto(maara))
            {
                cout << "Otto suoritettu tililtä " << komento[1] << "." << endl;
            }
            else
            {
                cout << "Virhe: Otto epäonnistui. Tilillä ei riittävästi rahaa." << endl;
            }
        }
        else if(komento[0] == "tilisiirto" && komento.size() == 3 &&
                  stoul(komento[1])-1 < tilit.size() && stoul(komento[2])-1 < tilit.size())
        {
            cout << "Syötä siirtomäärä: ";
            getline(cin, input);
            maara = stod(input);
            if(maara <= 0)
            {
                cout << "Virhe: Siirto epäonnistui." << endl;
            }
            else if(tilit[stoi(komento[1])-1].otto(maara))
            {
                tilit[stoi(komento[2])-1].pano(maara);
            }
            else
            {
                cout << "Virhe: Siirto epäonnistui. Tilillä ei riittävästi rahaa." << endl;
            }
        }
        else if(komento[0] != "loppu")
        {
            cout << "Virhe: Epäsopiva komento" << endl;
        }
    } while(komento.at(0) != "loppu");
}

Pankkitili::Pankkitili(string tilinumero, double saldo, string asiakasnumero):
    tilinumero_(tilinumero), saldo_(saldo), asiakasnumero_(asiakasnumero)
{
}

void Pankkitili::tulosta()
{
    cout << "Tilinumero: " << tilinumero_ << endl;
    cout << fixed;
    cout << setprecision(2);
    cout << "Saldo: " << saldo_ << endl;
    cout << "Asiakasnumero: " << asiakasnumero_ << endl;
}

void Pankkitili::aseta(string tilinumero, double saldo, string asiakasnumero)
{
    tilinumero_ = tilinumero;
    saldo_ = saldo;
    asiakasnumero_ = asiakasnumero;
}

void Pankkitili::pano(double maara)
{
    saldo_ += maara;
}

bool Pankkitili::otto(double maara)
{
    if(saldo_ >= maara)
    {
        saldo_ -= maara;
        return true;
    }
    else
    {
        return false;
    }
}

bool Pankkitili::siirto(Pankkitili tili, double maara)
{
    if(saldo_ >= maara)
    {
        saldo_ -= maara;
        tili.pano(maara);
        return true;
    }
    else
    {
        return false;
    }
}

vector<string> paloittele(string input)
{
    vector<string> komento;
    string temp = "";

    for(unsigned int i = 0; i < input.size(); i++)
    {
        if(input[i] == ' ')
        {
            if(temp != "")
            {
                komento.push_back(temp);
                temp = "";
            }
        }
        else {
            temp += input[i];
        }
    }
    if(temp != "")
    {
        komento.push_back(temp);
    }
    return komento;
}
