#ifndef MAZE_H
#define MAZE_H
///////////////////////////////////////////// MUJ
/// MAZE.h//////////////////////////////////////
#include "matrix.h"
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

// typ pro 2D souradnice
using Position = std::pair<int, int>;

// vypis pozice do streamu
std::ostream &operator<<(std::ostream &str, const Position &p) {
  return str << p.first << ':' << p.second;
}

// typ pro reprezentaci moznych typu policek v bludisti
// struct Tile ... NEBO using Tile = ... NEBO enum Tile ...?

// alternativni zpusob reprezentace (zde nebude dokoncen)

struct Tile {
  char type;
  int visited;
  //Tile* parent;
  Position coordinates;
  Position parent;
};

// trida pro bludiste
class Maze {
private:
  Matrix<Tile> maze;

  Matrix<Tile> maze_copy;

  Position start, end;
  std::map<char, Position> mapa;

  bool isPossible(const Position &p) {
    return (isValid(p) && isFree(p) && !isVisited(p));
  }

  bool isValid(const Position &p) {
    return p.first >= 0 && p.first < maze_copy.getRows() && p.second >= 0 &&
           maze_copy.getColumns();
  }

  bool isFree(const Position &p) {
    if(maze(p.first, p.second).type == '.' ||
       (maze(p.first, p.second).type <= 'Z' &&
       maze(p.first, p.second).type >= 'A')){
        return true;
    } else
        return false;
  }

  bool isVisited(const Position &p) {
    return maze_copy(p.first, p.second).visited != 0 ? true : false;
  }

  bool justOne(char c) {
    for (auto it = mapa.begin(); it != mapa.end(); it++) {
      if (it->first == c) {
        return 0;
      }
    }
    return 1;
  }

public:
  void loadFromFile(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.good())
      throw std::runtime_error("Failed to open file " + filename);

    // precist vsechny radky ze souboru
    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);)
      lines.emplace_back(std::move(line));

    if (lines.empty())
      throw std::runtime_error("Maze cannot be empty");

    // nastavit velikost bludiste
    maze.resize(lines.size(), lines[0].length());

    for (int i = 0; i < maze.getRows(); i++) {
      // overit, ze vsechny radky jsou stejne dlouhe
      if ((int)lines[i].length() != maze.getColumns())
        throw std::runtime_error("All lines must have the same length");

      // nastavit vsechny prvky v atributu maze
      for (int j = 0; j < maze.getColumns(); j++) {
        const char c = lines[i][j];
        if (c != 0) {
          if (c <= 'Z' && c >= 'A' && justOne(c) != false) {
            mapa.insert(std::make_pair(c, std::make_pair(i, j)));
            maze(i, j).type = c;
            maze(i,j).visited = 0;
          } else if (c == '#' || c == '.') {
            maze(i, j).type = c;
            maze(i,j).visited = 0;
          } else {
            throw std::runtime_error(
                std::string("Input contains an invalid character: ") + c);
          }
        }
      }
    }
  }

  std::vector<Position> solveFromTo(std::map<char, Position>::iterator s,
                                    std::map<char, Position>::iterator e) {
    start = s->second;
    end = e->second;
    // algoritmus BFS
    std::queue<Position> q;
    q.push(start);
    maze_copy(start.first, start.second).visited = 1;

    while (!q.empty()) {
      // precist novy prvek
      const Position current = q.front();
      q.pop();
      // kontrola konce
      if (current == end){
        break;
      }
      for (int i = -1; i <= 1; i += 2)
      {
        const Position p1 = {current.first + i, current.second};
        if (isPossible(p1)) {
          q.push(p1);
          maze_copy(p1.first, p1.second).visited =
              maze_copy(current.first, current.second).visited + 1;
        }
        const Position p2 = {current.first, current.second + i};
        if (isPossible(p2)) {
          q.push(p2);
          // zaznam navstiveneho policka jako "vzdalenost od startu + 1"
          maze_copy(p2.first, p2.second).visited =
              maze_copy(current.first, current.second).visited + 1;
        }
      }
    }

    // rekonstrukce cesty
    int counter = maze_copy(end.first, end.second).visited;
    std::vector<Position> path(counter - 1);
    for (Position current = end; current != start;) {
        path[counter - 2] = current;
        counter--;
        for (int i = -1; i <= 1; i += 2) {
            const Position p1 = {current.first + i, current.second};
            if (maze_copy(p1.first, p1.second).visited == counter) {
                current = p1;
                // vyznaceni cesty v bludisti
                if (counter > 1)
                    maze_copy(p1.first, p1.second).type = '*';
                break;
            }
            const Position p2 = {current.first, current.second + i};
            if (maze_copy(p2.first, p2.second).visited == counter) {
                current = p2;
                // vyznaceni cesty v bludisti
                if (counter > 1)
                    maze_copy(p2.first, p2.second).type = '*';
                break;
            }
        }
    }

    if (counter != 1)
        throw std::runtime_error("backtracking did not find start");
    return path;
  }

  std::vector<Position> solve() {
    for (auto it = mapa.begin(); it != std::prev(mapa.end()); ++it) {
      std::cout << "Maze:" << std::endl;
      maze_copy = maze;
      for (auto i : solveFromTo(it, std::next(it)))
        std::cout << " > " << i;
      std::cout << std::endl;
      print();
      std::cout << std::endl;
    }
    maze_copy = maze;
    std::vector<Position> result =
        solveFromTo(mapa.begin(), std::prev(mapa.end()));
    return result;
  }

  // print do console
  void print() {
    for (int i = 0; i < maze_copy.getRows(); i++) {
      for (int j = 0; j < maze_copy.getColumns(); j++) {
        std::cout << maze_copy(i, j).type;
      }
      std::cout << "\n";
    }
  }
};

#endif
