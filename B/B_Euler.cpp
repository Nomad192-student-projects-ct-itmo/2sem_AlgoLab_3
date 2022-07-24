#include <cstdio>

#include <iostream>
#include <vector>

using namespace std;

#define _DEBUG
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

class Tree
{
private:
    typedef unsigned long long type_tree;
#define TREE_SP "llu"
#define MAX_VAL (0xffffffffffffffff)

public:
    explicit Tree(size_t n)
    {
        for(la = 1; la < n; la*=2);
        data = new Element [rl = 2*la];
        for (size_t i = 0; i < rl; i++)
        {
            data[i].fd.asv = -1;
            data[i].fd.min = {0, 0};
            data[i].left = i - la;
            data[i].right = i - la + 1;
        }
        this->n = n;
        current_add = 0;
    }
    ~Tree()
    {
        delete[] data;
    }

    struct Minimum
    {
        type_tree result;
        size_t ind;

        bool operator <(const Minimum &second) const
        {
            return result < second.result;
        }
    };

private:
    typedef struct sub_element_t
    {
        long long asv;
        Minimum min;
    } Sub_Element;
    typedef struct element_t
    {
        Sub_Element fd;
        size_t left;
        size_t right;
    } Element;

    size_t rl;
    size_t la;
    Element *data;
    size_t n;
    size_t current_add;
    Minimum min_assign_rq(size_t el, size_t l, size_t r)
    {
        if(data[el].fd.asv != -1)
        {
            return {(type_tree)data[el].fd.asv, el};
        }

        if(data[el].left == l && data[el].right == r)
        {
            //cout << data[el].fd.min.result << " " << data[el].fd.min.ind << std::endl;
            return data[el].fd.min;
        }

        Minimum result;
        if(l < data[el*2].right && r > data[el*2 + 1].left)
        {
            Minimum left_min = min_assign_rq(el*2, MAX(l, data[el*2].left), MIN(r, data[el*2].right));
            Minimum right_min = min_assign_rq(el*2 + 1, MAX(l, data[el*2 + 1].left), MIN(r, data[el*2 + 1].right));
            result = MIN(left_min, right_min);
        }
        else if(l < data[el*2].right)
        {
            result = min_assign_rq(el*2, MAX(l, data[el*2].left), MIN(r, data[el*2].right));
        }
        else //if (r > data[el*2 + 1].left)
        {
            result =  min_assign_rq(el*2 + 1, MAX(l, data[el*2 + 1].left), MIN(r, data[el*2 + 1].right));
        }
        return result;
    }
//    void set_assign_rq(size_t el, size_t l, size_t r, type_tree v)
//    {
//        if(data[el].left == l && data[el].right == r)
//        {
//            data[el].fd.asv = (long long)v;
//            data[el].fd.min = v;
//            return;
//        }
//
//        if(data[el].fd.asv != -1)
//        {
//            data[el*2].fd.asv =  data[el].fd.asv;
//            data[el*2].fd.min =  data[el].fd.min;
//            data[el*2 + 1].fd.asv =  data[el].fd.asv;
//            data[el*2 + 1].fd.min =  data[el].fd.min;
//            data[el].fd.asv = -1;
//        }
//
//        if(v < data[el].fd.min)
//        {
//            data[el].fd.min = v;
//        }
//
//        if(l < data[el*2].right && r > data[el*2 + 1].left)
//        {
//            set_assign_rq(el*2, MAX(l, data[el*2].left), MIN(r, data[el*2].right), v);
//            set_assign_rq(el*2 + 1, MAX(l, data[el*2 + 1].left), MIN(r, data[el*2 + 1].right), v);
//        }
//        else if(l < data[el*2].right)
//        {
//            set_assign_rq(el*2, MAX(l, data[el*2].left), MIN(r, data[el*2].right), v);
//        }
//        else //if (r > data[el*2 + 1].left)
//        {
//            set_assign_rq(el*2 + 1, MAX(l, data[el*2 + 1].left), MIN(r, data[el*2 + 1].right), v);
//        }
//
//        data[el].fd.min = MIN(data[el*2].fd.min, data[el*2 + 1].fd.min);
//    }

public:
    void print()
    {
#ifdef _DEBUG
        printf("\n=============================================\n");
    for (size_t i = 1; i < rl; i++)
        printf("|%zu %" TREE_SP " %zu %lld = %zu %zu|\n", i, data[i].fd.min.result, data[i].fd.min.ind, data[i].fd.asv, data[i].left, data[i].right);
    printf("=============================================\n");
#endif
    }
    void ini()
    {
        for(size_t i = la - 1; i > 0; i--)
        {
            data[i].fd.min = MIN(data[i*2].fd.min, data[i*2 + 1].fd.min);
            data[i].fd.asv = -1;

            data[i].left = data[i*2].left;
            data[i].right = data[i*2+1].right;
        }
    }
    void add(type_tree v)
    {
        if(current_add >= n)
        {
            printf("Error: tree is full\n");
            return;
        }

        data[la + current_add].fd.min = {v, current_add};
        //printf("%zu\n", data[la + current_add].fd.min.ind);
        data[la + current_add].fd.asv = -1;

        if(++current_add == n)
            ini();
    }
    Minimum min_assign(size_t l, size_t r)
    {
        return min_assign_rq(1, l, r);
    }
//    void set_assign(size_t l, size_t r, type_tree v)
//    {
//        return set_assign_rq(1, l, r, v);
//    }
};

struct Node{
    size_t deep = 0;
    size_t parent = 0;
    size_t dfs_ind_fst;
    size_t dfs_ind_lst;
    vector <size_t> childs;
};

Node *tree;
size_t *dfs_deep;
size_t *parent;

void dfs(size_t cur)
{
    static size_t i = 0;
    dfs_deep[i] = tree[cur].deep;
    tree[cur].dfs_ind_fst = i;
    parent[i] = cur;
    i++;

    for(size_t child : tree[cur].childs)
        dfs(child);

    dfs_deep[i] = tree[cur].deep;
    tree[cur].dfs_ind_fst = i;
    parent[i] = cur;
    i++;
}

int main() {
    size_t n;
    cin >> n;

    tree = new Node[n+1];

    tree[1] = {1, 0};

    for(size_t i = 2; i <= n; i++)
    {
        size_t parent;
        cin >> parent;
        tree[i].parent = parent;
        tree[i].deep = tree[parent].deep + 1;
        tree[parent].childs.push_back(i);
    }

    //for(size_t i = 1; i <= n; i++) cout << i << " " << tree[i].parent << " " << tree[i].deep << endl;

    dfs_deep = new size_t[n*2];
    parent = new size_t[n*2];
    dfs(1);

    Tree dfs_deep_tree(n*2);

    for (size_t i = 0; i < 2*n; i++)
    {
        dfs_deep_tree.add(dfs_deep[i]);
    }
    //dfs_deep_tree.ini();

    //dfs_deep_tree.print();


    size_t m;
    cin >> m;

    while(m--)
    {
        size_t a, b;
        cin >> a >> b;

//        while(tree[a].deep > tree[b].deep) a = tree[a].parent;
//        while(tree[b].deep > tree[a].deep) b = tree[b].parent;
//
//        while(a != b)
//        {
//            a = tree[a].parent;
//            b = tree[b].parent;
//        }

        size_t min, max;

        min = MIN(tree[a].dfs_ind_fst, tree[b].dfs_ind_fst);
        max = MAX(tree[a].dfs_ind_fst, tree[b].dfs_ind_fst);

        Tree::Minimum mini = dfs_deep_tree.min_assign(min, max);

        a = parent[mini.ind];
        a = tree[a].parent;
        cout << a << endl;
        //cout << mini.result << " " << mini.ind << endl;
    }

    delete[] dfs_deep;
    delete[] parent;
    delete[] tree;
    return 0;
}
