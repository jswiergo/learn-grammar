#include <iostream>
#include <string>
#include <vector>
#include "linkGrammar.h"

using namespace std;

LinkGrammar link_grammar;

void translate_sentence_to_word_pairs(const string& line)
{
    vector<pair<string, string>> word_pairs;
    link_grammar.translate_sentence_to_word_pairs(line, word_pairs);
    for (size_t i = 0; i < word_pairs.size(); ++i)
    {
        cout << word_pairs[i].first << "\t";
        cout << word_pairs[i].second << endl;
    }
}

int main()
{
    link_grammar.init();

    string line;
    while (getline(cin, line))
    {
        translate_sentence_to_word_pairs(line.c_str());
    }
}
