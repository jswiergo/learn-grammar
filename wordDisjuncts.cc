#include "wordDisjuncts.h"

void WordDisjuncts::insert(IdxT word, IdxT disjunct, int count)
{
    if (word_disjuncts.find(word) == word_disjuncts.end())
    {
        word_disjuncts.insert({word, DisjunctCountsT()});
    }

    DisjunctCountsT& disjunct_counts = word_disjuncts[word];
    if (disjunct_counts.find(disjunct) != disjunct_counts.end())
    {
        disjunct_counts[disjunct] += count;
    } else {
        disjunct_counts.insert({disjunct, count});
    }
}

void WordDisjuncts::save(ostream& os)
{
    os << word_disjuncts.size() << endl;
    for (auto wd: word_disjuncts)
    {
        os << wd.first << " " << wd.second.size();
        for (auto it: wd.second)
        {
            os << " " << it.first << " " << it.second;
        }
        os << endl;
    }
}
