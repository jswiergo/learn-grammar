#include <iostream>
#include <string>
#include <unordered_map>
#include "words.h"

using namespace std;

typedef pair<IdxT, IdxT> PairIdxT;

namespace std
{
    template<>
    struct hash<PairIdxT>
    {
        size_t operator()(PairIdxT const& p) const
        {
            auto h1 = std::hash<IdxT>{}(p.first);
            auto h2 = std::hash<IdxT>{}(p.second);
            return h1 ^ h2;
        }
    };
}

class WordPairs
{
protected:
    Words& words;
    unordered_map<PairIdxT, int> word_pair_counts;

    void count_word_pair(PairIdxT pair_index, int count=1);

public:
    WordPairs(Words& ws) : words(ws) {};

    void insert(const string& word1, const string& word2, int count=1);
    void save(ostream& os);

    // translate line by line without memory usage
    void translate(istream& is, ostream& os);
};
