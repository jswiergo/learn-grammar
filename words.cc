#include <sstream>
#include "words.h"

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

IdxT Words::get_index(const string& word)
{
    return (words_index.find(word) != words_index.end()) ?
        words_index[word] : UNKNOWN_INDEX;
}

void Words::load(istream& istream, bool merging)
{
    string line;
    getline(istream, line);
    if (line == "") return;  // skip empty files

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
