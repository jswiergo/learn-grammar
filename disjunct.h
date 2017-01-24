#ifndef _DISJUNCT_H
#define _DISJUNCT_H

#include <string>
#include <vector>
#include "words.h"

using namespace std;

class Disjunct
{
protected:
    vector<IdxT> minusConnectors;
    vector<IdxT> plusConnectors;

public:
    Disjunct() {};

    void add_minus_connector(IdxT idx) { minusConnectors.push_back(idx); };
    void add_plus_connector(IdxT idx) { plusConnectors.push_back(idx); };
    void sort_connectors();

    string to_string();
};

#endif // _DISJUNCT_H
