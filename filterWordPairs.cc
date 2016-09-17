#include <iostream>
#include <string>

using namespace std;

/*
(EvaluationLink (stv 1.0 1.0)
   (LinkGrammarRelationshipNode "ANY")
   (ListLink
      (WordInstanceNode "ma@b45ab846-ee09-4f4b-a18b-a31de1414539")
      (WordInstanceNode "kota@2cda8f34-0956-452f-bed6-7872122eabec")
   )
)
(EvaluationLink (stv 1.0 1.0)
   (LinkGrammarRelationshipNode "ANY")
   (ListLink
      (WordInstanceNode "LEFT-WALL@sentence@643a872c-eecd-4297-8480-c4fcf28b7a3a_parse_0")
      (WordInstanceNode "ala@8ca23db2-f2ee-4e66-ae1d-b39a247622b8")
   )
)
*/

const string FIRST_LINE_PATTERN = "LinkGrammarRelationshipNode";
const string SECOND_LINE_PATTERN = "ListLink";
const string LEFT_WALL_PATTERN = "LEFT-WALL@sentence@";
const string LEFT_WALL_WORD = "LEFT-WALL";
const size_t PREFIX_LENGTH = 25;
const size_t IGNORED_LENGTH = PREFIX_LENGTH + 39;

int main()
{
    int matched_lines = 0;
    string first_word;
    string second_word;

    string line;
    while (getline(cin, line))
    {
        switch (matched_lines)
        {
            case 0:
                if (line.find(FIRST_LINE_PATTERN) != string::npos)
                    matched_lines = 1;
                continue;
            case 1:
                if (line.find(SECOND_LINE_PATTERN) != string::npos)
                    matched_lines = 2;
                else
                    matched_lines = 0;
                continue;
            case 2:
                if (line.length() < IGNORED_LENGTH)
                {
                    matched_lines = 0;
                    continue;
                }
                if (line.find(LEFT_WALL_PATTERN) != string::npos)
                    first_word = LEFT_WALL_WORD;
                else
                    first_word = line.substr(PREFIX_LENGTH, line.length() - IGNORED_LENGTH);
                matched_lines = 3;
                continue;
            case 3:
                if (line.length() < IGNORED_LENGTH)
                {
                    matched_lines = 0;
                    continue;
                }
                second_word = line.substr(PREFIX_LENGTH, line.length() - IGNORED_LENGTH);
                cout << first_word << "\t" << second_word << endl;
                matched_lines = 0;
            default:
                break;
        }
    }
}
