#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "words.h"

using namespace std;

typedef double entropy_t;

Words words;
int total_count;

#define entropy(cnt) (-log2((entropy_t)cnt/(entropy_t)total_count))

void translateCountToMutualInformation(istream& is, ostream& os)
{
    string line;
    getline(is, line);

    IdxT total_word_pairs = stoi(line);
    os << total_word_pairs << endl;

    for (IdxT i = 0; i < total_word_pairs; ++i)
    {
        getline(is, line);
        stringstream ss(line);
        string token1, token2, token3;
        getline(ss, token1, '\t');
        getline(ss, token2, '\t');
        getline(ss, token3, '\t');

        int left_count = words.get_left_count(stoi(token1));
        int right_count = words.get_right_count(stoi(token2));
        int pair_count = stoi(token3);

        entropy_t left_entropy = entropy(left_count);
        entropy_t right_entropy = entropy(right_count);
        entropy_t pair_entropy = entropy(pair_count);
        entropy_t mutual_information = left_entropy + right_entropy - pair_entropy;

        os << token1 << "\t";
        os << token2 << "\t";
        os << mutual_information << endl;
    }
}

int main()
{
    words.load(cin);
    words.save(cout);

    total_count = words.get_left_total_count();

    cout << setprecision(10);
    translateCountToMutualInformation(cin, cout);
}
