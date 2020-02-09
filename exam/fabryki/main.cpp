#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;

vector<vector<int>> maxDist1;
vector<vector<int>> maxDist2;
vector<int> types;
vector<int> results;
vector<vector<int>> graph;

void dfs(int num, int prev){
  if (graph[num].size() == 1 && prev != 0){
      maxDist1[num][types[num]] = 0;
      return;
    }
  for (int i = 0; i < graph[num].size(); i++){
      int next = graph[num][i];
      if (next != prev){
          //cout << "TEST " << next << endl;
          dfs(next, num);
          for (int j = 1; j <= 10; j++) {
              if (maxDist1[next][j] != -1)
                maxDist1[num][j] = max(maxDist1[num][j], maxDist1[next][j] + 1);
            }
        }
    }
  if (maxDist1[num][types[num]] == -1)
    maxDist1[num][types[num]] = 0;
}

void dfs2(int num, int prev){
  if (graph[num].size() == 1 && prev != 0)
    return;
  for (int j = 1; j <= 10; j++){
      int max1 = -1, max2 = -1;
      for (int i = 0; i < graph[num].size(); i++) {
          int next = graph[num][i];
          if (next != prev){
              if (maxDist1[next][j] != -1){
                  if (maxDist1[next][j] + 1 > max1) {
                      max2 = max1;
                      max1 = maxDist1[next][j] + 1;
                    }
                  else if (maxDist1[next][j] + 1 > max2)
                    max2 = maxDist1[next][j] + 1;
                }
              if (max1 != -1){
                  if (max2 != -1){
                      results[j] = max(results[j], max1 + max2);
                    } else if (types[num] == j) {
                      results[j] = max(results[j], max1);
                    }
                }
            }
        }
    }
  for (int i = 0; i < graph[num].size(); i++){
      int next = graph[num][i];
      if (next != prev){
          dfs2(next, num);
        }
    }
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  int a,b;
  cin >> n;
  types.resize(n+1);
  results.resize(11);
  maxDist1.resize(n+1);
  maxDist2.resize(n+1);
  graph.resize(n+1);
  for (int i = 1; i <= n; i++){
      maxDist1[i].resize(11);
      maxDist2[i].resize(11);
      for (int j = 0; j < 11; j++) {
          maxDist1[i][j] = maxDist2[i][j] = -1;
        }
    }
  for (int i = 0; i < 11; i++)
    results[i] = -1;
  for (int i = 1; i <= n; i++)
    cin >> types[i];
  for (int i = 0; i < n - 1; i++){
      cin >> a >> b;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
  dfs(1, 0);/*
  for (int i = 1; i <= n; i++) {
      cout << i << endl;
      for (int j = 1; j <= 2; j++)
        cout << maxDist1[i][j] << " ";
      cout << endl << endl;
    }*/
  dfs2(1, 0);/*
  for (int j = 1; j <= 10; j++)
    cout << results[j] << " ";*/
  int result = 0;
  for (int i = 1; i <= 10; i++)
    result = max(result, results[i]);
  cout << result << endl;
  return 0;
}
