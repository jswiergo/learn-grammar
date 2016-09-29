#include <sstream>
#include "wordPairs.h"

using namespace std;

IdxT Words::insert(const string& word, int left_count, int right_count)
{
    IdxT index;
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
    left_total_count += left_count;
    right_total_count += right_count;
    return index;
}

IdxT Words::merge(const string& word, IdxT unmerged_index, int left_count, int right_count)
{
    IdxT merged_index = insert(word, left_count, right_count);
    merged_indices[unmerged_index] = merged_index;
    return merged_index;
}

void Words::load(istream& istream, bool merging)
{
    string line;
    getline(istream, line);
    IdxT total_words = stoi(line);

    merged_indices.clear();
    merged_indices.resize(total_words);

    for (IdxT i = 0; i < total_words; ++i)
    {
        getline(istream, line);
        stringstream ss(line);
        string token1, token2, token3;
        getline(ss, token1, '\t');
        getline(ss, token2, '\t');
        getline(ss, token3, '\t');
        if (merging)
            merge(token1, i, stoi(token2), stoi(token3));
        else
            insert(token1, stoi(token2), stoi(token3));
    }
}

void Words::save(ostream& os)
{
    os << words.size() << endl;
    for (IdxT i = 0; i < words.size(); ++i)
    {
        os << words[i] << "\t";
        os << word_left_counts[i] << "\t";
        os << word_right_counts[i] << endl;
    }
}

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