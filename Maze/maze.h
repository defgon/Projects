#ifndef MAZE_H
#define MAZE_H

#include "matrix.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// typ pro 2D souradnice
using Position = std::pair<int, int>;

// vypis pozice do streamu
std::ostream& operator<<(std::ostream& str, const Position& p)
{
    return str << p.first << ':' << p.second;
}

// TODO: typ pro reprezentaci moznych typu policek v bludisti
//struct Tile ... NEBO using Tile = ... NEBO enum Tile ...?

enum Tile{
    tec = 1,
    hash = 2,
    S = 3,
    E = 4,
    res = 0
};

// trida pro bludiste
class Maze
{
private:
    Matrix<Tile> maze;
    Position start,end;

public:
    Maze()
        : maze(Matrix<Tile>(0,0)), start(0,0),end(0,0)
    {
    }
    ~Maze() {}
    void loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);

        if (!file.good())
            throw std::runtime_error("Failed to open file " + filename);

        std::vector<std::string> mazePlan = readWords(file);
        if (check(mazePlan)) {
            setMaze(mazePlan);
        } else{
            throw std::runtime_error("Too many S or E chars or lengths dont equal");
        }
    }

    //nastavit velikost bludiste : maze.resize(...);
    //nastavit vsechny prvky v atributu maze
    //nastavit pozice start, end
    void setMaze(std::vector<std::string>& mazePlan) {
        maze.resize((int)mazePlan.size(),(int)mazePlan.at(1).length());
        int i = 0;
        int j = 0;
        for (const auto& a : mazePlan) {
            for(const auto& s : a){
                switch (s) {
                  case '.':
                    maze(i,j) = tec;
                    break;
                  case '#':
                    maze(i,j) = hash;
                    break;
                  case 'S':
                    maze(i,j) = S;
                    start.first = i;
                    start.second = j;
                    break;
                  case 'E':
                    maze(i,j) = E;
                    end.first = i;
                    end.second = j;
                    break;
                }
                j++;
            }
            j = 0;
            i++;
        }
    }

    //precist vsechny radky ze souboru a ulozit do std::vector<std::string>
    std::vector<std::string> readWords(std::istream& str)
    {
        std::vector<std::string> result;
        std::string tile;
        while (str >> tile) {
            result.push_back(tile);
        }
        return result;
    }

    //overit, ze vsechny radky jsou stejne dlouhe
    //zkontrolovat pocet znaku 'S' a 'E'
    bool check(std::vector<std::string>& strVec) 
    {
        bool ok1 = true;
        bool ok2 = true;
        int SE = 0;
        int cols = strVec.at(1).size();
        for (const auto& a : strVec) {
            for(const auto& s : a){
                 if(s == 'S' || s == 'E'){
                     SE++;
                 }
            }
            if((int)a.size() != cols){
                ok1 = false;
            }
        }
        ok2 = SE > 2 ? false : true;
        return (ok1 && ok2);
    }

    // TODO: hledani nejkratsi cesty pomoci BFS algoritmu
    std::vector<Position> solve()
    {
        std::vector<Position> Result;
        std::vector<Position> Parent;
        std::queue<Position> Que;
        int stepCount = 0;
        int inlayer = 1;
        int nextlayer = 0;
        Matrix<int> visited(maze.getRows(),
        maze.getColumns());
        int drows[4] = {-1,1,0,0};
        int dcols[4] = {0,0,1,-1};

        Que.push(start);
        while(Que.size() > 0){
            int i = Que.front().first;
            int j = Que.front().second;
            visited(i,j) = 1;
            Que.pop();
            Position node(i,j);
            if(maze(i,j) == 4){
                break;
            }
            for(int k = 0; k < 4; k++){
                int ii = i + drows[k];
                int jj = j + dcols[k];
                if(ii >= 0 && jj >= 0 &&
                   ii < maze.getRows() && jj < maze.getColumns()
                   && maze(ii,jj) != 2 && visited(ii,jj) != 1)
                {
                    Position p;
                    p.first = ii;
                    p.second = jj;
                    Que.push(p);
                    visited(ii,jj) = 1;
                    nextlayer++;
                }
            }
            Parent.push_back(node);
            inlayer--;
            if(inlayer == 0){
                inlayer = nextlayer;
                nextlayer = 0;
                stepCount++;
            }
        }

        Position keep = end;
        while(!Parent.empty()){
            if(Parent.size() == 1 && Parent.back() != start){
                break;
                throw std::runtime_error("Nema reseni");
            }
            if(abs(Parent.back().first - keep.first +
                Parent.back().second - keep.second) == 1
                && abs(Parent.back().first - keep.first) <= 1)
            {
                Result.push_back(Parent.back());
                if(Parent.back() != start)
                    maze(Parent.back().first,Parent.back().second) = res;
                keep = Parent.back();
            }
            Parent.pop_back();
        }
        return Result;
    }

    // print do console
    void print()
    {
        for (int i = 0; i < maze.getRows();i++)
        {
            for(int j = 0; j < maze.getColumns();j++)
            {
                switch (maze(i,j))
                {
                  case tec:
                    std::cout << '.' << ' ';
                    break;
                  case hash:
                    std::cout << '#' << ' ';
                    break;
                  case S:
                    std::cout << 'S' << ' ';
                    break;
                  case E:
                    std::cout << 'E' << ' ';
                    break;
                case res:
                    std::cout << '*' << ' ';
                    break;
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif
