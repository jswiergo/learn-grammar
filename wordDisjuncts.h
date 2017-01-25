#ifndef _WORD_DISJUNCTS_H
#define _WORD_DISJUNCTS_H

#include <iostream>
#include <unordered_map>
#include "words.h"

class WordDisjuncts
{
protected:
    typedef unordered_map<IdxT, int> DisjunctCountsT;
    unordered_map<IdxT, DisjunctCountsT> word_disjuncts;

public:
    void insert(IdxT word, IdxT disjunct, int count=1);
    void save(ostream& os);
};

#endif // _WORD_DISJUNCTS_H
