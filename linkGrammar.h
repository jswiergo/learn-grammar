#include <string>
#include <vector>
#include <link-grammar/link-includes.h>

using namespace std;

class LinkGrammar
{
protected:
    Dictionary dict;
    Parse_Options opts;

    string strip_linkage_word(const char* word);

public:
    static const int DEFAULT_MAX_PARSES = 16;
    static const string DEFAULT_LANG;

    LinkGrammar() {};
    void init(int max_parses=DEFAULT_MAX_PARSES, const string& lang=DEFAULT_LANG);

    void translate_sentence_to_words(const string& line, vector<string>& words);
    void translate_sentence_to_word_pairs(const string& line,
                                          vector<pair<string, string>>& word_pairs);
};
