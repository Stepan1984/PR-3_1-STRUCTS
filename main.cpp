#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <locale.h>
#include <math.h>
#define N1 10000
#define N2 50000
#define N3 100000
#define N4 150000

using namespace std;

int readfile(vector<int>& , int); // функци€ чтени€ файла
void BubbleSort (vector<int> &); // сортировка пузырьком
void ShakerSort (vector<int> &); // шейкерна€ сортировка
void QuickSort (vector<int> &, int, int); // быстра€ сортировка


int main(void)
{
    setlocale(LC_ALL, "Rus"); 
    vector<int> array; // создаЄм объект класса массив
    
    readfile(array, N1); // считываем данные из файла
    BubbleSort(array);
    for(int i = 0; i < array.size(); i++)
    {
        cout << array[i] << endl;
    }
    
    while(cin.get() != '\n');
    return 1;
}

int readfile(vector<int> &array, int amount) // функци€ чтени€ файла
{
    int i = 0, itmp; // итератор
    ifstream fin; // создаЄм поток
    fin.exceptions(ifstream::badbit | ifstream::failbit); // дл€ обработки исключительных ситуаций при открытие
    try
    {
        fin.open("test_numbers.txt"); // открываем поток на чтение файла
        cout << "файл успешно открыт" << endl;
    }
    catch(const exception& ex)
    {
        cerr << ex.what() << endl;
        cout << "ќшибка открыти€ файла" << endl;
        while(cin.get() != '\n');
    }

    while(i < amount)
    {
        fin >> itmp; 
        array.push_back(itmp);
        i++;
    }
    fin.close();
}

void BubbleSort (vector<int> &array) // сортировка пузырьком
{
	int i, j, itmp, n = array.size();
	for (i = 1; i < n; i++)
		for (j = n - 1; j >= i; j--)
			if (array[j-1] > array[j])
			{
				itmp = array[j-1];
				array[j-1] = array[j];
				array[j] = itmp;
			}
}

void ShakerSort (vector<int> &array) // шейкерна€ сортировка
{
    int n = array.size();
	int j, k = n - 1, left = 1, right = n - 1, x;
	do
	{
		for (j = right; j >= left; j--)	/*сначала просматриваем справа налево*/
			if (array[j - 1]>array[j])
			{
				x = array[j - 1];
				array[j - 1] = array[j];
				array[j] = x;
				k = j;
			}
		left = k + 1;
		for (j = left; j <= right; j++)	/*а теперь просматриваем слева направо*/
			if (array[j - 1]>array[j])
			{
				x = array[j - 1];
				array[j - 1] = array[j];
				array[j] = x;
				k = j;
			}
		right = k-1;
	}
	while (left < right);	/*и так до тех пор, пока есть что просматривать*/
}

void QuickSort (vector<int> &array, int i, int n) // быстра€ сортировка
{
	int x, itmp, j;
    x = array[n / 2];     /* опорный элемент */
	i = 0; 
    j = n - 1;
	do
	{
		while (array[i] < x) i++; /* слева находим элемент больше опорного */
		while (x < array[j]) j--; /* справа находим элемент меньше опорного */
		if (i <= j)
		{
			itmp = array[i]; 
            array[i] = array[j]; 
            array[j] = itmp; /* мен€ем найденные элементы местами */
			i++; 
            j--;
		}
	}
	while (i < j); /* по завершении цикла слева от опорного элемента ключи, меньшие х, а справа - большие */
	/* сортируем так же левую и правую части */
	if (j > 0)
		QuickSort (array, 0, j + 1); // сортируем левую часть
	if (i < n-1)
		QuickSort (array, i, n - i); // сортируем правую часть
}

void NonRecursiveQuickSort (vector<int> &a)
{
    int n = a.size();
	const int M=log(n) / log(2) + 1;
	int i, j, left, right, s, x, w;
	struct stack 
    {
        int left, right;
    } *stack;

	stack = (struct stack *) malloc (M * sizeof(struct stack)); //...........
	s = 0;
	stack[0].left = 0;
	stack[0].right = n-1;
	do 				/*выбор из стека последнего запроса*/
	{
		left = stack[s].left;
		right = stack[s].right;
		s--;
		do			/*разделение а[left]Е a[right]*/
		{
			i = left; j = right;
			x = a[(left+right)/2];
			do
			{
				while (a[i]<x) i++;
				while (x<a[j]) j--;
				if (i<=j)
				{
					w = a[i]; a[i] = a[j]; a[j] = w;
					i++; j--;
				}
			}
			while (i<j);
			if (i<right && right-i>=j-left)     /*если права€ часть не меньше левой*/
			{                                   /*запись в стек границ правой части*/
				s++;
				stack[s].left = i;
				stack[s].right = right;
				right = j;      /*теперь left и right ограничивают левую часть*/
			}
			else if (j>left && j-left>right-i)   /*если лева€ часть больше правой*/
			{                                    /*запись в стек границ левой части*/
				s++;
				stack[s].left = left;
				stack[s].right = j;
				left = i;      /*теперь left и right ограничивают правую часть*/
			}
			else left = right;     /*делить больше нечего, интервал "схлопываетс€"*/
		}
		while (left<right);
	}
	while (s>-1);
	free (stack);
}