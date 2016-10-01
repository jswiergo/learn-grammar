#include <iostream>
#include <string>
#include <cstring>
#include "linkGrammar.h"

using namespace std;

const string LinkGrammar::DEFAULT_LANG = "any";

void LinkGrammar::init(int max_parses, const string& lang)
{
    opts = parse_options_create();
    parse_options_set_linkage_limit(opts, max_parses);
    dict = dictionary_create_lang(lang.c_str());
    if (!dict)
    {
        cerr << "Fatal error: Unable to open the dictionary" << endl;
        exit(1);
    }
}

/**
 * Strip special subscripts added by LinkGrammar similarly to relex.
 * See relex: LinkableView: setWordAndPos
 */
string LinkGrammar::strip_linkage_word(const char* word)
{
    size_t len = strlen(word);
    if (len > 2)
    {
       if (word[0] == '[' && word[len-1] == ']')
           return string(word+1, len-2);
    }
    if (len > 3)
    {
        if (!strncmp(word+len-3, "[!]", 3) ||
            !strncmp(word+len-3, "[?]", 3) ||
            !strncmp(word+len-3, "[~]", 3))
            return string(word, len-3);
    }
    return string(word);
}

void LinkGrammar::translate_sentence_to_word_pairs(const string& line,
                                                   vector<pair<string, string>>& word_pairs)
{
    Sentence sent = sentence_create(line.c_str(), dict);
    sentence_split(sent, opts);
    int num_linkages = sentence_parse(sent, opts);

    for(int i =0; i < num_linkages; ++i)
    {
        Linkage linkage = linkage_create(i, sent, opts);
        int num_links = linkage_get_num_links(linkage);
        for(int j = 0; j < num_links; ++j) {
            int lword = linkage_get_link_lword(linkage, j);
            int rword = linkage_get_link_rword(linkage, j);
            pair<string, string> word_pair = make_pair(
                strip_linkage_word(linkage_get_word(linkage, lword)),
                strip_linkage_word(linkage_get_word(linkage, rword)));
            word_pairs.push_back(word_pair);
        }
        linkage_delete(linkage);
    }
    sentence_delete(sent);
}

void LinkGrammar::translate_sentence_to_words(const string& line, vector<string>& words)
{
    Sentence sent = sentence_create(line.c_str(), dict);
    sentence_split(sent, opts);
    int num_linkages = sentence_parse(sent, opts);
    if (num_linkages == 0) return;

    Linkage linkage = linkage_create(0, sent, opts);
    size_t num_words = linkage_get_num_words(linkage);
    const char** linkage_words = linkage_get_words(linkage);
    for (size_t i = 0; i < num_words; ++i)
    {
        string word = strip_linkage_word(linkage_words[i]);
        words.push_back(word);
    }
    linkage_delete(linkage);
    sentence_delete(sent);
}
