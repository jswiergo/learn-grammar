#include <fstream>
#include "wordPairs.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "usage: " << argv[0];
        cerr << " <words_output_filename>";
        cerr << " <word_pairs_output_filename>";
        cerr << " <files_to_merge>...." << endl;
        exit(1);
    }

    Words words;
    WordPairs word_pairs(words);

    string words_filename(argv[1]);
    string word_pairs_filename(argv[2]);
    string filename;

    ofstream word_pairs_file;
    word_pairs_file.open(word_pairs_filename);

    try {
        for (int i = 3; i < argc; ++i)
        {
            filename = argv[i];
            ifstream file_to_merge;
            file_to_merge.open(filename);
            words.load(file_to_merge, true);
            word_pairs.translate(file_to_merge, word_pairs_file);
            file_to_merge.close();
        }
    } catch (exception e) {
        cerr << "Exception in merge file: " << filename << endl;
        cerr << e.what() << endl;
    }

    word_pairs_file.close();

    ofstream words_file;
    words_file.open(words_filename);
    words.save(words_file);
    words_file.close();
}
