#include <iostream>
#include <cmath>

using namespace std;

const int M = 1e9;
const int MAX_N = 1e6 + 1;

static int ile_el[MAX_N];       // Liczba elementów drzewa o numerze i.
static int poziom [MAX_N][2];   // Liczba drzew o numerze i na pewnym i nastepnym poziomie

int main()
{
    ios_base::sync_with_stdio(0);
    int n, d, ak, bk;
    int str = 1;                // Parametr do sprawdzania który poziom jest aktualny
    cin >> n >> d;
    int dane[n + 1][2];
    ile_el[0] = 1;
    for (int i = 1; i <= n; i++){
        cin >> ak >> bk;
        dane[i][0] = ak;
        dane[i][1] = bk;
        ile_el[i] = (ile_el[ak] + ile_el[bk] + 1) % M;
    }
    for (int i = 0; i <= n; i++){
        poziom[i][0] = 0;
        poziom[i][1] = 0;
    }
    poziom[n][0] = 1;
    // Obliczaenie drzew na kolejnych poziomach
    for (int i = 1; i <= d; i++){
        if (str == 1){
            poziom[0][0] = 0;
            for (int j = 1; j <= n; j++){
                poziom[dane[j][0]][1] += poziom[j][0];
                poziom[dane[j][0]][1] %= M;
                poziom[dane[j][1]][1] += poziom[j][0];
                poziom[dane[j][0]][1] %= M;
                poziom[dane[j][1]][1] %= M;
                poziom[j][0] = 0;
            }
        }
        else {
            poziom[0][1] = 0;
            for (int j = 1; j <= n; j++){
                poziom[dane[j][0]][0] += poziom[j][1];
                poziom[dane[j][0]][0] %= M;
                poziom[dane[j][1]][0] += poziom[j][1];
                poziom[dane[j][0]][0] %= M;
                poziom[dane[j][1]][0] %= M;
                poziom[j][1] = 0;
            }
        }
        str *= -1;
    }
    long long int ans = 0;
    if (str == -1) {
        for (int i = 0; i <= n; i++){
            ans += (static_cast<long long>(ile_el[i]) * static_cast<long long>(poziom[i][1])) % M;
            ans %= M;
        }
    }
    else {
        for (int i = 0; i <= n; i++){
            ans += (static_cast<long long>(ile_el[i]) * static_cast<long long>(poziom[i][0])) % M;
            ans %= M;
        }
    }
    cout << ans % M << endl;
    return 0;
}
