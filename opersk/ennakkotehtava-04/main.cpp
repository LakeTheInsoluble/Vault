#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    map<string, vector<string>> tulokset;
    /*tulokset = {
        {"keihäs", {"santeri", "pete", "tuomas"}},
        {"kuula", {"pete", "tomi"}},
        {"seiväs", {"eka"}}
    };*/

    string komento;
    string laji;
    string nimi;

    cout << "Komennot:" << endl << "  lisää" << endl << "  tulosta" << endl << "  lopeta" << endl;

    do
    {
        cout << "> ";
        cin >> komento;
        if(komento == "lisää")
        {
            cout << "Syötä laji: ";
            cin >> laji;
            cout << "Syötä kilpailijan nimi: ";
            cin >> nimi;
            if(tulokset.find(laji) != tulokset.end())
            {
                tulokset.at(laji).push_back(nimi);
            }
            else
            {
                tulokset.insert({laji, {nimi}});
            }
        }
        else if(komento == "tulosta")
        {
            for ( auto tietopari : tulokset ) {
                cout << tietopari.first << endl;
                for(unsigned int i = 0; i < tietopari.second.size(); i++)
                {
                    cout << "  " << i+1 << ". " << tietopari.second[i] << endl;
                }
            }
        }
        else if(komento != "lopeta")
        {
            cout << "Virhe: epäsopiva komento!" << endl;
        }
    } while(komento != "lopeta");

    return 0;
}
