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

	srand(time(NULL));
	setlocale(LC_ALL, "Ukr");
	int n = 10;
	Matrix A(2, 2);
	Matrix B(2, 2);
	//for (int i = 0; i < n; ++i)
	//	A[i] = new int[n];
	//int** B = new int* [n];
	//for (int i = 0; i < n; ++i)
	//	B[i] = new int[n];
	//int** RES = new int* [n];
	//for (int i = 0; i < n; ++i)
	//	RES[i] = new int[n];

	//SetRandom(A, 2);
	//SetRandom(B, 2);
	A.SetRandom();
	B.SetRandom();
	std::cout << "\nМатриця А: " << std::endl;
	//Print_Matrix(A, 2);
	std::cout << A;
	std:: cout << std::endl;
	std::cout << "Матриця B: " << std::endl;
	//Print_Matrix(B, 2);
	std::cout << B;
	std::cout << std::endl;
	std::cout << "Результат множення матриць AxB методом Штрассена: " << std::endl;
	Matrix RES = A*B;
	//Print_Matrix(RES, n);
	std::cout << RES;
}

