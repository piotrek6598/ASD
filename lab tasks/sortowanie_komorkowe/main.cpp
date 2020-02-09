#include <iostream>
#include <cmath>

using namespace std;

const int M = 1000000000;

int main()
{
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    int sequence [n];
    for (int i = 0; i < n; i++){
        cin >> sequence[i];
    }

    if (n == 1){
        cout << 1 << endl;
        return 0;
    }

    /* Tablica last_left/right[i][j] przechowują liczbę ciągów mod m, takich że
     * sortowanie tworzy podciąg sequence[i],sequence[i+1],...,sequence[j]
     * w których lewy/prawy jest ostatnim elementem ciągu wejściowego
     */
    int last_left[n][n];
    int last_right[n][n];

    // Jednoelementowy podciąg da się otrzymać na jeden sposób z jednoelementowego ciagu
    for (int i = 0; i < n; i++){
        last_left[i][i] = last_right[i][i] = 1;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; i + j + 1 < n; j++){
            if (i == 0){
                if (sequence[j] < sequence[j+1])
                    last_left[j][j+1] = last_right[j][j+1] = 1;
                else
                    last_left[j][j+1] = last_right[j][j+1] = 0;
            }
            else {
                if (sequence[j] < sequence[j+1])
                    last_left[j][i+j+1] = last_left[j+1][i+j+1];
                else
                    last_left[j][i+j+1] = 0;
                if (sequence[i+j+1] > sequence[i+j])
                    last_right[j][i+j+1] = last_right[j][i+j];
                else
                    last_right[j][i+j+1] = 0;
                if (sequence[j] < sequence[i+j+1]){
                    last_left[j][i+j+1] += last_right[j+1][i+j+1];
                    last_left[j][i+j+1] %= M;
                    last_right[j][i+j+1] += last_left[j][i+j];
                    last_right[j][i+j+1] %= M;
                }
            }
        }
    }
    /*
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << "last_left[" << i << "][" << j << "]: " << last_left[i][j] << endl;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << "last_right[" << i << "][" << j << "]: " << last_right[i][j] << endl;
        }
    }
    */
    cout << (last_left[0][n-1] + last_right[0][n-1]) % M << endl;
    return 0;
}
