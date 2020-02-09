#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);

    unsigned players, matches;
    unsigned player;
    vector <string> player_desc;
    cin >> players >> matches;
    for (unsigned i = 0; i < players; i++)
        player_desc.push_back("");
    for (unsigned i = 0; i < matches; i++){
        for (unsigned j = 1; j <= players; j++){
            cin >> player;
            if (j <= (players/2))
                player_desc[player-1] += "1";
            else
                player_desc[player-1] += "2";
        }
    }

    sort(player_desc.begin(), player_desc.end());
    for (unsigned i = 1; i < players; i++){
        if (player_desc[i].compare(player_desc[i-1]) == 0){
            cout << "NIE" << endl;
            return 0;
        }
    }
    cout << "TAK" << endl;
    return 0;
}
