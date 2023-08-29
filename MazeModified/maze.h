#ifndef MAZE_H
#define MAZE_H

#include "matrix.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <map>

// typ pro 2D souradnice
using Position = std::pair<int, int>;

// vypis pozice do streamu
std::ostream& operator<<(std::ostream& str, const Position& p)
{
    return str << p.first << ':' << p.second;
}

// TODO: typ pro reprezentaci moznych typu policek v bludisti
//struct Tile ... NEBO using Tile = ... NEBO enum Tile ...?


struct Tile
{
    char type;
    bool visited;
    Position coordinates;
};


// trida pro bludiste
class Maze
{
private:
    Matrix<Tile> maze;
    Matrix<Tile> mazeCopy;
    Position start,end;
    std::map<char,Position> Letters;
public:
    Maze()
        : maze(Matrix<Tile>(0,0)),
          mazeCopy(Matrix<Tile>(0,0)),
          start(0,0),end(0,0)
    {
    }
    ~Maze() {}

    // nacteni ze souboru
    void loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);

        if (!file.good())
            throw std::runtime_error("Failed to open file " + filename);

        std::vector<std::string> mazePlan = readWords(file);
        if (check(mazePlan)) {
            setMaze(mazePlan);
        } else{
            throw std::runtime_error("More than 2 chars of the same letter");
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

    //nastavit velikost bludiste : maze.resize(...);
    //nastavit vsechny prvky v atributu maze
    void setMaze(std::vector<std::string>& mazePlan) {
        maze.resize((int)mazePlan.size(),(int)mazePlan.at(1).length());
        mazeCopy.resize((int)mazePlan.size(),(int)mazePlan.at(1).length());
        for (int i = 0; i < maze.getRows(); i++) {
            for (int j = 0; j < maze.getColumns(); j++) {
                Tile s;
                s.type = mazePlan.at(i)[j];
                s.coordinates.first = i;
                s.coordinates.second = j;
                maze(i, j) = s;
            }
        }
        mazeCopy = maze;
    }


    //overit, ze vsechny radky jsou stejne dlouhe
    //zkontrolovat pocet znaku
    bool check(std::vector<std::string>& strVec) 
    {
        bool ok = true;
        Position p;
        int cols = strVec.at(1).size();
        for (int i = 0; i < (int)strVec.size(); i++) {
            if((int)strVec.at(i).size() != cols){
                throw std::runtime_error("Lengths dont equal!");
            }
            for (int j = 0; j <= (int)strVec.at(i).size(); j++) {
                auto s = strVec.at(i)[j];
                //zjisti jestli uz obsahuje element
                if(s >= 'A' && s <= 'Z'){
                   ok = Letters.find(s) != Letters.end() ? false:true;
                   p.first = i;
                   p.second = j;
                   Letters.insert(std::make_pair(s,p));
                } else if(s < 'A' && s != '#' && s !='.' && (s > 'Z')){
                    throw std::runtime_error("Invalid character");
                }
            }
        }
        return ok;
    }

    std::vector<Position> neighbours(int i, int j){
        std::vector<Position> result;
        int drows[4] = {-1,1,0,0};
        int dcols[4] = {0,0,1,-1};
        for(int k = 0; k < 4; k++){
            int ii = i + drows[k];
            int jj = j + dcols[k];
            if(ii >= 0 && jj >= 0 &&
               ii < mazeCopy.getRows() &&
               jj < mazeCopy.getColumns() &&
               mazeCopy(ii,jj).type != '#' &&
               mazeCopy(ii,jj).visited != true)
            {
                mazeCopy(ii,jj).visited = true;
                result.push_back(mazeCopy(ii,jj).coordinates);
            }
        }
        return result;
    }

    std::vector<Position> solve_between(
         std::map<char, Position>::iterator it,
         std::map<char, Position>::iterator s)
    {
        std::queue<Position> Que;
        std::vector<Position> Parent;
        std::vector<Position> Result;

        // BFS ALG
        Que.push(it->second);
        while(Que.size() > 0)
        {
            int i = Que.front().first;
            int j = Que.front().second;
            Que.pop();
            Position node(i,j);
            if(mazeCopy(i,j).type == s->first){
                break;
            }
            for(const auto& s : neighbours(i,j)){
                Que.push(s);
            }
            Parent.push_back(node);
        }

        // Zpetna cesta
        Position keep = s->second;
        while(!Parent.empty())
        {
            if(Parent.size() == 1 && Parent.back() != start){
                break;
                throw std::runtime_error("Nema reseni");
            }
            if(abs(Parent.back().first - keep.first +
                Parent.back().second - keep.second) == 1
                && abs(Parent.back().first - keep.first) <= 1
                && abs(Parent.back().second - keep.second) <= 1)
            {
                Result.push_back(Parent.back());
                if(Parent.back() != start)
                    mazeCopy(Parent.back().first,Parent.back().second).type = '*';
                keep = Parent.back();
            }
            Parent.pop_back();
        }
        return Result;
    }

    // TODO: hledani nejkratsi cesty pomoci BFS algoritmu
    std::vector<Position> solve()
    {
        for (auto it = Letters.begin(); it != Letters.end(); ++it) {
            auto nextIt = std::next(it);
            if (nextIt != Letters.end()) {
                mazeCopy = maze;
                std::cout << std::endl;
                std::cout << "Cesta od: " << it->first << " do pismene: " << nextIt->first << std::endl;
                for (auto& x : solve_between(it,nextIt)) {
                        std::cout << " -> " << x;
                }
                std::cout << std::endl;
                print();
            }
        }
        mazeCopy = maze;
        std::vector<Position> result = solve_between(Letters.begin(),std::prev(Letters.end()));
        return result;
    }

    void print(){
        for(int i = 0; i < mazeCopy.getRows(); i++){
            for(int j = 0; j < mazeCopy.getColumns(); j++){
                std::cout << mazeCopy(i,j).type << " ";
            }
            std::cout << std::endl;
        }
    }

};



#endif
