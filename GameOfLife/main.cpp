#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "matrix.h"

enum CellState : std::uint8_t
{
    ALIVE = 1,
    DEAD = 0
};

void readFile(Matrix<CellState> &board, const std::string &filename)
{
    std::ifstream file(filename);
    if ( ! file.good())
        throw std::runtime_error("file could not be opened");
    
    int width = 0;
    int height = 0;
    file >> width >> height;
    if (width <= 0 || height <= 0)
        throw std::runtime_error("invalid size of the board");
    board.resize(height, width);
    std::string lineskip;
    std::getline(file, lineskip);
    for (int i = 0; i < height; i++)
    {
        std::string line;
        std::getline(file, line);
        if ((int)line.size() == width)
        {
            for (int j = 0; j < width; j++)
            {
            if (line[j] == 'X')
                board(i, j) = ALIVE;
            else if (line[j] == '-')
                board(i, j) = DEAD;
            else
                throw std::runtime_error(std::string("invalid char ") + line[j]);
            }
        }
        else
            throw std::runtime_error("invalid lenght of line " + line);
    }
    
}

int getNeighbors(const Matrix<CellState> &input, int i, int j)
{
    int count = 0;
    int drows[8] = {-1,1,0,0,1,1,-1,-1};
    int dcols[8] = {0,0,1,-1,-1,1,-1,1};

    for(int k = 0; k < 8; k++){
        int ii = i + drows[k];
        int jj = j + dcols[k];
        if(ii >= 0 && jj >= 0 &&
           ii <= input.getRows() &&
           jj <= input.getColumns())
        {
            count += input(ii,jj) == ALIVE ? 1:0;
        }
    }
    return count;
}

void update(Matrix<CellState> &input, Matrix<CellState> &output)
{
    for (int i = 0; i < input.getRows(); i++) {
        for (int j = 0; j < input.getColumns(); j++) {
            int alive_neighbors = getNeighbors(input, i, j);
            if (input(i, j) == ALIVE)
            {
                if (alive_neighbors < 2)
                    output(i, j) = DEAD;
                else if (alive_neighbors < 4)
                    output(i, j) = ALIVE;
                else
                    output(i, j) = DEAD;
            }
            else
            {
                if (alive_neighbors == 3)
                    output(i, j) = ALIVE;
                else
                    output(i, j) = DEAD;
            }
        }
    }
    std::swap(input, output);
}


void print(const Matrix<CellState> input){
    for (int i = 0; i < input.getRows(); i++) {
        for (int j = 0; j < input.getColumns(); j++) {
            if(input(i,j) == ALIVE)
                std::cout << "X";
            else
                std::cout << "-";
        }
        std::cout << std::endl;
    }
}

std::pair<bool,int> alive(const Matrix<CellState> input) {
    std::pair<bool,int> result;
    int countAlive = 0;
    for (int i = 0; i < input.getRows(); i++)
        for (int j = 0; j < input.getColumns(); j++)
            countAlive += input(i,j) == ALIVE ? 1:0;
    result.first = countAlive > 0 ? true:false;
    result.second = countAlive;
    return result;
}

int main()
{
    // nacti desku ze souboru
    Matrix<CellState> in_board;
    readFile(in_board, "C:\\Users\\Mikovec-PC\\Desktop\\FJFI2\\4 semestr\\18PRC2\\GameOfLife\\input.txt");

    // napln novou desku
    Matrix<CellState> board;
    board.resize(10 * in_board.getRows(), 10 * in_board.getColumns());
    int offset_i = 5 * in_board.getRows();
    int offset_j = 5 * in_board.getColumns();
    for (int i = 0; i < board.getRows(); i++){
        for (int j = 0; j < board.getColumns(); j++){
            if (i >= offset_i && i <= offset_i + in_board.getRows() &&
                j >= offset_j && j <= offset_j + in_board.getColumns())
                board(i, j) = in_board(i - offset_i, j - offset_j);
            else
                board(i, j) = DEAD;
        }
    }


    // ukazuj hru
    Matrix<CellState> temp(board.getRows(), board.getColumns());
    while (alive(board).first)
    {
        // iterace
        update(board, temp);
        
        //vizualizace
        print(board);
        std::cout << std::endl << "Pocet zivych bunek je: " << alive(board).second;
        
        // pauza
        std::cin.get();
    }

    
    return 0;
}
