#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct Rec_dp
{
    long long min;
    size_t ind;
};

vector<Rec_dp> *dp;

struct Node{
    size_t deep = 0;
    size_t parent = 0;
    long long cost;
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
    dp[cur].push_back({tree[cur].cost, tree[cur].parent});

    for(size_t i = 1, h = 2; h < tree[cur].deep; i++, h *= 2)
    {
        Rec_dp prev = dp[dp[cur][i-1].ind][i-1];
        dp[cur].push_back({MIN(dp[cur][i-1].min, prev.min), prev.ind});
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
    tree[1].cost = LONG_MAX;
    for(size_t i = 2; i <= n; i++)
    {
        size_t parent;
        long long cost;
        //cin >> parent >> cost;
        scanf("%zu %lld", &parent, &cost);

        tree[i].parent = parent;
        tree[i].cost = cost;
        tree[i].deep = tree[parent].deep + 1;
        tree[parent].childs.push_back(i);
    }

    //dfs_set_deep(root, 0);

    //for(size_t i = 1; i <= n; i++) cout << i << " " << tree[i].parent << " " << tree[i].deep << " " << tree[i].cost << endl;

    for(size_t child : tree[1].childs)
        dfs_set_dp(child);

//    for(size_t i = 1; i <= n; i++)
//    {
//        printf("%zu: ", i);
//        for(Rec_dp rec : dp[i])
//        {
//            printf("{%ld %zu} ", rec.min, rec.ind);
//        }
//        printf("\n");
//    }

    size_t m;
    cin >> m;
    while(m--)
    {
        size_t a, b;
        //cin >> a >> b;

        scanf("%zu %zu", &a, &b);

        long long min_a = LONG_MAX;
        long long min_b = LONG_MAX;

        if(tree[a].deep > tree[b].deep)
        {
            size_t h = tree[a].deep - tree[b].deep;
            size_t two = 1;
            size_t i = 0;
            for(size_t hh = h; hh > 0; hh = hh >> 1, two = two << 1, i++);

            for(; two > 0; two = two >> 1, i--)
            {
                if(h & two)
                {
                    Rec_dp res = dp[a][i];
                    a = res.ind;
                    min_a = MIN(min_a, res.min);
                }
            }

//            while(tree[a].deep > tree[b].deep)
//            {
//                min_a = MIN(min_a, tree[a].cost);
//                a = tree[a].parent;
//            }
        }
        else if(tree[b].deep > tree[a].deep)
        {
            size_t h = tree[b].deep - tree[a].deep;

            size_t two = 1;
            size_t i = 0;
            for(size_t hh = h; hh > 0; hh = hh >> 1, two = two << 1, i++);

            for(; two > 0; two = two >> 1, i--)
            {
                if(h & two)
                {
                    Rec_dp res = dp[b][i];
                    b = res.ind;
                    min_b = MIN(min_b, res.min);
                }
            }

//            while(tree[b].deep > tree[a].deep)
//            {
//                min_b = MIN(min_b, tree[b].cost);
//                b = tree[b].parent;
//            }
        }

        if(a == b)
        {
            //cout << "lca is =" << a << endl;
            //cout << MIN(min_a, min_b) << endl;
            printf("%lld\n", MIN(min_a, min_b));
            continue;
        }

        while(tree[a].parent != tree[b].parent)
        {

//            min_a = MIN(min_a, tree[a].cost);
//            a = tree[a].parent;
//            min_b = MIN(min_b, tree[b].cost);
//            b = tree[b].parent;

//            size_t i = dp[a].size();
//            if (i == 0)
//                break;
//
//            bool find = false;
//            for(i -= 1; i > 0; i--)
//            {
//                if(dp[a][i].ind != dp[b][i].ind)
//                {
//                    size_t a_old = a, b_old = b;
//                    a = dp[a][i].ind;
//                    b = dp[b][i].ind;
//                    while(a != a_old)
//                    {
//                        min_a = MIN(min_a, tree[a_old].cost);
//                        a_old = tree[a_old].parent;
//
//                        min_b = MIN(min_b, tree[b_old].cost);
//                        b_old = tree[b_old].parent;
//                    }
//
//                    find = true;
//                    break;
//                }
//            }
//            if(find)
//                continue;
//            else
//            {
//                if(dp[a][i].ind != dp[b][i].ind)
//                {
//                    size_t a_old = a, b_old = b;
//                    a = dp[a][i].ind;
//                    b = dp[b][i].ind;
//                    while(a != a_old)
//                    {
//                        min_a = MIN(min_a, tree[a_old].cost);
//                        a_old = tree[a_old].parent;
//
//                        min_b = MIN(min_b, tree[b_old].cost);
//                        b_old = tree[b_old].parent;
//                    }
//                }
//                else
//                    break;
//            }



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

                    min_a = MIN(min_a, res_a.min);
                    min_b = MIN(min_b, res_b.min);
                    find = true;
                    break;
                }
            }
            if (!find)
                break;
        }

        min_a = MIN(min_a, tree[a].cost);
        min_b = MIN(min_b, tree[b].cost);

//        while(a != b)
//        {
//            min_a = MIN(min_a, tree[a].cost);
//            a = tree[a].parent;
//            min_b = MIN(min_b, tree[b].cost);
//            b = tree[b].parent;
//        }

        //cout << "lca is =" << tree[a].parent << endl;
        //cout << MIN(min_a, min_b) << endl;
        printf("%lld\n", MIN(min_a, min_b));
    }

    delete[] tree;
    delete[] dp;
    return 0;
}

/**
7
1 2
1 3
2 4
3 5
2 1
2 7
*/
