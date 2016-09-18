#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef size_t index_t;
typedef pair<index_t, index_t> pair_index_t;

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

int line_number;

index_t insert_word(const string& word, int count=1)
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

void merge_word(string word, int count, index_t unmerged_index)
{
    index_t merged_index = insert_word(word, count);
    merged_indices_map.insert(make_pair(unmerged_index, merged_index));
}

void merge_file_word_counts(ifstream& file)
{
    string line;
    index_t total_words;

    getline(file, line);
    line_number++;
    total_words = stoi(line);

    for (index_t i = 0; i < total_words; ++i)
    {
        getline(file, line);
        line_number++;

        stringstream ss(line);
        string word1, word2;
        getline(ss, word1, '\t');
        getline(ss, word2, '\t');
        merge_word(word1, stoi(word2), i);
    }
}

void merge_file_word_pair_counts(ifstream& file)
{
    string line;
    index_t total_word_pairs;

    getline(file, line);
    line_number++;
    total_word_pairs = stoi(line);

    for (index_t i = 0; i < total_word_pairs; ++i)
    {
        getline(file, line);
        line_number++;

        stringstream ss(line);
        string word1, word2, word3;
        getline(ss, word1, '\t');
        getline(ss, word2, '\t');
        getline(ss, word3, '\t');
        
        index_t index1 = stoi(word1);
        index_t index2 = stoi(word2);
        index1 = merged_indices_map[index1];
        index2 = merged_indices_map[index2];

        int word_pair_count = stoi(word3);

        pair_index_t pair_index = make_pair(index1, index2);
        if (word_pair_counts.find(pair_index) != word_pair_counts.end())
        {
            word_pair_counts[pair_index] += word_pair_count;
        } else {
            word_pair_counts.insert(make_pair(pair_index, word_pair_count));
        }
    }
}

void merge_file(string filename)
{
    merged_indices_map.clear();
    line_number = 1;

    try {
        ifstream file;
        file.open(filename);
        merge_file_word_counts(file);
        merge_file_word_pair_counts(file);
        file.close();        
    } catch (exception e) {
        cerr << "Exception in merge file: " << filename;
        cerr << ":" << line_number << endl;
        cerr << e.what() << endl;
    }
}

void dump_counts()
{
    cout << words.size() << endl;
    for (index_t i = 0; i < words.size(); ++i)
    {
        cout << words[i] << "\t" << word_counts[i] << endl;
    }

    cout << word_pair_counts.size() << endl;
    for (auto it = word_pair_counts.begin(); it != word_pair_counts.end(); ++it)
    {
        cout << it->first.first << "\t" << it->first.second << "\t" << it->second << endl;
    }
}

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        merge_file(argv[i]);
    }
    dump_counts();
}
