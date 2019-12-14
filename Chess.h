//
// Created by Banson on 2019/12/13.
//

#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <array>

using std::vector;
using std::array;

class Table;
class Cord;
typedef Table *Edge;
typedef array<array<int, 3>, 3> Map;

enum mapState
{
    empty, computer, player
};

class Table
{
private:
    enum Status
    {
        success, unknown, fail
    };
    Map map{};
    vector<Edge> edges;
    bool myTurn;
    Status status;
public:
    explicit Table(const Map &mmap, bool myTurn);
    void addEdge(Edge mPointer);
    void setStatus(Status mStatus);
    int operator()(int i, int j);
    const vector<Edge> &getEdges();
    bool isMyTurn();
    Status getStatus();
    void create(int cntOn);
};


#endif //CHESS_H
