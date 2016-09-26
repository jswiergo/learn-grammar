#include <iostream>
#include <string>

using namespace std;

typedef size_t index_t;
typedef pair<index_t, index_t> pair_index_t;

index_t insert_word(const string& word, int count=1);
index_t merge_word(const string& word, index_t unmerged_index, int count=1);

void insert_word_pair(const string& word1, const string& word2, int count=1);
void merge_word_pair_count(index_t unmerged_index1, index_t unmerged_index2, int count=1);
void calculate_mutual_informations();

void dump_counts(ostream& os);
void dump_MIs(ostream& os);

void clear_indices_map();
