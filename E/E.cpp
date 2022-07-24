#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct Rec_dp
{
    size_t ind;
};

vector<Rec_dp> *dp;

struct Node{
    size_t deep = 0;
    size_t parent = 0;
    vector <size_t> childs;
};

Node *tree;

struct Path{
    size_t a, b;
    size_t lca;
};

Path *paths;

void dfs_make_tree(size_t cur, size_t deep_parent)
{
    tree[cur].deep = ++deep_parent;

    for(size_t child : tree[cur].childs)
    {
        tree[child].childs.erase(find(tree[child].childs.begin(), tree[child].childs.end(), cur));
        tree[child].parent = cur;
        dfs_make_tree(child, deep_parent);
    }
}

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

struct OC
{
    size_t open = 0;
    size_t close = 0;

    OC &operator +=(const OC &second)
    {
        open += second.open;
        close += second.close;

        return *this;
    }
};


OC *color;

size_t k = 0;

OC dfs_color(size_t cur)
{
    OC oc;
    for(size_t child : tree[cur].childs)
        oc += dfs_color(child);

    //oc.open += color[cur].open;
    oc += color[cur];

    if(oc.open == oc.close)
        k++;

    //oc.close += color[cur].close;

    //printf("%zu - %zu %zu\n", cur, oc.open, oc.close);

    return oc;
}

int main()
{
    size_t n;

    cin >> n;
    tree = new Node[n+1];
    dp = new vector<Rec_dp>[n+1];

    tree[1].deep = 1;
    for(size_t i = 1; i < n; i++)
    {
        size_t a, b;
        cin >> a >> b;

        tree[b].childs.push_back(a);
        tree[a].childs.push_back(b);
    }

    dfs_make_tree(1, 0);

    //for(size_t i = 1; i <= n; i++) cout << i << " " << tree[i].parent << " " << tree[i].deep << endl;

    for(size_t child : tree[1].childs)
        dfs_set_dp(child);


    size_t m;
    cin >> m;

    paths = new Path[m];
    color = new OC[n+1];
    for(size_t p = 0; p < m; p++)
    {
        size_t a, b;
        cin >> a >> b;

        paths[p] = {a, b, 0};
        color[a].open++;
        color[b].open++;

        if(tree[a].deep > tree[b].deep)
        {
            size_t h = tree[a].deep - tree[b].deep;
            for(size_t i = 0, two = 1; two <= h; two = two << 1, i++)
            {
                if(h & two)
                {
                    Rec_dp res = dp[a][i];
                    a = res.ind;
                }
            }
        }
        else if(tree[b].deep > tree[a].deep)
        {
            size_t h = tree[b].deep - tree[a].deep;
            for(size_t i = 0, two = 1; two <= h; two = two << 1, i++)
            {
                if(h & two)
                {
                    Rec_dp res = dp[b][i];
                    b = res.ind;
                }
            }
        }

        if(a == b)
        {
            paths[p].lca = a;
            //cout << a << endl;
            //cout << MIN(min_a, min_b) << endl;
            color[a].close += 1;
            color[a].open--;
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

                    find = true;
                    break;
                }
            }
            if (!find)
                break;
        }

        paths[p].lca = tree[a].parent;
        color[tree[a].parent].close += 2;
        //cout << tree[a].parent << endl;
        //cout << MIN(min_a, min_b) << endl;
    }

//    for(size_t i = 0; i < m; i++)
//    {
//        printf("%zu: ", i);
//        Path path = paths[i];
//        printf("{%zu %zu - %zu}\n", path.a, path.b, path.lca);
//    }

//    for(size_t i = 1; i < n+1; i++)
//        color[i] = false;
//    color[0] = true;
//
//    size_t k = 0;
//
//    for(size_t i = 0; i < m; i++)
//    {
//        {
//            size_t a = paths[i].a;
//            while(a != paths[i].lca)
//            {
//                if(!color[a])
//                {
//                    color[a] = true;
//                    k++;
//                }
//                a = tree[a].parent;
//            }
//        }
//        {
//            size_t b = paths[i].b;
//            while(b != paths[i].lca)
//            {
//                if(!color[b])
//                {
//                    color[b] = true;
//                    k++;
//                }
//                b = tree[b].parent;
//            }
//        }
//    }

    for(size_t child : tree[1].childs)
        dfs_color(child);

    cout << k;

    delete[] tree;
    delete[] dp;
    delete[] paths;
    delete[] color;
    return 0;
}


/**
7
1 4
4 3
5 2
5 6
7 5
2 4
3
1 7
2 4
7 6

7
1 4
4 3
5 2
5 6
7 5
2 4
2
2 7
7 6
**/


/*
 * quick start
cd 2sem_AlgoLab_3\E\build
..\..\run_cmake\run

 * set
mkdir build & cd build & cmake -G "MinGW Makefiles" ..

* build and run
cmake --build . && (echo START & C)
echo return code: %errorlevel%

* or
..\..\run_cmake\run

* move
cd 2sem_DM_1\C\build
cd 2sem_DM_1\C
cd C\build

* update run_cmake
git submodule update --remote
*/
