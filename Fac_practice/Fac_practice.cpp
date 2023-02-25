// Fac_practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>

using Tinfo = int*;

Tinfo* memory_alloc_and_fill(const int size, const int A, const int B)
{
    Tinfo* arr = new Tinfo[size];
	for (int i = 0; i < size; i++)
	{
		//arr[i] = new int(A + rand()%(B-A));
		arr[i] = new int;
		*arr[i] = A + rand() % (B - A);
	}
	return arr;
}
void free_memory(Tinfo*& arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

int pos_first_odd(const Tinfo* arr, const int size)
{
	int pos = -1;
	int i = 0;
	while (i < size && pos == -1)
	{
		if (*arr[i] % 2)
			pos = i;
		else
			i++;

	}
	return pos;
}
// with index
Tinfo* ptr_first_odd(Tinfo* arr, const int size)
{
	Tinfo* ptr = nullptr;
	int i = 0;
	while (i < size && !ptr)
	{
		if (*arr[i] % 2)
			ptr = &arr[i];
		else
			++i;
	}
	return ptr;
}
//no index
Tinfo* ptr_first_odd_noi(Tinfo* arr, const int size)
{
	Tinfo* ptr = nullptr;
	Tinfo* p = arr;
	Tinfo* p_end = arr + size;
	while (p < p_end && !ptr)
		if (p && **p % 2)
			ptr = p;
		else
			++p;
	return ptr;
}

const int max_row = 5;
const int max_col = 4;

void print(int matrix[][max_col], const int row, const int col, std::ostream& stream = std::cout)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			stream << std::setw(4) << matrix[i][j];
			stream << std::setw(4) << *(matrix[i] + j);
			stream << std::setw(4) << *(*(matrix+i) + j);
		}
		stream << std::endl;
	}
}
int summa(int matrix[][max_col], const int row, const int col)
{
	int sum = 0;
	/*for (int* i = matrix[0] ; i < matrix[0]+row*col; i++)
	{
		sum += *i;
	}*/

	for (int* i = &matrix[0][0] ; i < &matrix[0][0] + row * col; i++)
	{
		sum += *i;
	}
	return sum;
}

int summa_row(int* arr, const int col)
{
	int sum = 0;
	for (int i = 0; i < col; i++)
	{
		sum += arr[i];
	}
	return sum;
}

int count_rows_sum_odd(int matrix[][max_col], const int row, const int col)
{
	int cnt = 0;
	for (int i = 0; i < row; i++)
	{
		if (summa_row(matrix[i], col) % 2)
			cnt++;
	}
}

bool is_column_order(int matrix[][max_col], const int row, const int num_col)
{
	bool result = true;
	int i = 0;
	while (i < row - 1 && result)
		if (matrix[i][num_col] < matrix[i + 1][num_col])
			++i;
		else
			result = false;
	return result;
}

bool is_all_col_order(int matrix[][max_col], const int row, const int col)
{
	bool result = true;
	int j = 0;
	while (j < col && result)
		if (is_column_order(matrix, row, j))
			++j;
		else
			result = false;
	return result;
}
int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
