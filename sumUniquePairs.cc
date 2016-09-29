#include <iostream>

using namespace std;

int prevX = -1;
int prevY = -1;
int total = 0;

void print_line()
{
    if (prevX >= 0)
    {
        cout << prevX << "\t";
        cout << prevY << "\t";
        cout << total << endl;
    }
}

int main()
{
    while (true)
    {
        int x, y, cnt;
        cin >> x >> y >> cnt;
        if (cin.eof()) break;
        if (x != prevX || y != prevY)
        {
            print_line();
            prevX = x;
            prevY = y;
            total = 0;
        }
        total += cnt;
    }
    print_line();
}
