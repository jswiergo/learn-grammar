#ifndef _WORD_PAIRS_H
#define _WORD_PAIRS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "words.h"

using namespace std;

typedef pair<IdxT, IdxT> PairIdxT;
typedef double entropy_t;

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
    unordered_map<PairIdxT, entropy_t> word_pair_MIs;

    void count_word_pair(PairIdxT pair_index, int count=1);
    void insert_word_pair_MI(PairIdxT pair_index, entropy_t mi);

public:
    WordPairs(Words& ws) : words(ws) {};

    void insert(const string& word1, const string& word2, int count=1);
    entropy_t get_word_pair_MI(PairIdxT pair_index);

    void load_MI(istream& is);
    void save(ostream& os);

    // translate line by line without memory usage
    void translate(istream& is, ostream& os);
};

#endif // _WORD_PAIRS_H
