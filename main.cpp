#include "Chess.h"

using namespace std;

int main()
{
    Map map;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            map[i][j] = empty;
        }
    }
    Table table(map, false);
    Table::welcome(table);
    table.create(0);
    table.evaluateWisePlayer();
    Table::execute(&table);
    return 0;
}
