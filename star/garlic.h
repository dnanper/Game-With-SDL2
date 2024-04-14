#ifndef GARLIC_H
#define GARLIC_H

#include "../collision/CollisionHandler.h"
#include "../map/TileLayer.h"
#include "../map/GameMap.h"
#include "../inc/SDL.h"
#include <math.h>
#include<iostream>
#include<utility>
#include<stack>
#include<set>
#include<limits>
#include<cstring>
#include <iostream>

#define ROW 90
#define COL 90
#define FLT_MAX 10000

using namespace std;

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> > pPair;

class garlic
{
    public:
        struct cell 
        {
            int parent_i, parent_j;
            // f = g + h
            double f, g, h;
        };
        TileMap Map = CollisionHandler::GetInstance()->GetTileMap();

        static bool isDestination(int row, int col, Pair dest);
        static double calculateHValue(int row, int col, Pair dest);
        static Pair tracePath(cell cellDetails[][COL], Pair dest);
        static Pair aStarSearch(TileMap grid, Pair src, Pair dest);
        static bool isValid(int row, int col);
        static bool isUnBlocked(vector<vector<int>> grid, int row, int col)
        {
            if (grid[row][col] == 0) return (true);
            else return (false);
            // SDL_Rect rect;
            // rect.x = col * 30;
            // rect.y = row * 30;
            // rect.w = 30;
            // rect.h = 30;
            // return !(CollisionHandler::GetInstance()->MapCollision(rect));
        }



};

#endif  // GARLIC_H
