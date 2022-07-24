#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<size_t> *dp;

struct Node{
    size_t deep = 0;
    size_t parent = 0;
    vector <size_t> childs;
};

Node *tree;

void dfs_set_deep(size_t cur, size_t deep_parent)
{
    tree[cur].deep = ++deep_parent;

    for(size_t child : tree[cur].childs)
        dfs_set_deep(child, deep_parent);
}

void dfs_set_dp(size_t cur)
{
    dp[cur].push_back(tree[cur].parent);

    for(size_t i = 1, h = 2; h < tree[cur].deep; i++, h *= 2)
        dp[cur].push_back(dp[dp[cur][i-1]][i-1]);

    for(size_t child : tree[cur].childs)
        dfs_set_dp(child);
}

int main() {

    size_t n;

    cin >> n;
    tree = new Node[n+1];
    dp = new vector<size_t>[n+1];

    size_t root;

    for(size_t i = 1; i <= n; i++)
    {
        size_t parent;
        cin >> parent;
        if(!parent)
            root = i;
        tree[i].parent = parent;
        tree[parent].childs.push_back(i);
    }


    dfs_set_deep(root, 0);

    //for(size_t i = 1; i <= n; i++) cout << i << " " << tree[i].parent << " " << tree[i].deep << endl;

    for(size_t child : tree[root].childs)
        dfs_set_dp(child);

    for(size_t i = 1; i <= n; i++)
    {
        printf("%zu: ", i);
        for(size_t p : dp[i])
        {
            printf("%zu ", p);
        }
        printf("\n");
    }

    delete[] tree;
    delete[] dp;
    return 0;
}
