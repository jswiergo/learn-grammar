#include <vector>
#include <queue>
#include "unionSet.h"

using namespace std;

template<typename KeyT, typename WeightT>
class Kruskal
{
public:
    typedef KeyT Node;
    typedef pair<pair<KeyT, KeyT>, WeightT> Edge;

    static vector<Edge> maximum_spanning_tree(const vector<Node>& nodes, const vector<Edge>& edges);
};

template<typename KeyT, typename WeightT>
vector<typename Kruskal<KeyT,WeightT>::Edge>
Kruskal<KeyT,WeightT>::maximum_spanning_tree(const vector<Node>& nodes, const vector<Edge>& edges)
{
    vector<Edge> spanning_tree;
    UnionSet<Node> union_set(nodes);

    auto comparator = [](const Edge& left, const Edge& right) { return left.second < right.second; };
    priority_queue<Edge, vector<Edge>, decltype(comparator)> pri_queue(comparator, edges);

    while (!pri_queue.empty())
    {
        Edge edge = pri_queue.top(); pri_queue.pop();
        Node n1 = edge.first.first;
        Node n2 = edge.first.second;
        if (!union_set.same_set(n1, n2))
        {
            spanning_tree.push_back(edge);
            union_set.union_sets(n1, n2);
        }
    }
    return spanning_tree;
}
