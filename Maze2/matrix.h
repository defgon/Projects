#include <ostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Matrix
{
private:
    int rows = 0;
    int cols = 0;
    std::vector<T> data;

public:
    Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) = default;

    Matrix(int rows, int cols) : rows(rows), cols(cols)
    {
        data.resize(rows * cols);
    }

    void resize(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        data.resize(rows * cols);
    }

    int getRows() const
    {
        return rows;
    }

    int getColumns() const
    {
        return cols;
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

// operátor pro výpis matice
template <typename T>
std::ostream& operator<<(std::ostream& str, const Matrix<T>& matrix)
{
    str << "[";
    for (int i = 0; i < matrix.getRows(); i++) {
        if (i > 0)
            str << " ";
        str << "[";
        for (int j = 0; j < matrix.getColumns(); j++) {
            if (j > 0)
                str << ", ";
            str << matrix(i, j);
        }
        str << "]";
        if (i < matrix.getRows() - 1)
            str << std::endl;
    }
    return str;
}

// operátor pro sčítání matice a čísla
template <typename T>
Matrix<T> operator+(const Matrix<T>& matrix, T value)
{
    Matrix<T> result(matrix.getRows(), matrix.getColumns());

    for (int i = 0; i < matrix.getRows(); i++)
        for (int j = 0; j < matrix.getColumns(); j++)
            result(i, j) = matrix(i, j) + value;

    return result;
}

// operátor pro sčítání čísla a matice
template <typename T>
Matrix<T> operator+(T value, const Matrix<T>& matrix)
{
    return matrix + value;
}

// operátor pro odčítání matice a čísla
template <typename T>
Matrix<T> operator-(const Matrix<T>& matrix, T value)
{
    Matrix<T> result(matrix.getRows(), matrix.getColumns());

    for (int i = 0; i < matrix.getRows(); i++)
        for (int j = 0; j < matrix.getColumns(); j++)
            result(i, j) = matrix(i, j) - value;

    return result;
}

// operátor pro odčítání čísla a matice
template <typename T>
Matrix<T> operator-(T value, const Matrix<T>& matrix)
{
    Matrix<T> result(matrix.getRows(), matrix.getColumns());

    for (int i = 0; i < matrix.getRows(); i++)
        for (int j = 0; j < matrix.getColumns(); j++)
            result(i, j) = value - matrix(i, j);

    return result;
}

// operátor pro násobení matice a čísla
template <typename T>
Matrix<T> operator*(const Matrix<T>& matrix, T value)
{
    Matrix<T> result(matrix.getRows(), matrix.getColumns());

    for (int i = 0; i < matrix.getRows(); i++)
        for (int j = 0; j < matrix.getColumns(); j++)
            result(i, j) = matrix(i, j) * value;

    return result;
}

// operátor pro násobení čísla a matice
template <typename T>
Matrix<T> operator*(T value, const Matrix<T>& matrix)
{
    return matrix * value;
}

// operátor pro dělení matice a čísla
template <typename T>
Matrix<T> operator/(const Matrix<T>& matrix, T value)
{
    Matrix<T> result(matrix.getRows(), matrix.getColumns());

    for (int i = 0; i < matrix.getRows(); i++)
        for (int j = 0; j < matrix.getColumns(); j++)
            result(i, j) = matrix(i, j) / value;

    return result;
}

// operátor pro dělení čísla a matice
template <typename T>
Matrix<T> operator/(T value, const Matrix<T>& matrix)
{
    Matrix<T> result(matrix.getRows(), matrix.getColumns());

    for (int i = 0; i < matrix.getRows(); i++)
        for (int j = 0; j < matrix.getColumns(); j++)
            result(i, j) = value / matrix(i, j);

    return result;
}

// operátor pro sčítání matic
template <typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
{
    if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns())
        throw std::invalid_argument("Matrix dimensions do not match.");

    Matrix<T> result(a.getRows(), a.getColumns());

    for (int i = 0; i < a.getRows(); i++)
        for (int j = 0; j < a.getColumns(); j++)
            result(i, j) = a(i, j) + b(i, j);

    return result;
}

// operátor pro odčítání matic
template <typename T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
{
    if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns())
        throw std::invalid_argument("Matrix dimensions do not match.");

    Matrix<T> result(a.getRows(), a.getColumns());

    for (int i = 0; i < a.getRows(); i++)
        for (int j = 0; j < a.getColumns(); j++)
            result(i, j) = a(i, j) - b(i, j);

    return result;
}

// operátor pro násobení matic
template <typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
{
    if (a.getColumns() != b.getRows())
        throw std::invalid_argument("Matrix dimensions do not match.");

    Matrix<T> result(a.getRows(), b.getColumns());

    for (int i = 0; i < a.getRows(); i++)
        for (int j = 0; j < b.getColumns(); j++) {
            T sum = 0;
            for (int k = 0; k < a.getColumns(); k++) {
                sum += a(i, k) * b(k, j);
            }
            result(i, j) = sum;
        }

    return result;
}

