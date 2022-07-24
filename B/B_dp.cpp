#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct Rec_dp
{
    //long min;
    size_t ind;
};

vector<Rec_dp> *dp;

struct Node{
    size_t deep = 0;
    size_t parent = 0;
    //long cost;
    vector <size_t> childs;
};

Node *tree;

//void dfs_set_deep(size_t cur, size_t deep_parent)
//{
//    tree[cur].deep = ++deep_parent;
//
//    for(size_t child : tree[cur].childs)
//        dfs_set_deep(child, deep_parent);
//}

void dfs_set_dp(size_t cur)
{
    dp[cur].push_back({tree[cur].parent});

    for(size_t i = 1, h = 2; h < tree[cur].deep; i++, h *= 2)
    {
        Rec_dp prev = dp[dp[cur][i-1].ind][i-1];
        dp[cur].push_back({prev.ind});
    }


    for(size_t child : tree[cur].childs)
        dfs_set_dp(child);
}

int main()
{
    size_t n;

    cin >> n;
    tree = new Node[n+1];
    dp = new vector<Rec_dp>[n+1];

    tree[1].deep = 1;
    //tree[1].cost = LONG_MAX;
    for(size_t i = 2; i <= n; i++)
    {
        size_t parent;
        //long cost;
        cin >> parent;

        tree[i].parent = parent;
        //tree[i].cost = cost;
        tree[i].deep = tree[parent].deep + 1;
        tree[parent].childs.push_back(i);
    }

    //dfs_set_deep(root, 0);

    //for(size_t i = 1; i <= n; i++) cout << i << " " << tree[i].parent << " " << tree[i].deep << endl;

    for(size_t child : tree[1].childs)
        dfs_set_dp(child);

//    for(size_t i = 1; i <= n; i++)
//    {
//        printf("%zu: ", i);
//        for(Rec_dp rec : dp[i])
//        {
//            printf("{%zu} ", rec.ind);
//        }
//        printf("\n");
//    }

    size_t m;
    cin >> m;
    while(m--)
    {
        size_t a, b;
        cin >> a >> b;

        //long min_a = LONG_MAX;
        //long min_b = LONG_MAX;

        if(tree[a].deep > tree[b].deep)
        {
            size_t h = tree[a].deep - tree[b].deep;
            for(size_t i = 0, two = 1; two <= h; two = two << 1, i++)
            {
                if(h & two)
                {
                    Rec_dp res = dp[a][i];
                    a = res.ind;
                    //min_a = MIN(min_a, res.min);
                }

                //printf("%d\n", a);
            }
        }
        else if(tree[b].deep > tree[a].deep)
        {
            size_t h = tree[b].deep - tree[a].deep;
            for(size_t i = 0, two = 1; two <= h; two = two << 1, i++)
            {
                //printf("two = %d\n", two);
                if(h & two)
                {
                    Rec_dp res = dp[b][i];
                    b = res.ind;
                    //min_b = MIN(min_b, res.min);
                }
                //printf("%d\n", b);
            }
        }

        if(a == b)
        {
            cout << a << endl;
            //cout << MIN(min_a, min_b) << endl;
            continue;
        }

        while(true)
        {
            size_t i = dp[a].size();
            if (i == 0)
                break;

            bool find = false;
            while(i--)
            {
                if(dp[a][i].ind != dp[b][i].ind)
                {
                    Rec_dp res_a = dp[a][i];
                    Rec_dp res_b = dp[b][i];

                    a = res_a.ind;
                    b = res_b.ind;

                    //min_a = MIN(min_a, res_a.min);
                    //min_b = MIN(min_b, res_b.min);
                    find = true;
                    break;
                }
            }
            if (!find)
                break;
        }

        //min_a = MIN(min_a, tree[a].cost);
        //min_b = MIN(min_b, tree[b].cost);

        cout << tree[a].parent << endl;
        //cout << MIN(min_a, min_b) << endl;
    }

    delete[] tree;
    delete[] dp;
    return 0;
}

/**
10
1
2
3
4
5
6
7
8
9
1
40
1 2
*/

/**
7
1 2
1 3
2 4
3 5
2 1
2 7
*/
