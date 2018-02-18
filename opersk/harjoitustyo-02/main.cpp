// Henri Laakso 240062 henri.m.laakso@student.tut.fi

#include "splitter.hh"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Tuote
{
    string tuotenimi;
    double hinta;

    // palauttaa toden jos nimi "pienempi", kuin toisella structilla
    // tämän operaation voisi tehdä myös structin ulkopuolella
    // muttä tämä on kiva kun tarvitsee tutkia vain nimien järjestystä
    bool operator<(const Tuote& a) const
    {
        return tuotenimi < a.tuotenimi;
    }
};

// Lähes koko ohjelma on mainin sisällä, sillä eri funktioiksi eritteleminen ei poista toistoa
// tai muutenkaan optimoi kirjoitusta ja yleisesti ohjelman kulku on aika selkeää,
// vaikka jotkin rakenteet ovatkin hieman monimutkaisia käsitellä.
// Tietorakenteeni koostuu vektroreista mapeissa, jotka sijaitsevat vektorissa.

int main()
{
    map<string, map<string, vector<Tuote>>> kauppaketjut;
    map<string, map<string, vector<Tuote>>>::iterator ketjuiter;
    map<string, vector<Tuote>>::iterator kauppaiter;
    Splitter splitter;
    string rivi;

    ifstream tiedosto("tuotetiedot.txt");
    if(not tiedosto)
    {
        cout << "Virhe: syötetiedostoa ei saatu luettua." << endl;
        return 0;
    }
    try
    {
        while(getline(tiedosto, rivi))
        {
            string kauppaketju = "";
            string kauppa = "";
            Tuote tuote;

            splitter.aseta_paloiteltava_merkkijono(rivi);
            splitter.paloittele(';');
            kauppaketju = splitter.hae_kentta(0);
            kauppa = splitter.hae_kentta(1);

            if (kauppaketjut.find(kauppaketju) != kauppaketjut.end())
            {
                if(kauppaketjut.at(kauppaketju).find(kauppa) != kauppaketjut.at(kauppaketju).end())
                {
                    bool olemassa = false;
                    for(unsigned int i = 0; i < kauppaketjut.at(kauppaketju).at(kauppa).size(); i++)
                    {
                        if(kauppaketjut.at(kauppaketju).at(kauppa)[i].tuotenimi == splitter.hae_kentta(2))
                        {
                            if(splitter.hae_kentta(3) != "loppu")
                            {
                                kauppaketjut.at(kauppaketju).at(kauppa)[i].hinta = stod(splitter.hae_kentta(3));
                            }
                            else
                            {
                                kauppaketjut.at(kauppaketju).at(kauppa)[i].hinta = -1;
                            }
                            olemassa = true;
                        }
                    }
                    if(olemassa != true)
                    {
                        tuote.tuotenimi = splitter.hae_kentta(2);
                        if(splitter.hae_kentta(3) != "loppu")
                        {
                            tuote.hinta = stod(splitter.hae_kentta(3));
                        }
                        else
                        {
                            tuote.hinta = -1;
                        }
                        kauppaketjut.at(kauppaketju).at(kauppa).push_back(tuote);
                    }
                }
                else
                {
                    vector<Tuote> tuotteet;

                    tuote.tuotenimi = splitter.hae_kentta(2);
                    if(splitter.hae_kentta(3) != "loppu")
                    {
                        tuote.hinta = stod(splitter.hae_kentta(3));
                    }
                    else
                    {
                        tuote.hinta = -1;
                    }
                    tuotteet.push_back(tuote);
                    kauppaketjut.at(kauppaketju).insert({kauppa, tuotteet});
                }
            }
            else
            {
                vector<Tuote> tuotteet;

                tuote.tuotenimi = splitter.hae_kentta(2);
                if(splitter.hae_kentta(3) != "loppu")
                {
                    tuote.hinta = stod(splitter.hae_kentta(3));
                }
                else
                {
                    tuote.hinta = -1;
                }
                tuotteet.push_back(tuote);
                map<string, vector<Tuote>> kaupat = {{kauppa, tuotteet}};
                kauppaketjut.insert({kauppaketju, kaupat});
            }
        }
    }
    catch(...)
    {
        cout << "Virhe: syötetiedostoa ei saatu luettua." << endl;
        return 0;
    }
    tiedosto.close();

    while(true)
    {
        cout << "tuotehaku> ";
        getline(cin, rivi);
        splitter.aseta_paloiteltava_merkkijono(rivi);
        splitter.paloittele(' ');

        if(rivi == "lopeta")
        {
            return 0;
        }
        else if(rivi == "kauppaketjut")
        {
            ketjuiter = kauppaketjut.begin();
            while(ketjuiter != kauppaketjut.end())
            {
                cout << ketjuiter->first << endl;
                ++ketjuiter;
            }
        }
        else if(splitter.hae_kentta(0) == "myymalat" && splitter.kenttien_lukumaara() == 2)
        {
            if(kauppaketjut.find(splitter.hae_kentta(1)) == kauppaketjut.end())
            {
                cout << "Virhe: tuntematon kauppaketju." << endl;
            }
            else
            {
                kauppaiter = kauppaketjut.at(splitter.hae_kentta(1)).begin();
                while(kauppaiter != kauppaketjut.at(splitter.hae_kentta(1)).end())
                {
                    cout << kauppaiter->first << endl;
                    ++kauppaiter;
                }
            }
        }
        else if(splitter.hae_kentta(0) == "halvin" && splitter.kenttien_lukumaara() == 2)
        {
            double hinta = -2;
            vector<string> kaupat;

            ketjuiter = kauppaketjut.begin();
            while(ketjuiter != kauppaketjut.end())
            {
                kauppaiter = ketjuiter->second.begin();
                while(kauppaiter != ketjuiter->second.end())
                {
                    for(unsigned int i = 0; i < kauppaiter->second.size(); i++)
                    {
                        if(kauppaiter->second[i].tuotenimi == splitter.hae_kentta(1))
                        {
                            if(hinta == -2)
                            {
                                hinta = kauppaiter->second[i].hinta;
                            }
                            if(hinta == -1 && kauppaiter->second[i].hinta > 0)
                            {
                                hinta = kauppaiter->second[i].hinta;
                                kaupat.push_back(kauppaiter->first);
                            }
                            else if(kauppaiter->second[i].hinta < hinta && kauppaiter->second[i].hinta > 0)
                            {
                                hinta = kauppaiter->second[i].hinta;
                                kaupat.clear();
                                kaupat.push_back(ketjuiter->first + " " + kauppaiter->first);
                            }
                            else if(hinta == kauppaiter->second[i].hinta)
                            {
                                kaupat.push_back(ketjuiter->first + " " + kauppaiter->first);
                            }
                        }
                    }
                    ++kauppaiter;
                }
                ++ketjuiter;
            }
            if(hinta == -2)
            {
                cout << "Tuote ei kuulu valikoimiin." << endl;
            }
            else if(hinta == -1)
            {
                cout << "Tuote on tilapäisesti loppu kaikkialta." << endl;
            }
            else
            {
                cout << setprecision(2) << fixed << hinta << " euroa" << endl;
                for(unsigned int i = 0; i < kaupat.size(); i++)
                {
                    cout << kaupat[i] << endl;
                }
            }
        }
        else if(splitter.hae_kentta(0) == "tuotevalikoima" && splitter.kenttien_lukumaara() == 3)
        {
            if(kauppaketjut.find(splitter.hae_kentta(1)) == kauppaketjut.end())
            {
                cout << "Virhe: tuntematon kauppaketju." << endl;
            }
            else if(kauppaketjut.at(splitter.hae_kentta(1)).find(splitter.hae_kentta(2)) == kauppaketjut.at(splitter.hae_kentta(1)).end())
            {
                cout << "Virhe: tuntematon myymälä." << endl;
            }
            else
            {
                sort(kauppaketjut.at(splitter.hae_kentta(1)).at(splitter.hae_kentta(2)).begin(),
                     kauppaketjut.at(splitter.hae_kentta(1)).at(splitter.hae_kentta(2)).end());
                for(unsigned int i= 0; i < kauppaketjut.at(splitter.hae_kentta(1)).at(splitter.hae_kentta(2)).size(); i++)
                {
                    if(kauppaketjut.at(splitter.hae_kentta(1)).at(splitter.hae_kentta(2))[i].hinta == -1)
                    {
                        cout << kauppaketjut.at(splitter.hae_kentta(1)).at(splitter.hae_kentta(2))[i].tuotenimi << " loppu" << endl;
                    }
                    else
                    {
                        cout << setprecision(2) << fixed << kauppaketjut.at(splitter.hae_kentta(1)).at(splitter.hae_kentta(2))[i].tuotenimi << " "
                            << kauppaketjut.at(splitter.hae_kentta(1)).at(splitter.hae_kentta(2))[i].hinta << endl;
                    }
                }
            }
        }
        else if(rivi == "tuotenimet")
        {
            vector<string> tuotteet;

            ketjuiter = kauppaketjut.begin();
            while(ketjuiter != kauppaketjut.end())
            {
                kauppaiter = ketjuiter->second.begin();
                while(kauppaiter != ketjuiter->second.end())
                {
                    for(unsigned int i = 0; i < kauppaiter->second.size(); i++)
                    {
                        if(find(tuotteet.begin(),tuotteet.end(), kauppaiter->second[i].tuotenimi) == tuotteet.end())
                        {
                            tuotteet.push_back(kauppaiter->second[i].tuotenimi);
                        }
                    }
                    ++kauppaiter;
                }
                ++ketjuiter;
            }
            sort(tuotteet.begin(), tuotteet.end());
            for(unsigned int i = 0; i < tuotteet.size(); i++)
            {
                cout << tuotteet[i] << endl;
            }
        }
        else
        {
            cout << "Virhe: tuntematon komento." << endl;
        }
    }
}
