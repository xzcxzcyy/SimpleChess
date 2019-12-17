//
// Created by Banson on 2019/12/13.
//

#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <array>
#include <iostream>

using std::vector;
using std::array;
using std::ostream;

class Table;
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
    bool computerTurn;
    Status status;

    bool haveFailed();
    bool haveEnded();

public:
    explicit Table(const Map &mmap, bool myTurn);
    void create(int cntOn);
    void evaluateWisePlayer();
    friend ostream &operator<<(ostream &out, const Table &x);
    static void execute(Table *current);
};


#endif //CHESS_H
