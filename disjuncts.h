#ifndef _DISJUNCTS_H
#define _DISJUNCTS_H

#include "disjunct.h"

class Disjuncts
{
protected:
    vector<Disjunct> disjuncts;
    unordered_map<string, IdxT> disjuncts_index;

public:
    Disjuncts() {};

    IdxT insert(const Disjunct& disjunct);
    void save(ostream& os);
};

#endif // _DISJUNCTS_H
