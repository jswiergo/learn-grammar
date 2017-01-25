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

    ss << minusConnectors.size();
    for (auto conn: minusConnectors)
    {
        ss << " " << conn;
    }
    ss << " " << plusConnectors.size();
    for (auto conn: plusConnectors)
    {
        ss << " " << conn;
    }

    return ss.str();
}
