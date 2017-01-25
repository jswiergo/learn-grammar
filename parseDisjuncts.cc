#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "algorithms/kruskal.h"
#include "wordPairs.h"
#include "disjuncts.h"
#include "wordDisjuncts.h"

using namespace std;

typedef Kruskal<IdxT, entropy_t> KruskalT;
typedef KruskalT::Node NodeT;
typedef KruskalT::Edge EdgeT;

Words words;
WordPairs word_pairs(words);
Disjuncts disjuncts;
WordDisjuncts word_disjuncts;

vector<IdxT> parse_word_indexes_from_sentence(const string& sentence)
{
    vector<IdxT> word_indexes;
    stringstream ss(sentence);
    string token;
    while (getline(ss, token, ' '))
    {
        word_indexes.push_back(stoi(token));
    }
    return word_indexes;
}

void parse_disjuncts_from_sentence(const string& sentence)
{
    vector<IdxT> word_indexes = parse_word_indexes_from_sentence(sentence);
    size_t number_of_words = word_indexes.size();

    vector<Disjunct> sentence_disjuncts(number_of_words);

    vector<NodeT> nodes;
    for (IdxT i = 0; i < number_of_words; ++i)
    {
        nodes.push_back(i);
    }
    vector<EdgeT> edges;
    for (IdxT i = 0; i < number_of_words-1; ++i)
    {
        for (IdxT j = i+1; j < number_of_words; ++j)
        {
            entropy_t mi = word_pairs.get_word_pair_MI({word_indexes[i], word_indexes[j]});
            edges.push_back({{i, j}, mi});
        }
    }
    vector<EdgeT> tree_edges = KruskalT::maximum_spanning_tree(nodes, edges);

    for (auto edge: tree_edges)
    {
        IdxT i = edge.first.first;
        IdxT j = edge.first.second;
        sentence_disjuncts[i].add_plus_connector(word_indexes[j]);
        sentence_disjuncts[j].add_minus_connector(word_indexes[i]);
    }
    for (IdxT i = 0; i < number_of_words; ++i)
    {
        sentence_disjuncts[i].sort_connectors();
        IdxT disjunct_index = disjuncts.insert(sentence_disjuncts[i]);
        word_disjuncts.insert(word_indexes[i], disjunct_index);
    }
}

void parse_disjuncts_from_article(istream& istream)
{
    string line;
    while (getline(istream, line))
    {
        parse_disjuncts_from_sentence(line);
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "usage: " << argv[0] << " <words_mi_filename> <output_dir> <articles>...." << endl;
        exit(1);
    }

    string words_mi_filename(argv[1]);
    ifstream words_mi_file;
    words_mi_file.open(words_mi_filename);
    word_pairs.load_MI(words_mi_file);

    string output_dir = argv[2];
    for (int i = 3; i < argc; ++i)
    {
        string article_filename = argv[i];
        string article_name = article_filename.substr(article_filename.find_last_of("/")+1);
        string output_filename = output_dir + "/" + article_name;
        ifstream article_file;
        ofstream output_file;
        article_file.open(article_filename);
        output_file.open(output_filename);

        parse_disjuncts_from_article(article_file);

        disjuncts.save(output_file);
        word_disjuncts.save(output_file);

        article_file.close();
        output_file.close();
    }
}
