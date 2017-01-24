#include <sstream>
#include <cstdlib>
#include "wordPairs.h"

using namespace std;

void WordPairs::count_word_pair(PairIdxT pair_index, int count)
{
    if (word_pair_counts.find(pair_index) != word_pair_counts.end())
    {
        word_pair_counts[pair_index] += count;
    } else {
        word_pair_counts.insert({pair_index, count});
    }
}

void WordPairs::insert(const string& word1, const string& word2, int count)
{
    IdxT index1 = words.insert(word1, count, 0);
    IdxT index2 = words.insert(word2, 0, count);
    PairIdxT pair_index = {index1, index2};
    count_word_pair(pair_index, count);
}

void WordPairs::insert_word_pair_MI(PairIdxT pair_index, entropy_t mi)
{
    word_pair_MIs.insert({pair_index, mi});
}

entropy_t WordPairs::get_word_pair_MI(PairIdxT pair_index)
{
    if (word_pair_MIs.find(pair_index) != word_pair_MIs.end())
    {
        return word_pair_MIs[pair_index];
    } else {
        return 0;
    }
}

void WordPairs::load_MI(istream& istream)
{
    string line;
    getline(istream, line);
    if (line == "") return;  // skip empty files

    // skip words
    IdxT total_words = stoi(line);
    for (IdxT i = 0; i < total_words; ++i)
    {
        getline(istream, line);
    }

    IdxT total_word_pairs = stoi(line);
    for (IdxT i = 0; i < total_word_pairs; ++i)
    {
        getline(istream, line);
        stringstream ss(line);
        string token1, token2, token3;
        getline(ss, token1, '\t');
        getline(ss, token2, '\t');
        getline(ss, token3, '\t');
        IdxT idx1 = stoi(token1);
        IdxT idx2 = stoi(token2);
        entropy_t mi = stod(token3);
        insert_word_pair_MI({idx1, idx2}, mi);
    }
}

void WordPairs::save(ostream& os)
{
    os << word_pair_counts.size() << endl;
    for (auto wp: word_pair_counts)
    {
        os << wp.first.first << "\t";
        os << wp.first.second << "\t";
        os << wp.second << endl;
    }
}

void WordPairs::translate(istream& is, ostream& os)
{
    string line;
    getline(is, line);
    if (line == "") return;  // skip empty files

    int total_pairs = stoi(line);

    for (int i = 0; i < total_pairs; ++i)
    {
        getline(is, line);
        stringstream ss(line);
        string token1, token2, token3;
        getline(ss, token1, '\t');
        getline(ss, token2, '\t');
        getline(ss, token3, '\t');
        IdxT unmerged_index1 = stoi(token1);
        IdxT unmerged_index2 = stoi(token2);
        os << words.get_merged_index(unmerged_index1) << "\t";
        os << words.get_merged_index(unmerged_index2) << "\t";
        os << token3 << endl;
    }
}
