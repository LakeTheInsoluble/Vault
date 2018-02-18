#include <iostream>

using namespace std;

int fibonacci(int numero){
    int a = 0;
    int b = 1;
    int c = 0;

    for(int i = 0; i < numero-1; i++){
        c = b;
        b = a;
        a = b + c;
    }

    return a;
}

int main(int argc, char *argv[])
{
    int montako;

    cout << "Monesko fibonaccin luku tulostetaan? ";
    cin >> montako;

    cout << "Fibonaccin luku numero " << montako << " on: " << fibonacci(montako) << "\n";

    return 0;
}
