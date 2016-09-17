#include <cstdlib>
#include <iostream>
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

index_t insert_word(const string& word)
{
    index_t index;
    if (words_index.find(word) != words_index.end())
    {
        index = words_index[word];
        word_counts[index]++;
    }
    else
    {
        index = words.size();
        words.push_back(word);
        words_index.insert(make_pair(word, index));
        word_counts.push_back(1);
    }
    return index;
}

void insert_word_pair(const string& word1, const string& word2)
{
    index_t index1 = insert_word(word1);
    index_t index2 = insert_word(word2);

    pair_index_t pair_index = make_pair(index1, index2);
    if (word_pair_counts.find(pair_index) != word_pair_counts.end())
    {
        word_pair_counts[pair_index]++;
    } else {
        word_pair_counts.insert(make_pair(pair_index, 1));
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

int main()
{
    string line;
    int line_number = 0;

    while (getline(cin, line))
    {
        line_number++;

        stringstream ss(line);
        string word1, word2, word3;
        getline(ss, word1, '\t');
        getline(ss, word2, '\t');
        getline(ss, word3, '\t');

        if (!word1.length() || !word2.length() || word3.length())
        {
            cerr << "Wrong format at line " << line_number << ":" << endl;
            cerr << line << endl;
            exit(1);
        }

        insert_word_pair(word1, word2);

        if (line_number % 10000 == 0)
        {
            cerr << "Line: " << line_number << " words: " << words.size();
            cerr << " word pairs: " << word_pair_counts.size() << endl;
        }
    }

    dump_counts();
}
