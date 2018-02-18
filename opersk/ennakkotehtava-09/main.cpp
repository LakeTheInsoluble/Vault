// Henri Laakso
// 240062
// henri.m.laakso@student.tut.fi

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

    cout << "lisätään numerot 0 - 100" << endl;
    for(unsigned int i = 0; i <= 100; i++) {
        pino.push_front(i);
    }
    while(pino.pop_front(temp)) {
        cout << temp << endl;
    }
}
