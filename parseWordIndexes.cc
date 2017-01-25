#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include "linkGrammar.h"
#include "words.h"

using namespace std;

LinkGrammar link_grammar;
Words words;

void translate_sentence_to_word_indexes(const string& line, ostream& os)
{
    vector<string> sentence_words;
    link_grammar.translate_sentence_to_words(line, sentence_words);
    for (size_t i = 0; i < sentence_words.size(); ++i)
    {
        if (i > 0) os << " ";
        os << words.get_index(sentence_words[i]);
    }
    if (sentence_words.size() > 0)
    {
        os << endl;
    }
}

void translate_article_to_word_indexes(istream& is, ostream& os)
{
    string line;
    while (getline(is, line))
    {
        translate_sentence_to_word_indexes(line, os);
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "usage: " << argv[0] << " <words_filename> <output_dir> <move_articles_dir> <articles>...." << endl;
        exit(1);
    }

    string words_filename(argv[1]);
    ifstream words_file;
    words_file.open(words_filename);
    words.load(words_file);

    link_grammar.init(1);

    string output_dir = argv[2];
    string move_articles_dir = argv[3];
    for (int i = 4; i < argc; ++i)
    {
        string article_filename = argv[i];
        string article_name = article_filename.substr(article_filename.find_last_of("/")+1);
        string output_filename = output_dir + "/" + article_name;
        ifstream article_file;
        ofstream output_file;
        article_file.open(article_filename);
        output_file.open(output_filename);

        translate_article_to_word_indexes(article_file, output_file);

        article_file.close();
        output_file.close();

        string moved_article_filename = move_articles_dir + "/" + article_name;
        rename(article_filename, moved_article_filename);
    }
}
