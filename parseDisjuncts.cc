#include <iostream>
#include <fstream>
#include <string>
#include "algorithms/kruskal.h"
#include "wordPairs.h"

using namespace std;

Words words;
WordPairs word_pairs(words);

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

        // TODO:

        article_file.close();
        output_file.close();
    }
}
