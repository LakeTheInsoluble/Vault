// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

// En nyt ole ihan varma tämän toteutuksen toiminnasta muistivuotojen suhteen.
// Jos mahdollista haluaisin jonkinlaisen selityksen tuon reallocaation toiminnasta, ja siitä miten se olisi pitänyt tehdä, jos tämä ei ole sopiva tapa.

#include "pino.h"

#include <iostream>

using namespace std;

int main()
{
    int temp = 0;
    Pino pino;

    pino.push_front(3);
    if(pino.pop_front(temp)) {
        cout << temp << endl;
    }
    pino.push_front(2);
    cout << "tyhjä " << pino.empty() << endl;
    pino.push_front(1);
    while(pino.pop_front(temp)) {
        cout << temp << endl;
    }
    cout << "tyhjä " <<  pino.empty() << endl;

    cout << "lisätään numerot 0 - 99" << endl;
    for(unsigned int i = 0; i < 100; i++) {
        cout << "lisätään " << i << endl;
        pino.push_front(i);
    }
    cout << "lisätty" << endl;
    while(pino.pop_front(temp)) {
        cout << temp << endl;
    }
    cout << "loppu" << endl;
}
