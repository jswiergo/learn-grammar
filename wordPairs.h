#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

typedef size_t IdxT;
typedef pair<IdxT, IdxT> PairIdxT;

// This is only for WordPairs map structure
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

class Words
{
protected:
    vector<string> words;
    vector<int> word_left_counts;
    vector<int> word_right_counts;
    unordered_map<string, IdxT> words_index;
    vector<IdxT> merged_indices;

    int left_total_count;
    int right_total_count;

    IdxT merge(const string& word, IdxT unmerged_index, int left_count, int right_count);

public:
    Words() { left_total_count = 0; right_total_count = 0; };

    IdxT insert(const string& word, int left_count, int right_count);

    int get_left_count(IdxT index) { return word_left_counts[index]; };
    int get_right_count(IdxT index) { return word_right_counts[index]; };
    size_t size() { return words.size(); };
    int get_left_total_count() { return left_total_count; };
    int get_right_total_count() { return right_total_count; };
    IdxT get_merged_index(IdxT unmerged_index) { return merged_indices[unmerged_index]; }

    void load(istream& is, bool merging=false);
    void save(ostream& os);
};

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
