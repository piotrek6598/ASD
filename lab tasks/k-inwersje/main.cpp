#include <iostream>
#include <cmath>

using namespace std;

const int M = 1e9;

const int MAX_SIZE = 32 * 1024;
const int MAX_K = 10;
int suma = 0;

int drzewo [2*MAX_SIZE][MAX_K + 1];

void oblicz(int poczatek, int koniec, int j, int w = 1, int p = 1, int k = MAX_SIZE){
    if (poczatek <= p && koniec >= k){
        suma += drzewo[w][j];
        suma %= M;
        return;
    }
    else {
    int polowa = (p + k) / 2;
    if (poczatek <= polowa)
        oblicz(poczatek, koniec, j, 2 * w, p, polowa);
    if (koniec >= polowa + 1)
        oblicz(poczatek, koniec, j, 2*w + 1, polowa + 1, k);
    }

}

void wstaw (int w, int j, int wartosc){
    drzewo[w][j] = wartosc % M;
    while (w != 1){
        w/=2;
        drzewo[w][j] = (drzewo[2*w][j] + drzewo[2*w+1][j]) % M;
    }
}

void init(){
    for (int i = 0; i < 2 * MAX_SIZE; i++){
        for (int j = 0; j < MAX_K + 1; j++)
            drzewo[i][j] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    int dane[n];
    for (int i = 0; i < n; i++)
        cin >> dane[i];
    init();
    for (int i = 0; i < n; i++){
        int x = dane[i];
        wstaw(MAX_SIZE + x - 1, 1, 1);
        for (int j = 2; j <= k; j++){
            suma = 0;
            oblicz(x+1, MAX_SIZE, j-1);
            wstaw(MAX_SIZE + x - 1, j, suma);
        }
    }
    cout << drzewo[1][k] << endl;
    return 0;
}
