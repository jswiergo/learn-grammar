#ifndef _WORDS_H
#define _WORDS_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

typedef size_t IdxT;

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
    const IdxT UNKNOWN_INDEX = -1;

    Words() { left_total_count = 0; right_total_count = 0; };

    IdxT insert(const string& word, int left_count, int right_count);

    int get_left_count(IdxT index) { return word_left_counts[index]; };
    int get_right_count(IdxT index) { return word_right_counts[index]; };
    size_t size() { return words.size(); };
    int get_left_total_count() { return left_total_count; };
    int get_right_total_count() { return right_total_count; };
    IdxT get_index(const string& word);
    IdxT get_merged_index(IdxT unmerged_index) { return merged_indices[unmerged_index]; }

    void load(istream& is, bool merging=false);
    void save(ostream& os);
};

#endif // _WORDS_H
