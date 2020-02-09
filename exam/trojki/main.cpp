#include <iostream>
#include <vector>

using namespace std;

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  vector<long long> ile, ile2;
  ile.resize(11);
  ile2.resize(11);
  int n;
  int a;
  for (int i = 0; i < 11; i++){
      ile[i] = 0L;
      ile2[i] = 0L;
    }
  long long result = 0L;
  ile[0] = 1;
  ile2[0] = 1;
  cin >> n;
  for (int i = 0; i < n; i++){
      cin >> a;
      if (i >= 2)
        result += ile2[a];
      for (int j = a + 1; j <= 10; j++)
        ile2[j] += ile[j-a];
      ile[a]++;
    }
  cout << result << endl;
  return 0;
}
