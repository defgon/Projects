#include <iostream>
#include <cstdlib>
#include <ostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <fstream>
#include <random>
#include <ctime>
#include <string>
#include <algorithm>
#include "matrix.h"

// pomocne promene a typy
const int INF = std::numeric_limits<int>::max();

    // Prevede retezec cisel na spojeni cisel
    int stringToInteger(const std::string& str) {
        int result = 0;
        for (char c : str) {
            result = result * 10 + (c - '0');
        }
        return result;
    }

// trida graph
class Graph {
private:
    Matrix<int> m;
    Matrix<int> visited;
    int fuel;

public:

    int getSize(){
        return m.getColumns();
    }

    void setFuel(int f){
       fuel = f;
    }

    // Získání matice sousednosti ze souboru
    void loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);

        if (!file.good())
            throw std::runtime_error("Failed to open file " + filename);

      // precist vsechny radky ze souboru
      std::vector<std::string> lines;
      for (std::string line; std::getline(file, line);)
        lines.emplace_back(std::move(line));
      // overit zda neni soubor prazdny
      if (lines.empty())
        throw std::runtime_error("Soubor nemuze byt prazdny");

      // vytvoreni matice
      m.resize(lines.size(), lines.size());
      std::string result;
      int length = 0;
      // zadani prvku ze souboru do matice
      for (int i = 0; i < m.getRows(); i++){
        for (int j = 0; j < (int)lines[i].length(); j++){
            const char c = lines[i][j];
            if ((c >= '0' && c <= '9') || c == ' '){
                if(c != ' '){
                    result += c;
                    if((j+1) >= (int)lines[i].length()){
                        length += result.length();
                        m(i,j - length + 1) = stringToInteger(result);
                    }
                } else{
                    length += result.length();
                    m(i,j - length) = stringToInteger(result);
                    result = "";
                }
            }
            else{
                throw std::runtime_error(std::string("Obsahuje nepripustne znaky, opravte (lze zadat pouze cisla)"));
            }
        }
        length = 0;
        result = "";
      }
      std::cout << std::endl;
      if(!MatrixChecker())
          throw std::runtime_error(std::string("Diagonalni prvky musi byt nulove"));
      m.print();
    }

    // overi ze diagonalni prvky jsou nulove
    bool MatrixChecker()
    {
        for (int i = 0; i < m.getRows(); i++)
            for (int j = 0; j <= i; j++)
                if(i == j && m(i,j) != 0)
                {return false;}
        return true;
    }

    // Ziskani matice sousednosti pomoci nahodnych cisel
    void generateRandom(int n)
    {
        if(n < 10)
        {
            m.resize(n,n);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(1, 9);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j <= i; j++)
                {
                    if(i != j)
                    {
                        m(i,j) = distribution(gen);
                    }
                }
            }
            m.reflect();
            m.print();
        } else
        {
           throw std::invalid_argument("Neplatny vstup: Cislo je vetsi nez 10");
        }
    }

    // Ziskani matice sousednosti z konzole (rucni zadani)
    void getFromConsole ()
    {
        int n;

        std::cout << "Zadejte pocet uzlu (radek = sloupcu) <= 10:" << std::endl;
        std::cin >> n;
        if(n > 10){throw std::invalid_argument("Neplatny vstup: Cislo je vetsi nez 10");}
        m.resize(n,n);

        std::cout << "Zadejte matici sousednosti:" << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                std::cout << "[" << i << "," << j << "]" << " :";
                std::cin >> m(i,j);
                while (std::cin.fail()) {
                    std::cout << "Neplatny vstup." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "[" << i << "," << j << "]" << " :";
                    std::cin >> m(i,j);
                }
            }
        }
        m.reflect();
        m.print();
    }


    // najde nejblizsi nejmensi index
    int minDistance(const std::vector<int>& dist, const std::vector<bool>& visited) {
        int minDist = INF;
        int minIndex = -1;

        for (int i = 0; i < m.getColumns(); i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

        return minIndex;
    }

    // dijkstra algoritmus
    std::vector<int> dijkstra(int from, int to)
    {
        std::vector<int> dist(m.getColumns(), INF);
        std::vector<bool> visited(m.getColumns(), false);
        std::vector<std::pair<int, std::pair<int, int>>> tracker;
        std::vector<int> solution;
        dist[from] = m(from,from); // nastavi na nulu

        // projde vsechny uzly
        for (int i = 0; i < m.getColumns() - 1; i++) {
            int u = minDistance(dist, visited);
            visited[u] = true;

            for (int j = 0; j < m.getColumns(); j++) {
                if (!visited[j] &&
                    m(u,j) != 0 &&
                    dist[u] != INF &&
                    dist[u] + m(u,j) < dist[j])
                {
                    dist[j] = dist[u] + m(u,j);
                    tracker.push_back(std::make_pair(m(u,j),std::make_pair(u,j)));
                }
            }
        }

        int number = 0;
        std::reverse(tracker.begin(), tracker.end());
        for(auto& a : tracker)
        {
            if(number != a.second.second && a.second.second <= to){
                solution.push_back(a.second.second);
                number = a.second.second;
            }
            //std::cout << a.first << " : " << a.second.first << " : " << a.second.second << std::endl;
        }
        if(fuel - dist[to] <= 0)
            throw std::invalid_argument("Nedostatek paliva");
        std::reverse(solution.begin(), solution.end());
        std::cout << "Nejkratsi vzdalenost z: " << from << " do uzlu " << to << " je: " << dist[to] << std::endl;
        return solution;
    }


};
