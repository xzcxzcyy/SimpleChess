//
// Created by Banson on 2019/12/13.
//

#include "Chess.h"

Table::Table(const Map &mmap, bool myTurn)
{
    this->map = mmap;
    edges.clear();
    this->computerTurn = myTurn;
    status = unknown;
}

void Table::create(int cntOn)
{
    if (cntOn == 9)
    {
        if (haveFailed())
        {
            status = fail;
        }
        else
        {
            status = unknown;
        }
        return;
    }
    if (haveFailed())
    {
        status = fail;
        return;
    }

    Map curMap = this->map;
    bool turn = !computerTurn;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (curMap[i][j] == empty)
            {
                curMap[i][j] = computerTurn ? computer : player;
                auto next = new Table(curMap, turn);
                edges.push_back(next);
                next->create(cntOn + 1);
                curMap[i][j] = empty;
            }
        }
    }
}

bool Table::haveFailed()
{
    MapState cstd; // current standard
    if (computerTurn)
    {
        cstd = player;
    }
    else
    {
        cstd = computer;
    }
    for (int i = 0; i < 3; ++i)
    {
        bool flag = true;
        for (int j = 0; j < 3; ++j)
        {
            if (map[i][j] != cstd)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }

    for (int j = 0; j < 3; ++j)
    {
        bool flag = true;
        for (int i = 0; i < 3; ++i)
        {
            if (map[i][j] != cstd)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            return true;
        }
    }

    if (map[0][0] == cstd && map[1][1] == cstd && map[2][2] == cstd)
    {
        return true;
    }

    if (map[0][2] == cstd && map[1][1] == cstd && map[2][0] == cstd)
    {
        return true;
    }

    return false;
}

ostream &operator<<(ostream &out, const ExtendedMap &x)
{
    system("cls");
    for (const auto &i:x)
    {
        for (auto j:i)
        {
            print(out, j);
        }
        out << std::endl;
    }
    return out;
}

void Table::execute(Table *current)
{
    using std::cout;
    using std::cin;

    int boxedX = 0, boxedY = 0;
    while (!current->haveEnded())
    {
        cout << generateEMap(current->map, boxedX, boxedY);
        if (current->computerTurn)
        {
            Sleep(300);
            if (current->status == success)
            {
                for (const auto &e:current->edges)
                {
                    if (e->status == fail)
                    {
                        current = e;
                        break;
                    }
                }
            }
            else if (current->status == unknown)
            {
                for (const auto &e:current->edges)
                {
                    if (e->status == unknown)
                    {
                        current = e;
                        break;
                    }
                }
            }
        }
        else
        {
            int x, y;
            int ch;
            while ((ch = getch()) != 13)
            {
                switch (ch)
                {
                    case 224:
                        continue;

                    case 72: // up arrow
                        if (boxedX > 0)
                        {
                            --boxedX;
                            cout << generateEMap(current->map, boxedX, boxedY);
                        }
                        break;

                    case 80: // down arrow
                        if (boxedX < 2)
                        {
                            ++boxedX;
                            cout << generateEMap(current->map, boxedX, boxedY);
                        }
                        break;

                    case 75: // left arrow
                        if (boxedY > 0)
                        {
                            --boxedY;
                            cout << generateEMap(current->map, boxedX, boxedY);
                        }
                        break;

                    case 77: // right arrow
                        if (boxedY < 2)
                        {
                            ++boxedY;
                            cout << generateEMap(current->map, boxedX, boxedY);
                        }
                        break;

                    default:
                        continue;
                }
            }
            x = boxedX;
            y = boxedY;
            Map temp = current->map;
            temp[x][y] = player;
            for (const auto &e:current->edges)
            {
                if (e->map == temp)
                {
                    current = e;
                    break;
                }
            }
        }
    }

    cout << generateEMap(current->map, boxedX, boxedY) << std::endl;
    cout << "ENDING TABLE" << std::endl;
    system("pause");
    cout << generateEMap(current->map, boxedX, boxedY);

}

void Table::evaluateWisePlayer()
{
    if (edges.empty())
    {
        return;
    }
    for (const auto &e:edges)
    {
        e->evaluateWisePlayer();
    }

    for (const auto &e:edges)
    {
        if (e->status == fail)
        {
            status = success;
            return;
        }
    }

    bool flag = true;
    for (const auto &e:edges)
    {
        if (e->status != success)
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        status = fail;
        return;
    }

    status = unknown;
}

bool Table::haveEnded()
{
    if (haveFailed())
    {
        return true;
    }

    for (const auto &x:map)
    {
        for (const auto i:x)
        {
            if (i == empty)
            {
                return false;
            }
        }
    }
    return true;
}

bool setColor(WORD forceGroundColor, WORD backGroundColor)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == nullptr)
    {
        return false;
    }
    BOOL ret = SetConsoleTextAttribute(handle, forceGroundColor | backGroundColor);
    return (ret == TRUE);
}

void print(ostream &out, MapState i)
{
    switch (i)
    {
        case empty:
            setColor(FOREGROUND_GREEN, 7 << 4);
            out << " ";
            break;

        case computer:
            setColor(FOREGROUND_GREEN, BACKGROUND_RED);
            out << " ";
            break;

        case player:
            setColor(10, 10 << 4);
            out << " ";
            break;

        case boxed:
            setColor(FOREGROUND_GREEN, BACKGROUND_INTENSITY);
            out << " ";
            break;

        default:
            out << "ERROR: Map code is illegal!" << std::endl;
    }
    setColor(10, 0 << 4);
}

ExtendedMap generateEMap(const Map &map, int x, int y)
{
    ExtendedMap emap;
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            emap[i][j] = empty;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 4 * i + 1; k <= 4 * i + 3; ++k)
            {
                for (int l = 8 * j + 2; l <= 8 * j + 7; ++l)
                {
                    emap[k][l] = map[i][j];
                }
            }
        }
    }

    if (x >= 0 && x <= 2 && y >= 0 && y <= 2)
    {
        int k = 4 * x;
        int l = 8 * y;
        for (int m = l; m <= l + 9; ++m)
        {
            emap[k][m] = boxed;
            emap[k + 4][m] = boxed;
        }
        for (int m = k + 1; m <= k + 3; ++m)
        {
            emap[m][l] = emap[m][l + 1] = emap[m][l + 8] = emap[m][l + 9] = boxed;
        }
    }
    return emap;
}


void Table::welcome(Table &table)
{
    using std::cout;
    using std::endl;

    system("cls");
    cout << "This is a simple # chess" << endl << endl
         << "You will use GREEN, while the computer will use RED" << endl << endl
         << "Press up/down/left/right arrow keys to select; Press Enter to confirm." << endl << endl
         << "Enjoy yourself! /cy" << endl << endl;
    setColor(10, 0 << 4);
    system("pause");
    cout << generateEMap(table.map, 0, 0) << endl;
    table.map[1][1] = computer;
    Sleep(300);
}
