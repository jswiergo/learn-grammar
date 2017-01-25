#include "disjuncts.h"

IdxT Disjuncts::insert(const Disjunct& disjunct)
{
    IdxT index;
    string disjunct_string = disjunct.to_string();
    if (disjuncts_index.find(disjunct_string) != disjuncts_index.end())
    {
        index = disjuncts_index[disjunct_string];
    } else {
        index = disjuncts.size();
        disjuncts.push_back(disjunct);
        disjuncts_index.insert({disjunct_string, index});
    }
    return index;
}

void Disjuncts::save(ostream& os)
{
    os << disjuncts.size() << endl;
    for (IdxT i = 0; i < disjuncts.size(); ++i)
    {
        os << disjuncts[i].to_string() << endl;
    }
};
