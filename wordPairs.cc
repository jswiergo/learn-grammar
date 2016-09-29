#include <iomanip>
#include <vector>
#include <cmath>
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
vector<int> word_left_counts;
vector<int> word_right_counts;
unordered_map<string, index_t> words_index;
unordered_map<pair_index_t, int> word_pair_counts;
unordered_map<index_t, index_t> merged_indices_map;

// for mutual information
typedef double entropy_t;

long long int word_pairs_total_count;
vector<entropy_t> word_left_entropies;
vector<entropy_t> word_right_entropies;
unordered_map<pair_index_t, entropy_t> word_pair_MIs;

void clear_indices_map()
{
    merged_indices_map.clear();
}

index_t insert_word(const string& word, int left_count, int right_count)
{
    index_t index;
    if (words_index.find(word) != words_index.end())
    {
        index = words_index[word];
        word_left_counts[index] += left_count;
        word_right_counts[index] += right_count;
    }
    else
    {
        index = words.size();
        words.push_back(word);
        words_index.insert(make_pair(word, index));
        word_left_counts.push_back(left_count);
        word_right_counts.push_back(right_count);
    }
    return index;
}

index_t merge_word(const string& word, index_t unmerged_index, int left_count, int right_count)
{
    index_t merged_index = insert_word(word, left_count, right_count);
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
    index_t index1 = insert_word(word1, 1, 0);
    index_t index2 = insert_word(word2, 0, 1);
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

#define entropy(cnt) (-log2((entropy_t)cnt/(entropy_t)word_pairs_total_count))

void calculate_mutual_informations()
{
    word_pairs_total_count = 0;
    for (auto wp: word_pair_counts)
    {
        word_pairs_total_count += wp.second;
    }

    word_left_entropies.assign(words.size(), 0.0);
    word_right_entropies.assign(words.size(), 0.0);
    for (index_t i = 0; i < words.size(); ++i)
    {
        word_left_entropies[i] = entropy(word_left_counts[i]);
        word_right_entropies[i] = entropy(word_right_counts[i]);
    }

    for (auto wp: word_pair_counts)
    {
        index_t index1 = wp.first.first;
        index_t index2 = wp.first.second;
        int pair_count = wp.second;

        entropy_t pair_entropy = entropy(pair_count);
        entropy_t pair_MI = word_left_entropies[index1]
                          + word_right_entropies[index2]
                          - pair_entropy;
        pair_index_t pair_index = make_pair(index1, index2);
        word_pair_MIs.insert(make_pair(pair_index, pair_MI));
    }
}


void dump_words(ostream& os)
{
    os << words.size() << endl;
    for (index_t i = 0; i < words.size(); ++i)
    {
        os << words[i] << "\t";
        os << word_left_counts[i] << "\t";
        os << word_right_counts[i] << endl;
    }
}

void dump_counts(ostream& os)
{
    dump_words(os);

    os << word_pair_counts.size() << endl;
    for (auto wp: word_pair_counts)
    {
        os << wp.first.first << "\t";
        os << wp.first.second << "\t";
        os << wp.second << endl;
    }
}

void dump_MIs(ostream& os)
{
    dump_words(os);

    os << word_pair_MIs.size() << endl;
    os << setprecision(8);
    for (auto wp: word_pair_MIs)
    {
        os << wp.first.first << "\t";
        os << wp.first.second << "\t";
        os << wp.second << endl;
    }
}
