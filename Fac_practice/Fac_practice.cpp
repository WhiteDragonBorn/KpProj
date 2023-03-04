// Fac_practice.cpp : This file contains the 'main' function.

#include <iostream>
#include <Windows.h>
#include <functional>
#include <iomanip>

using TInfo = int*;
using TCompareInt = std::function<bool(int, int)>;

TInfo memory_alloc(const int size);
void free_memory(int*& arr);
void print_arr(int* begin, const int* end);
void print_arr(int* arr, const int size);
void fill_arr(int* arr, const int size, const int A, const int B);
int count_even_pair(int* arr, const int size);
int count_even_pair_unique(int* arr, const int size);
void reverse_arr(int* arr, const int left, const int right);
void shift_to_left(int* arr, const int size, const int pos);
void remove_from_pos(int* arr, int& size, const int pos);
void cyclic_shift_to_left(int* arr, const int size);
void shift_to_right(int* arr, const int left, const int right);
void expand_arr_to_right(int*& arr, int& size, int amount);
void insert_at_pos(int* &arr, int& size, const int pos, const int elem);
void cyclic_shift_to_right(int* arr, const int left, const int right);
void remove_odd(int*& arr, int& size);
void compress_odd(int* arr, const int size);
void filter_even(int* arr, const int size);
void sort_bubble_fromback(int* arr, const int size, TCompareInt compare);
void sort_bubble_fromfront(int* arr, const int size, TCompareInt compare);
void selection_sort(int* arr, const int size, TCompareInt compare);
void insert_sort(int* arr, const int size, TCompareInt compare);

TInfo* memory_alloc_and_fill(const int size, const int A, const int B);
void free_memory(TInfo*& arr, int size);


// «адача о одномерном массиве использу€ указатели
// Returns a pointer to array of pointers (size) of single int in [A, B)
TInfo* memory_alloc_and_fill(const int size, const int A, const int B)
{
	TInfo* arr = new TInfo[size];
	for (int i = 0; i < size; ++i)
	{
		//arr[i] = new int(A + rand()%(B-A));
		arr[i] = new int;
		*arr[i] = A + rand() % (B - A);
	}
	return arr;
}
// Destructor for memory_alloc_and_fil(...)
void free_memory(TInfo*& arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		delete arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

int pos_first_odd(const TInfo* arr, const int size)
{
	int pos = -1;
	int i = 0;
	while (i < size && pos == -1)
	{
		if (*arr[i] % 2)
			pos = i;
		else
			++i;

	}
	return pos;
}
// with index
TInfo* ptr_first_odd(TInfo* arr, const int size)
{
	TInfo* ptr = nullptr;
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
TInfo* ptr_first_odd_noi(TInfo* arr, const int size)
{
	TInfo* ptr = nullptr;
	TInfo* p = arr;
	TInfo* p_end = arr + size;
	while (p < p_end && !ptr)
		if (p && **p % 2)
			ptr = p;
		else
			++p;
	return ptr;
}
//


// ќперации со статическими матрицами
const int max_row = 5;
const int max_col = 4;

void print(int matrix[][max_col], const int row, const int col, std::ostream& stream = std::cout)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; j++)
		{
			stream << std::setw(4) << matrix[i][j];
			//stream << std::setw(4) << *(matrix[i] + j);
			//stream << std::setw(4) << *(*(matrix+i) + j);
		}
		stream << std::endl;
	}
}
int summa(int matrix[][max_col], const int row, const int col)
{
	int sum = 0;
	/*for (int* i = matrix[0] ; i < matrix[0]+row*col; ++i)
	{
		sum += *i;
	}*/

	for (int* i = &matrix[0][0] ; i < &matrix[0][0] + row * col; ++i)
	{
		sum += *i;
	}
	return sum;
}

int summa_row(int* arr, const int col)
{
	int sum = 0;
	for (int i = 0; i < col; ++i)
	{
		sum += arr[i];
	}
	return sum;
}

int count_rows_sum_odd(int matrix[][max_col], const int row, const int col)
{
	int cnt = 0;
	for (int i = 0; i < row; ++i)
	{
		if (summa_row(matrix[i], col) % 2)
			cnt++;
	}
	return cnt;
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
// 

// јлгоритм сортировки матрицы
// упор€дочить строки по их суммам
void sorting_matrix(int matrix[][max_col], const int row, const int col)
{
	int* sum = new int[row];
	for (int i = 0; i < row; ++i)
	{
		sum[i] = summa_row(matrix[i], col);
	}

	for (int count = row ; count >=2; --count)
	{
		for (int i = 0; i < count - 1; ++i)
		{
			if (sum[i] < sum[i + 1])
			{
				std::swap(sum[i], sum[i+1]);
				std::swap(matrix[i], matrix[i + 1]);
			}
		}
	}

	delete[]sum;
	sum = nullptr;
}

//  сортировка через карту индексов

int* sorting_matrix_map(int matrix[][max_col], const int row, const int col)
{
	int* sum = new int[row];
	int* map = new int[row];

	for (int i = 0; i < row; ++i)
	{
		sum[i] = summa_row(matrix[i], col);
		map[i] = i;
	}

	for (int count = row; count >= 2; --count)
	{
		for (int i = 0; i < count - 1; ++i)
		{
			if (sum[i] < sum[i + 1])
			{
				std::swap(sum[i], sum[i + 1]);
				std::swap(map[i], map[i + 1]);
			}
		}
	}
	delete[]sum;
	sum = nullptr;

	return map;
}



void print_matrix_map(int matrix[][max_col], const int row, const int col, int* map, char* message, std::ostream& stream = std::cout)
{
	stream << message << "\n";
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			stream << matrix[map[i]][j] << " ";
		}
		stream << "\n";
	}
}

int main()
{
	srand(time(NULL));
	int size = 10;
	TInfo arr = memory_alloc(size);
	fill_arr(arr, size, 0, 10);
	print_arr(arr, arr + size);
	std::cout << std::setw(2) << std::endl;
	//print_arr(arr, size);
	
	/*int even_pair = count_even_pair(arr, size);
	int unique_pair = count_even_pair_unique(arr, size);
	std::cout << even_pair << " " << unique_pair;*/

	reverse_arr(arr, 0, size-1);
	print_arr(arr, arr + size);

	std::cout << std::endl;

	shift_to_left(arr, size, size / 2);
	print_arr(arr, arr + size);

	std::cout << std::endl;

	remove_from_pos(arr, size, size / 2);
	print_arr(arr, arr + size);

	std::cout << std::endl;

	cyclic_shift_to_left(arr, size);
	print_arr(arr, arr + size);

	std::cout << std::endl;

	remove_odd(arr, size);
	//compress_odd(arr, size);
	print_arr(arr, arr + size);

	int pos_to_insert = size - 1;
	int some_elem = 123;
	insert_at_pos(arr, size, pos_to_insert, some_elem); // insert between arr[size-2] and arr[size-1]
	insert_at_pos(arr, size, -1, some_elem); // push_back
	std::cout << std::endl;
	print_arr(arr, arr + size);

	sort_bubble_fromfront(arr, size, [](int x, int y) { return x > y; });
	std::cout << std::endl;
	print_arr(arr, arr + size);
	sort_bubble_fromback(arr, size, [](int x, int y) { return x < y; });
	std::cout << std::endl;
	print_arr(arr, arr + size);
	reverse_arr(arr, 0, size - 1);
	std::cout << std::endl;
	print_arr(arr, arr + size);
	selection_sort(arr, size, [](int x, int y) {return x > y; });
	std::cout << std::endl;
	print_arr(arr, arr + size);
	insert_sort(arr, size, [](int x, int y) {return x > y; });
	std::cout << std::endl;
	print_arr(arr, arr + size);

	free_memory(arr);

	int matrix[max_row][max_col]{ {1,1,1,1}, {2,2,2,2}, {3,3,3,3}, {4,4,4,4} , {5,5,5,5} };
	int* map = sorting_matrix_map(matrix, max_row, max_col);
	//print_matrix_map(matrix, max_row, max_col, map, "zb");




	return 0;
}

// Create new array (size) of int
TInfo memory_alloc(const int size)
{
	return new int[size];
}

// Destructor for memory_alloc(const int size)
void free_memory(int*& arr)
{
	if (arr != nullptr)
	{
		delete[] arr;
		arr = nullptr;
	}
}

/* Prints an array using pointers, end = arr + size */
void print_arr(int* begin, const int* end)
{
	for (TInfo ptr = begin; ptr < end; ++ptr)
	{
		std::cout << *ptr << " ";

	}
}

// Print an array using indexes
void print_arr(int* arr, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << *(arr+i) << " ";
	}
}

// Fills an array with pseudorandom ints from [ A, B )
void fill_arr(int* arr, const int size, const int A, const int B)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = A + rand() % (B - A);

	}
}

// In given array counts even pairs
int count_even_pair(int* arr, const int size)
{
	int result = 0;
	for (int i = 0; i < size - 1; ++i)
	{
		if ((arr[i] + arr[i + 1]) % 2 == 0)
			++result;
	}
	return result;
}

// In given array counts even unique pairs
int count_even_pair_unique(int* arr, const int size)
{
	int result = 0;
	int end = size - 1;
	/*if (size % 2 == 0)
		end = size - 1;
	else
		end = size - 2;*/

	for (int i = 0; i < end; i+=2)
	{
		if ((arr[i] + arr[i + 1]) % 2 == 0)
			++result;
	}
	return result;
}

// Symmetrically exchanges values of arr[left] till arr[right]
void reverse_arr(int* arr, const int left, const int right)
{
	for (int i = left, j = right; i < j; ++i, --j)
	{
		std::swap(arr[i], arr[j]);
	}
}

/*Remove elem in pos and move elements
to left (be aware of last element, it will be arr[size-1]) */
void shift_to_left(int* arr, const int size, const int pos)
{
	for (int i = pos; i < size - 1; ++i)
	{
		arr[i] = arr[i + 1];
	}
}

// Same as shift_to_left, but modifies arr size 
void remove_from_pos(int* arr, int& size, const int pos)
{
	shift_to_left(arr, size, pos);
	--size;
}

// Makes arr to shift_to_left and isnerts arr[0] in arr[size-1]
void cyclic_shift_to_left(int* arr, const int size)
{
	int tmp = arr[0];
	shift_to_left(arr, size, 0);
	arr[size - 1] = tmp;
}

void shift_to_right(int* arr, const int left, const int right)
{
	for (int i = right; i > left; --i)
	{
		arr[i] = arr[i - 1];
	}
}

void expand_arr_to_right(int*& arr, int &size, int amount)
{
	int new_size = size + amount;
	int* tmp = memory_alloc(new_size);
	for (int i = 0; i < size; ++i)
	{
		tmp[i] = arr[i];
	}
	for (int j = size; j < new_size; ++j)
	{
		tmp[j] = 0;
	}
	delete[] arr;
	arr = tmp;
	size = new_size;
	tmp = nullptr;
}

// Insert certain elem in pos index ( to "push_back" do pos = -1 )
void insert_at_pos(int* &arr, int& size, const int pos, const int elem)
{
	if (pos == -1)
	{
		expand_arr_to_right(arr, size, 1);
		arr[size-1] = elem;
	}
	else if (pos >= 0)
	{
		expand_arr_to_right(arr, size, 1);
		shift_to_right(arr, pos, size - 1);
		arr[pos] = elem;
	}
}

void cyclic_shift_to_right(int* arr, const int left, const int right)
{
	int tmp = arr[right];
	shift_to_right(arr, left, right);
	arr[left] = tmp;
}

// Creates new array of only even numbers ( new array will be in arr )
void remove_odd(int*& arr, int& size)
{
	int cnt = 0;
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] % 2 == 0)
		{
			arr[cnt++] = arr[i];
		}
	}
	int* tmp = memory_alloc(cnt);
	for (int i = 0; i < cnt; ++i)
	{
		tmp[i] = arr[i];
	}
	delete[] arr;
	arr = tmp;
	size = cnt;
	tmp = nullptr;
}

// Finds even numbers, puts them first, then all not-even number will be zeros
void compress_odd(int* arr, const int size)
{
	int cnt = 0;
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] % 2 == 0)
		{
			arr[cnt++] = arr[i];
		}
	}
	for (int i = cnt; i < size; ++i)
	{
		arr[i] = 0;
	}
}

// Finds even numbers, puts them first
void filter_even(int* arr, const int size)
{
	int cnt = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
		{
			if (cnt != i) cyclic_shift_to_right(arr, cnt, i);
			++cnt;
		}
	}
}

void sort_bubble_fromback(int* arr, const int size, TCompareInt compare)
{
	for (int count = size; count >= 2; --count)
	{
		for (int i = 0; i < count - 1; ++i)
		{
			if (compare(arr[i], arr[i + 1]))
			{
				std::swap(arr[i], arr[i + 1]);
			}
		}
	}
}

void sort_bubble_fromfront(int * arr, const int size, TCompareInt compare)
{
	for (int i = 0; i < size - 1; ++i)
		// Last i elements are already in place
		for (int j = 0; j < size - i - 1; ++j)
			if (compare(arr[j], arr[j + 1]))
				std::swap(arr[j], arr[j + 1]);
}

void selection_sort(int* arr, const int size, TCompareInt compare)
{
	for (int i = 0; i < size - 1; ++i)
	{
		int tmp = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (compare(arr[j], arr[tmp]))
			{
				tmp = j;
			}
		}
		if (tmp != i)
		{
			std::swap(arr[i], arr[tmp]);
		}
	}
}

void insert_sort(int* arr, const int size, TCompareInt compare)
{
	for (int i = 1; i < size; ++i)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && compare(arr[j], key))
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}
