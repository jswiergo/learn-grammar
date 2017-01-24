#include <algorithm>
#include <sstream>
#include "disjunct.h"

void Disjunct::sort_connectors()
{
    sort(minusConnectors.begin(), minusConnectors.end());
    sort(plusConnectors.begin(), plusConnectors.end());
}

string Disjunct::to_string()
{
    stringstream ss;
    bool first = true;

    for (auto it = minusConnectors.begin(); it != minusConnectors.end(); ++it)
    {
        if (!first) ss << "\t";
        first = false;
        ss << *it;
    }
    if (!first) ss << "\t";
    ss << "|";
    for (auto it = minusConnectors.begin(); it != minusConnectors.end(); ++it)
    {
        ss << "\t" << *it;
    }

    return ss.str();
}
