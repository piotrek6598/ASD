#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string str;
    int last_color = 42;
    int last_position = -1;
    int min_dist;

    cin >> str;

    min_dist = str.length();

    for (int i = 0; i < (int)str.length(); i++){
        if (str[i] != 42){
            if (last_color == 42){
                last_color = str[i];
                last_position = i;
            }
            else if (str[i] == last_color){
                last_position = i;
            }
            else {
                last_color = str[i];
                min_dist = min (min_dist, i - last_position);
                last_position = i;
            }
        }
    }
    cout << str.length() - min_dist + 1 << endl;
    return 0;
}
