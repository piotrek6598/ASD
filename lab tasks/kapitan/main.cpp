#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <climits>

using namespace std;

using point = pair<int, int>;
using dist_to = pair<long long, int>;

long long get_dist (const point &first, const point &second){
    return min(abs(first.first - second.first), abs(first.second - second.second));
}

int main()
{
    int n;
    ios_base::sync_with_stdio(0);
    vector<point> islands;
    vector<long long> distance;
    vector<vector<int>> neighbours;
    vector<dist_to> x,y;
    set<point> queue;

    cin >> n;

    for (int i = 0; i < n; i++){
        vector<int> vec;
        point p = {0,0};
        dist_to is = {0,0};
        long long dis = 0;
        islands.push_back(p);
        x.push_back(is);
        y.push_back(is);
        neighbours.push_back(vec);
        distance.push_back(dis);
    }
    for (int i = 0; i < n; i++){
        cin >> islands[i].first >> islands[i].second;
        distance[i] = INT_MAX;
    }
    distance[0] = 0L;
    for (int i = 0; i < n; i++){
        x[i] = {islands[i].first, i};
        y[i] = {islands[i].second, i};
    }
    sort (x.begin(), x.end());
    sort (y.begin(), y.end());
    for (int i = 0; i < n; i++){
        if (i != 0){
            neighbours[x[i].second].push_back(x[i-1].second);
            neighbours[y[i].second].push_back(y[i-1].second);
        }
        if (i != n-1){
            neighbours[x[i].second].push_back(x[i+1].second);
            neighbours[y[i].second].push_back(y[i+1].second);
        }
    }

    queue.insert({distance[0], 0});
    while (true){
        dist_to island = *queue.begin();
        queue.erase(queue.begin());
        if (island.second == n-1)
            break;
        for (int i: neighbours[island.second]){
            long long next_dist = get_dist(islands[island.second], islands[i]) + distance[island.second];
            if (next_dist < distance[i]){
                if (distance[i] == INT_MAX){
                    distance[i] = next_dist;
                    queue.insert({next_dist, i});
                }
                else {
                    queue.erase(queue.find({distance[i], i}));
                    distance[i] = next_dist;
                    queue.insert({distance[i], i});
                }
            }
        }
    }
    cout << distance[n-1] << endl;
    return 0;
}
