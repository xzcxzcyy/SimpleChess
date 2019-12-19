//
// Created by Banson on 2019/12/13.
//

#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <array>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>

using std::vector;
using std::array;
using std::ostream;


enum MapState
{
    empty, computer, player, boxed
};

class Table;
typedef Table *Edge;
typedef array<array<MapState, 3>, 3> Map;
typedef array<array<MapState, 26>, 13> ExtendedMap;

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

    static void execute(Table *current);
    static void welcome(Table &table);

};

ostream &operator<<(ostream &out, const ExtendedMap &x);
bool setColor(WORD forceGroundColor, WORD backGroundColor);
void print(ostream &out, MapState i);
ExtendedMap generateEMap(const Map &map, int x, int y);

#endif //CHESS_H
