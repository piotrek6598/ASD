#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int M = 1000000007;

struct Node {
    Node *parent;
    long long countRR;
    long long countRG;
    long long countGR;
    long long countGG;
    int size;          // All subtree.
    int reversed;
    int rome;
    Node *children[2];
};

Node *romeNode;
Node *galNode;
Node *root;
Node *nullNode;

vector <int> input;

void recountNode(Node *result, Node *left, Node *right){
    long long countRR, countRG, countGR, countGG;
    countRR = (left->countRR + right->countRR) % M;
    countRR += left->countRR * (right->countRR + right->countGR);
    countRR %= M;
    countRR += left->countRG * right->countRR;
    countRR %= M;

    countRG = (left->countRG + right->countRG) % M;
    countRG += left->countRR * (right->countRG + right->countGG);
    countRG %= M;
    countRG += left->countRG * right->countRG;
    countRG %= M;

    countGR = (left->countGR + right->countGR) % M;
    countGR += left->countGR * (right->countRR + right->countGR);
    countGR %= M;
    countGR += left->countGG * right->countRR;
    countGR %= M;

    countGG = (left->countGG + right->countGG) % M;
    countGG += left->countGR * (right->countGG + right->countRG);
    countGG %= M;
    countGG += left->countGG * right->countRG;
    countGG %= M;

    result->countRR = countRR;
    result->countRG = countRG;
    result->countGR = countGR;
    result->countGG = countGG;
}

void pushDown(Node *node){
    if (node->reversed){
        swap(node->children[0], node->children[1]);
        swap(node->countGR, node->countRG);
        node->children[0]->reversed ^= 1;
        node->children[1]->reversed ^= 1;
        node->reversed = 0;
    }
}

void update(Node *node){
    if (node->children[0] != nullNode)
        pushDown(node->children[0]);
    if (node->children[1] != nullNode)
        pushDown(node->children[1]);
    node->size = node->children[0]->size + node->children[1]->size + 1;
    if (node->rome)
        recountNode(node, node->children[0], romeNode);
    else if (node->rome == 0)
        recountNode(node, node->children[0], galNode);
    else
        recountNode(node, node->children[0], nullNode);
    recountNode(node, node, node->children[1]);
}

void rotate(Node *node, int c){
    Node *parent = node->parent;
    //pushDown(parent);
    //pushDown(node);
    parent->children[!c] = node->children[c];
    if (node->children[c] != nullNode)
        node->children[c]->parent = parent;
    node->parent = parent->parent;
    if (parent->parent != nullNode){
        if (parent->parent->children[0] == parent)
            parent->parent->children[0] = node;
        else
            parent->parent->children[1] = node;
    }
    node->children[c] = parent;
    parent->parent = node;
    update(parent);
    if (root == parent)
        root = node;
}

void splay(Node *node, Node *newParent){
    pushDown(node);
    while (node->parent != newParent){
        Node *parent = node->parent;
        if (parent->parent == newParent) {
            if (node->parent->children[0] == node)
                rotate(node, 1);
            else
                rotate(node, 0);
        } else {
            Node *grandparent = parent->parent;
            if (grandparent->children[0] == parent){
                if (parent->children[0] == node){
                    rotate(parent, 1);
                    rotate(node, 1);
                }
                else {
                    rotate(node, 0);
                    rotate(node, 1);
                }
            }
            else {
                if (parent->children[1] == node){
                    rotate(parent, 0);
                    rotate(node, 0);
                }
                else {
                    rotate(node, 1);
                    rotate(node, 0);
                }
            }
        }
    }
    update(node);
}

void findAndSetBelow(int beg, Node *parent){
    Node *result = root;
    int left = beg + 1;
    while (true){
        pushDown(result);
        if (left == result->children[0]->size + 1)
            break;
        if (left <= result->children[0]->size){
            result = result->children[0];
        }
        else {
            left -= result->children[0]->size + 1;
            result = result->children[1];
        }
    }
    splay(result, parent);
}

Node* getInterval(int beg, int end){
    findAndSetBelow(beg - 1, nullNode);
    findAndSetBelow(end + 1, root);
    return root->children[1]->children[0];
}

void reverseInterval(int beg, int end){
    Node *temp = getInterval(beg, end);
    temp->reversed ^= 1;
    splay(temp, nullNode);
}

Node* build(int beg, int end, Node *prev){
    if (beg > end)
        return nullNode;
    int half = (beg + end)/2;
    Node *node = new Node;
    node->countGG = node->countGR = node->countRG = node->countRR = node->reversed = 0;
    node->parent = prev;
    node->size = 1;
    node->rome = input[half];
    if (input[half])
        node->countRR = 1;
    else
        node->countGG = 1;
    node->children[0] = build(beg, half - 1, node);
    node->children[1] = build(half + 1, end, node);
    update(node);
    return node;
}

void printResult(Node *node){
    long long result;
    result = (node->countRR + node->countRG + node->countGR + node->countGG) % M;
    cout << result << endl;
}

void makeNodes(){
    romeNode = new Node;
    romeNode->countRR = 1;
    romeNode->countRG = romeNode->countGR = romeNode->countGG = 0;
    galNode = new Node;
    galNode->countGG = 1;
    galNode->countGR = galNode->countRG = galNode->countRR = 0;
    nullNode = new Node;
    nullNode->countGG = nullNode->countGR = nullNode->countRG = nullNode->countRR = 0;
    nullNode->children[0] = nullNode->children[1] = nullNode->parent = nullptr;
    nullNode->reversed = nullNode->rome = nullNode->size = 0;
    root = new Node;
    root->countGG = root->countGR = root->countRG = root->countRR = 0;
    root->children[0] = root->children[1] = root->parent = nullNode;
    root->reversed = 0;
    root->rome = -1;
    root->size = 1;
}

void init(int n){
    makeNodes();
    root->children[1] = new Node;
    root->children[1]->children[0] = root->children[1]->children[1] = nullNode;
    root->children[1]->countGG = root->children[1]->countGR = 0;
    root->children[1]->countRG = root->children[1]->countRR = 0;
    root->children[1]->reversed = 0;
    root->children[1]->rome = -1;
    root->children[1]->size = 1;
    root->children[1]->parent = root;
    root->children[1]->children[0] = build(1, n, root->children[1]);
    splay(root->children[1]->children[0], nullNode);
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, querry, beg, end;
    char c;
    string s;
    input.push_back(1);
    cin >> n >> querry;
    cin >> s;
    for (unsigned i = 0; i < s.size(); i++)
        input.push_back(s[i] == 'R');
    init(n);
    for (int i = 0; i < querry; i++){
        cin >> c >> beg >> end;
        if (c == '?'){
            Node *temp = getInterval(beg, end);
            printResult(temp);
        }
        else {
            reverseInterval(beg, end);
        }
    }
    return 0;
}
