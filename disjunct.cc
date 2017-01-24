#include <algorithm>
#include <sstream>
#include "disjunct.h"

void Disjunct::sort_connectors()
{
    sort(minusConnectors.begin(), minusConnectors.end());
    sort(plusConnectors.begin(), plusConnectors.end());
}

string Disjunct::to_string() const
{
    stringstream ss;
    bool first = true;

    for (auto conn: minusConnectors)
    {
        if (!first) ss << "\t";
        first = false;
        ss << conn;
    }
    if (!first) ss << "\t";
    ss << "|";
    for (auto conn: plusConnectors)
    {
        ss << "\t" << conn;
    }

    return ss.str();
}
