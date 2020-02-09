#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Node {
    int left;
    int right;
    int parent;
    int sibiling;
};

vector<Node> tree;
vector<int> depth;
vector<vector<int>> links;
vector<pair<int, int>> fardown;
vector<pair<int, int>> farup;
int N;

void insert(int v, int left, int right){
    tree[v].left = left;
    tree[v].right = right;
    if (left != -1){
        tree[left].sibiling = right;
        tree[left].parent = v;
    }
    if (right != -1){
        tree[right].sibiling = left;
        tree[right].parent = v;
    }
}

void makeVectors(){
    Node node = {-1,-1,-1,-1};
    vector <int> link;
    pair<int, int> p = {-1,-1};
    for (int i = 0; i <= N; i++){
        depth.push_back(-1);
        tree.push_back(node);
        link.push_back(-1);
        fardown.push_back(p);
        farup.push_back(p);
    }
    for (int j = 0; j <= floor(log2(N)); j++){
        links.push_back(link);
    }
}

pair<int, int> maxPair (pair<int, int> p1, pair<int, int> p2){
    if (p1.first > p2.first)
        return p1;
    else
        return p2;
}

void makeFardown(int v){
    if (v == -1)
        return;
    makeFardown(tree[v].left);
    makeFardown(tree[v].right);
    pair<int, int> p = {0,v};
    if (tree[v].left != -1)
        p = maxPair(p, {fardown[tree[v].left].first + 1, fardown[tree[v].left].second});
    if (tree[v].right != -1)
        p = maxPair(p, {fardown[tree[v].right].first + 1, fardown[tree[v].right].second});
    fardown[v] = p;
    return;
}

void makeFarup(int v){
    if (v == -1)
        return;
    pair<int, int> p = {0,v};
    if (tree[v].parent != -1)
        p = maxPair(p, {farup[tree[v].parent].first + 1, farup[tree[v].parent].second});
    if (tree[v].sibiling != -1)
        p = maxPair(p, {fardown[tree[v].sibiling].first + 2, fardown[tree[v].sibiling].second});
    farup[v] = p;
    makeFarup(tree[v].left);
    makeFarup(tree[v].right);
    return;
}

void countDepthAndLinks (int v, int d){
    if (v == -1)
        return;
    depth[v] = d;
    links[0][v] = tree[v].parent;
    for (int i = 1; i <= floor(log2(N)); i++){
        if (links[i-1][v] == -1)
            links[i][v] = -1;
        else
            links[i][v] = links[i-1][links[i-1][v]];
    }
    countDepthAndLinks(tree[v].left, d + 1);
    countDepthAndLinks(tree[v].right, d + 1);
    return;
}

int ancestor(int v, int h){
    int result = v;
    int i = floor(log2(N));
    int pow2i = 1;
    for (int j = 1; j <= i; j++)
        pow2i *= 2;
    while (h > 0){
        if (pow2i > h){
            i--;
            pow2i/=2;
        }
        else {
            result = links[i][result];
            h -= pow2i;
        }
    }
    return result;
}

int lca (int v, int u){
    int du = depth[u], dv = depth[v];
    if (du < dv){
        v = ancestor(v, dv-du);
        dv = depth[v];
    } else if (du > dv){
        u = ancestor(u, du-dv);
        du = depth[u];
    }
    if (v == u)
        return u;
    int i = floor(log2(N));
    while (i >= 0){
        if (links[i][v] != links[i][u]){
            u = links[i][u];
            v = links[i][v];
        }
        i--;
    }
    return tree[v].parent;
}

int dist (int v, int d){
    pair<int, int> p = maxPair(fardown[v], farup[v]);
    if (d > p.first)
        return -1;
    int l = lca(v, p.second);
    int d1 = depth[v] - depth[l];
    if (d <= d1)
        return ancestor(v, d);
    else
        return ancestor(p.second, p.first - d);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int a,b,m;
    cin >> N;
    makeVectors();
    for (int i = 1; i <= N; i++){
        cin >> a >> b;
        insert(i, a, b);
    }
    countDepthAndLinks(1, 0);
    makeFardown(1);
    makeFarup(1);
    cin >> m;
    for (int i = 1; i <= m; i++){
        cin >> a >> b;
        cout << dist(a,b) << endl;
    }
    return 0;
}
