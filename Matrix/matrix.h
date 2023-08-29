#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include <iostream>

template <typename T>
class Matrix
{
private:
    int rows = 0;
    int cols = 0;
    std::vector<T> data;

public:
    Matrix(Matrix&&) = default;
    Matrix& operator=(const Matrix& rhs) = default;
    Matrix& operator=(Matrix&&) = default;
    Matrix(const Matrix &src) = default;

    Matrix(int rows, int cols)
    : rows(rows), cols(cols)
    {
        data.resize(rows * cols);
    }

    ~Matrix(){
        data.clear();
    }

    int getRows() const
    {
        return rows;
    }

    void print() const
    {
        for (int i = 0;
             i < this->getRows() * this->getColumns();
             i++)
            std::cout << this->getData()[i] << " ";
        std::cout << std::endl;
    }

    int getColumns() const
    {
        return cols;
    }

    std::vector<int> getDim() const
    {
        return std::vector<int>{this->getRows(),
                    this->getColumns()};
    }

    T& operator()(int i, int j)
    {
        return data[i * cols + j];
    }

    const T& operator()(int i, int j) const
    {
        return data[i * cols + j];
    }

    const T* getData() const
    {
        return data.data();
    }
};

// operator* číslo
template <typename T>
Matrix<T> operator*(T alfa, Matrix<T>& a)
{
    Matrix<T> c(a.getRows(),a.getColumns());
    for(int i = 0; i < a.getRows(); i++){
        for(int j = 0; j < a.getColumns(); j++){
            c(i, j) = alfa * a(i, j);
        }
    }
    return c;
}

template <typename T>
Matrix<T> operator*(Matrix<T>& a, T alfa)
{
    return alfa*a;
}

// operator+ číslo
template <typename T>
Matrix<T> operator+(T alfa, Matrix<T>& a)
{
    Matrix<T> c(a.getRows(),a.getColumns());
    for(int i = 0; i < a.getRows(); i++){
        for(int j = 0; j < a.getColumns(); j++){
            c(i, j) = alfa + a(i, j);
        }
    }
    return c;
}

template <typename T>
Matrix<T> operator+(Matrix<T>& a, T alfa)
{
    return alfa+a;
}

// operator- číslo
template <typename T>
Matrix<T> operator-(T alfa, Matrix<T>& a)
{
    Matrix<T> c(a.getRows(),a.getColumns());
    for(int i = 0; i < a.getRows(); i++){
        for(int j = 0; j < a.getColumns(); j++){
            c(i, j) = alfa - a(i, j);
        }
    }
    return c;
}

template <typename T>
Matrix<T> operator-(Matrix<T>& a, T alfa)
{
    return -(alfa) + a;
}

// operator/ číslo
template <typename T>
Matrix<T> operator/(T alfa, Matrix<T>& a)
{
    Matrix<T> c(a.getRows(),a.getColumns());
    for(int i = 0; i < a.getRows(); i++){
        for(int j = 0; j < a.getColumns(); j++){
            c(i, j) = alfa / a(i, j);
        }
    }
    return c;
}

template <typename T>
Matrix<T> operator/(Matrix<T>& a, T alfa)
{
    Matrix<T> c(a.getRows(),a.getColumns());
    for(int i = 0; i < a.getRows(); i++){
        for(int j = 0; j < a.getColumns(); j++){
            c(i, j) = a(i, j) / alfa;
        }
    }
    return c;
}

// operator+ Matice | Matice

template <typename T>
Matrix<T> operator+(Matrix<T>& a, Matrix<T>& b)
{
    if(a.getDim() == b.getDim())
    {
        Matrix<T> c(a.getRows(),a.getColumns());
        for(int i = 0; i < a.getColumns(); i++){
            for(int j = 0; j <= a.getRows(); j++){
                c(i, j) = a(i, j) + b(i, j);
            }
        }
        return c;
    } else{
        throw std::invalid_argument( "Dimensions dont match!" );
    }
}

// operator- Matice | Matice

template <typename T>
Matrix<T> operator-(Matrix<T>& a, Matrix<T>& b)
{
    if(a.getDim() == b.getDim())
    {
        Matrix<T> c(a.getRows(),a.getColumns());
        for(int i = 0; i < a.getColumns(); i++){
            for(int j = 0; j <= a.getRows(); j++){
                c(i, j) = a(i, j) - b(i, j);
            }
        }
        return c;
    } else{
        throw std::invalid_argument( "Dimensions dont match!" );
    }
}

// operator* Matice | Matice

template <typename T>
Matrix<T> operator*(Matrix<T>& a, Matrix<T>& b)
{
    if(a.getColumns() == b.getRows()){
        Matrix<T> c(b.getRows(),a.getColumns());
        for(int i = 0; i < a.getColumns(); i++)
        {
            for(int j = 0; j < b.getRows(); j++)
            {
                for(int l = 0; l < a.getColumns(); l++)
                {
                    c(i, j) = c(i,j) + a(i, l) * b(l, j);
                }
            }
        }
        return c;
    } else{
        throw std::invalid_argument( "Right matrix columns, "
                                     "dont equal left matrix rows!" );
    }
}


template <int rows, int cols, typename T>
class StaticMatrix
{
private:
    T data[rows][cols];

public:
};


#endif // MATRIX_H
