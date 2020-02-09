#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_N = 1000001;
const int MAX_PRICE = 1e9;

int even_highest_price[MAX_N], even_lowest_price[MAX_N];
int odd_highest_price[MAX_N], odd_lowest_price[MAX_N];

int main()
{
    /**
     * Tablice even/odd_highest_price przechowują na i-tym miejscu
     * parzystą/nieparzystą najwyższą cenę produktu nie droższego niż
     * i-ty najdroższy produkt. Analogicznie tablice even/odd_lowest_price
     * przechowują na i-tym miejscu najtańszą cenę spośród i najdroższych
     * produktów.
     */
    ios_base::sync_with_stdio(0);
    int n,m,k;
    long long int prices[MAX_N];
    int odd_price_count = 0;

    cin >> n;

    for (int i = n; i > 0; i--)
        cin >> prices[i];

    even_highest_price[n] = odd_highest_price[n] = -1;

    /*
     * Tworzenie tablic even/odd_highest_price
     */
    for (int i = n - 1; i > 0; i--){
        if (prices[i+1] % 2 == 0){
            even_highest_price[i] = max(prices[i+1], (long long)even_highest_price[i+1]);
            odd_highest_price[i] = odd_highest_price[i+1];
        }
        else {
            odd_highest_price[i] = max(prices[i+1], (long long)odd_highest_price[i+1]);
            even_highest_price[i] = even_highest_price[i+1];
        }
    }

    even_lowest_price[0] = odd_lowest_price[0] = MAX_PRICE + 1;

    /*
     * Tworzenie tablic even/odd_lowest_price
     */
    for (int i = 1; i <= n; i++){
        if (prices[i] % 2 == 0){
            even_lowest_price[i] = min(prices[i], (long long)even_lowest_price[i-1]);
            odd_lowest_price[i] = odd_lowest_price[i-1];
        }
        else {
            odd_lowest_price[i] = min(prices[i], (long long)odd_lowest_price[i-1]);
            even_lowest_price[i] = even_lowest_price[i-1];
            odd_price_count ++;
        }
    }

    /*
     * Prices[i] przechowuje łączną cenę i najdroższych produktów
     */
    for (int i = 2; i <= n; i++)
        prices[i] += prices[i-1];

    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> k;
        if (n == k){
            if (prices[k] % 2 == 0)
                cout << -1 << endl;
            else
                cout << prices[k] << endl;
        }
        else if (odd_price_count == 0 ||
                 (odd_price_count == n && prices[k] % 2 == 0)){
            cout << -1 << endl;
        }
        else if (prices[k] % 2 == 1) {
            cout << prices[k] << endl;
        }
        else if (odd_lowest_price[k] > MAX_PRICE || even_highest_price[k] == -1){
            cout << prices[k] - even_lowest_price[k] + odd_highest_price[k] << endl;
        }
        else if (even_lowest_price[k] > MAX_PRICE || odd_highest_price[k] == -1) {
            cout << prices[k] - odd_lowest_price[k] + even_highest_price[k] << endl;
        }
        else {
            cout << prices[k] + max(even_highest_price[k] - odd_lowest_price[k],
                                    odd_highest_price[k] - even_lowest_price[k]) << endl;
        }
    }
    return 0;
}
