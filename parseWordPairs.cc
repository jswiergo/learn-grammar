#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <link-grammar/link-includes.h>

using namespace std;

const int DEFAULT_MAX_PARSES = 16;
const char* DEFAULT_LANG = "any";

Dictionary dict;
Parse_Options opts;

void init_parser()
{
    opts = parse_options_create();
    parse_options_set_linkage_limit(opts, DEFAULT_MAX_PARSES);
    dict = dictionary_create_lang(DEFAULT_LANG);
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
string strip_linkage_word(const char* word)
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

void parse_line(const char* line)
{
    Sentence sent = sentence_create(line, dict);
    sentence_split(sent, opts);
    int num_linkages = sentence_parse(sent, opts);

    for(int i =0; i < num_linkages; ++i)
    {
        Linkage linkage = linkage_create(i, sent, opts);
        int num_links = linkage_get_num_links(linkage);
        for(int j = 0; j < num_links; ++j) {
            int lword = linkage_get_link_lword(linkage, j);
            int rword = linkage_get_link_rword(linkage, j);
            cout << strip_linkage_word(linkage_get_word(linkage, lword));
            cout << "\t";
            cout << strip_linkage_word(linkage_get_word(linkage, rword));
            cout << endl;
        }
        linkage_delete(linkage);
    }
    sentence_delete(sent);
}

int main()
{
    init_parser();

    string line;
    while (getline(cin, line))
    {
        parse_line(line.c_str());
    }
}
