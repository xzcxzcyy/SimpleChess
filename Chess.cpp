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
    mapState cstd; // current standard
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

ostream &operator<<(ostream &out, const Table &x)
{
    for (const auto &a:x.map)
    {
        for (auto i:a)
        {
            out << i << " ";
        }
        out << std::endl;
    }
    return out;
}

void Table::execute(Table *current)
{
    using std::cout;
    using std::cin;

    while (!current->haveEnded()) //TODO: Rewrite the condition
    {
        cout << *current;
        if (current->computerTurn)
        {
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
            do
            {
                cin >> x >> y;
            } while (x < 0 || x > 2 || y < 0 || y > 2);

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

    cout << "ENDING TABLE" << std::endl;
    cout << *current;

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
