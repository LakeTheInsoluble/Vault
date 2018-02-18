#include <iostream>
#include <iomanip>
#include <regex>

using namespace std;

int main()
{
    string rivi;
    smatch tulos;
    regex PVM_REGEX(
                "([[:digit:]]{1,2})"
                "(.)"
                "([[:digit:]]{1,2})"
                "(.)"
                "([[:digit:]]{1,4})"
                );

    while(1) {
        cout << "Anna päivämäärä: ";
        getline(cin, rivi);
        if(regex_match(rivi, tulos, PVM_REGEX)) {
            cout << tulos[5] << "-" << setfill('0') << setw(2) << tulos[3] << "-" << setw(2) << tulos[1] << endl;
        } else {
            cout << "Ei löytynyt" << endl;
        }
    }
}
