#include <iostream>

#include "Matrix.h"

int main()
{
    Row row1(2), row2(2), row3;
    row1[0] = 12; row1[1] = 10;
    row2[0] = 22; row2[1] = 20;

    row3 = row1 + row2;

    std::cout << row3[0] << ' ' << row3[1] << '\n';

    Matrix m(2, 2); m[0][0] = 5; m[1][1] = 442;

    std::cout << m;

    Matrix k(m);
    Matrix g = m;

   //while(1)
   //    Matrix d(m);

    std::cout << k << g;
}

