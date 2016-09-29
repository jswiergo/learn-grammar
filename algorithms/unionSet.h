#include <vector>
#include <unordered_map>

using namespace std;

template<typename T>
class UnionSet
{
protected:
    struct Node
    {
        Node* parent;
        int height;
        T value;
        Node(const T& v) { parent = NULL; height = 0; value = v; };
    };
    unordered_map<T, Node*> nodes;

    Node* find(Node* n);
    void union_sets(Node* nx, Node* ny);

public:
    UnionSet() {};
    UnionSet(const vector<T>& vec);
    ~UnionSet();

    void add(const T& v);
    bool same_set(const T& v1, const T& v2);
    void union_sets(const T& v1, const T& v2);
};

template<typename T>
UnionSet<T>::UnionSet(const vector<T>& vec)
{
    for (auto v : vec)
    {
        add(v);
    }
}

template<typename T>
UnionSet<T>::~UnionSet()
{
    for (auto it : nodes)
    {
        delete it.second;
    }
}

template<typename T>
void UnionSet<T>::add(const T& v)
{
    if (nodes.find(v) == nodes.end())
    {
        Node* node = new Node(v);
        nodes.insert(make_pair(v, node));
    }
}

template<typename T>
typename UnionSet<T>::Node* UnionSet<T>::find(UnionSet<T>::Node * n)
{
    if (n->parent == NULL)
    {
        return n;
    }
    n->parent = find(n->parent);   // path compression
    return n->parent;
}

template<typename T>
void UnionSet<T>::union_sets(UnionSet<T>::Node* nx, UnionSet<T>::Node* ny)
{
    UnionSet<T>::Node* xRoot = find(nx);
    UnionSet<T>::Node* yRoot = find(ny);
    if (xRoot->height > yRoot->height)
    {
        yRoot->parent = xRoot;
    }
    else if (xRoot->height < yRoot->height)
    {
        xRoot->parent = yRoot;
    }
    else if (xRoot != yRoot)
    {
        yRoot->parent = xRoot;
        xRoot->height = xRoot->height + 1;
    }
}

template<typename T>
bool UnionSet<T>::same_set(const T& v1, const T& v2)
{
    if (nodes.find(v1) == nodes.end()) return false;
    if (nodes.find(v2) == nodes.end()) return false;
    Node* n1 = find(nodes[v1]);
    Node* n2 = find(nodes[v2]);
    return (n1 == n2);
}

template<typename T>
void UnionSet<T>::union_sets(const T& v1, const T& v2)
{
    if (nodes.find(v1) == nodes.end()) return;
    if (nodes.find(v2) == nodes.end()) return;
    union_sets(nodes[v1], nodes[v2]);
}
