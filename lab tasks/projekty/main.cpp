#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> ile_wchodzi;
vector <int> ile_programistow;
vector <vector<int>> krawedzie;

void makeVectors(int n){
    for (int i = 0; i < n; i++){
        ile_wchodzi.push_back(0);
        ile_programistow.push_back(0);
        krawedzie.push_back(*new vector<int>);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m, k;
    int a, b;
    int result = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> myqueue;
    cin >> n >> m >> k;
    makeVectors(n);
    for (int i = 0; i < n; i++)
        cin >> ile_programistow[i];
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        krawedzie[b-1].push_back(a-1);
        ile_wchodzi[a-1]++;
    }
    for (int i = 0; i < n; i++){
        if (ile_wchodzi[i] == 0)
            myqueue.push({ile_programistow[i], i});
    }
    for (int i = 0; i < k; i++){
        pair<int, int> p = myqueue.top();
        myqueue.pop();
        result = max (result, p.first);
        for (unsigned j = 0; j < krawedzie[p.second].size(); j++){
            int next = krawedzie[p.second][j];
            ile_wchodzi[next]--;
            if (ile_wchodzi[next] == 0)
                myqueue.push({ile_programistow[next], next});
        }
    }
    cout << result << endl;
    return 0;
}
