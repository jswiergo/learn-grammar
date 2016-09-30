#include <sstream>
#include "wordPairs.h"

using namespace std;

void WordPairs::count_word_pair(PairIdxT pair_index, int count)
{
    if (word_pair_counts.find(pair_index) != word_pair_counts.end())
    {
        word_pair_counts[pair_index] += count;
    } else {
        word_pair_counts.insert(make_pair(pair_index, count));
    }
}

void WordPairs::insert(const string& word1, const string& word2, int count)
{
    IdxT index1 = words.insert(word1, count, 0);
    IdxT index2 = words.insert(word2, 0, count);
    PairIdxT pair_index = make_pair(index1, index2);
    count_word_pair(pair_index, count);
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
