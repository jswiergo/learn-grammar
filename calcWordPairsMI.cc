#include <fstream>
#include <sstream>
#include "wordPairs.h"

using namespace std;

int line_number;

// copy & paste for now

void merge_file_word_counts(istream& file)
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
        string word1, word2, word3;
        getline(ss, word1, '\t');
        getline(ss, word2, '\t');
        getline(ss, word3, '\t');
        merge_word(word1, i, stoi(word2), stoi(word3));
    }
}

void merge_file_word_pair_counts(istream& file)
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
        merge_word_pair_count(index1, index2, stoi(word3));
    }
}

int main()
{
    line_number = 1;

    try {
        merge_file_word_counts(cin);
        merge_file_word_pair_counts(cin);
    } catch (exception e) {
        cerr << "Exception in parsing word pair counts file: ";
        cerr << ":" << line_number << endl;
        cerr << e.what() << endl;
    }
    calculate_mutual_informations();
    dump_MIs(cout);
}
