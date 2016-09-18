#include <vector>
#include <unordered_map>
#include "wordPairs.h"

using namespace std;

namespace std
{
    template<>
    struct hash<pair_index_t>
    {
        size_t operator()(pair_index_t const& p) const
        {
            auto h1 = std::hash<index_t>{}(p.first);
            auto h2 = std::hash<index_t>{}(p.second);
            return h1 ^ h2;
        }
    };
}

vector<string> words;
vector<int> word_counts;
unordered_map<string, index_t> words_index;
unordered_map<pair_index_t, int> word_pair_counts;
unordered_map<index_t, index_t> merged_indices_map;

void clear_indices_map()
{
    merged_indices_map.clear();
}

index_t insert_word(const string& word, int count)
{
    index_t index;
    if (words_index.find(word) != words_index.end())
    {
        index = words_index[word];
        word_counts[index] += count;
    }
    else
    {
        index = words.size();
        words.push_back(word);
        words_index.insert(make_pair(word, index));
        word_counts.push_back(count);
    }
    return index;
}

index_t merge_word(const string& word, index_t unmerged_index, int count)
{
    index_t merged_index = insert_word(word, count);
    merged_indices_map.insert(make_pair(unmerged_index, merged_index));
    return merged_index;
}

void count_word_pair(pair_index_t pair_index, int count=1)
{
    if (word_pair_counts.find(pair_index) != word_pair_counts.end())
    {
        word_pair_counts[pair_index] += count;
    } else {
        word_pair_counts.insert(make_pair(pair_index, count));
    }
}

void insert_word_pair(const string& word1, const string& word2, int count)
{
    index_t index1 = insert_word(word1);
    index_t index2 = insert_word(word2);
    pair_index_t pair_index = make_pair(index1, index2);
    count_word_pair(pair_index, count);
}

void merge_word_pair_count(index_t unmerged_index1, index_t unmerged_index2, int count)
{
    index_t index1 = merged_indices_map[unmerged_index1];
    index_t index2 = merged_indices_map[unmerged_index2];
    pair_index_t pair_index = make_pair(index1, index2);
    count_word_pair(pair_index, count);
}

void dump_counts(ostream& os)
{
    os << words.size() << endl;
    for (index_t i = 0; i < words.size(); ++i)
    {
        os << words[i] << "\t" << word_counts[i] << endl;
    }

    os << word_pair_counts.size() << endl;
    for (auto it = word_pair_counts.begin(); it != word_pair_counts.end(); ++it)
    {
        os << it->first.first << "\t" << it->first.second << "\t" << it->second << endl;
    }
}
