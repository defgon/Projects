#include <iostream>
#include <matrix.h>

int main()
{
    Matrix<int> m(3, 2);
    Matrix<int> n(3, 3);

    int c = 1;
    for (int i = 0; i < m.getRows(); i++)
        for (int j = 0; j < m.getColumns(); j++)
            m(i, j) = c++;

    c = 1;
    for (int i = 0; i < n.getRows(); i++)
        for (int j = 0; j < n.getColumns(); j++)
            n(i, j) = c++;

    m = m * n;
    m.print();
    return 0;
}
