#include <sstream>
#include "wordPairs.h"

using namespace std;

int main()
{
    Words words;
    WordPairs word_pairs(words);

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
        word_pairs.insert(word1, word2);
    }
    words.save(cout);
    word_pairs.save(cout);
}
