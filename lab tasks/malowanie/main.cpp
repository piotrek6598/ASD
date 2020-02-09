#include <iostream>
#include <vector>

using namespace std;

static int max_size;

static vector<int> ile_bialych;
static vector<int> co_wstawione; // 1 biale, 0 nic, -1 czarne

void init(int n){
    int size = 1;
    while (size < n)
        size *= 2;
    max_size = size;
    for (int i = 0; i < 2 * max_size; i++){
        ile_bialych.push_back(0);
        co_wstawione.push_back(0);
    }
}

void update(unsigned w){
    while (w != 1){
        w/=2;
        ile_bialych[w] = ile_bialych[2*w] + ile_bialych[2*w+1];
    }
}

void spychaj(unsigned w, int p, int k){
    if (co_wstawione[w] != 0){
        if (co_wstawione[w] == 1)
            ile_bialych[2*w] = ile_bialych[2*w+1] = (k - p + 1)/2;
        else
            ile_bialych[2*w] = ile_bialych[2*w+1] = 0;
        co_wstawione[2*w] = co_wstawione[2*w+1] = co_wstawione[w];
        co_wstawione[w] = 0;
    }
}

void insert(int poczatek, int koniec, int x, unsigned w = 1, int p = 1, int k = max_size){
    if (poczatek <= p && k <= koniec){
        co_wstawione[w] = x;
        if (x == 1)
            ile_bialych[w] = k - p + 1;
        else
            ile_bialych[w] = 0;
        update(w);
    }
    else {
        spychaj(w,p,k);
        int polowa = (p + k) / 2;
        if (poczatek <= polowa)
            insert(poczatek, koniec, x, 2*w, p, polowa);
        if (koniec >= polowa + 1)
            insert(poczatek, koniec, x, 2*w+1, polowa + 1, k);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int n, m;
    int a, b;
    char c;
    cin >> n >> m;
    init(n);
    for (int i = 0; i < m; i++){
        cin >> a >> b >> c;
        if (c == 'C')
            insert(a, b, -1);
        if (c == 'B')
            insert(a, b, 1);
        cout << ile_bialych[1] << endl;
    }
    return 0;
}
