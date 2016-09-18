#include <sstream>
#include "wordPairs.h"

using namespace std;

int main()
{
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
        insert_word_pair(word1, word2);
    }
    dump_counts(cout);
}
