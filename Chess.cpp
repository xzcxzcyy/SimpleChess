//
// Created by Banson on 2019/12/13.
//

#include "Chess.h"

Table::Table(const Map &mmap, bool myTurn)
{
    this->map = mmap;
    edges.clear();
    this->myTurn = myTurn;
    status = unknown;
}

void Table::addEdge(Edge mPointer)
{
    edges.push_back(mPointer);
}

void Table::setStatus(Table::Status mStatus)
{
    this->status = mStatus;
}

int Table::operator()(int i, int j)
{
    return map[i][j];
}

const vector<Edge> &Table::getEdges()
{
    return edges;
}

bool Table::isMyTurn()
{
    return myTurn;
}

Table::Status Table::getStatus()
{
    return status;
}

void Table::create(int cntOn)
{
    if (cntOn == 9)
    {
        return;
    }

    Map curMap = this->map;
    bool turn = !myTurn;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (curMap[i][j] == empty)
            {
                curMap[i][j] = myTurn ? computer : player;
                auto next = new Table(curMap, turn);
                edges.push_back(next);
                next->create(cntOn + 1);
                curMap[i][j] = empty;
            }
        }
    }
}
