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

int readfile(vector<int>& , int); // ������� ������ �����
void BubbleSort (vector<int> &); // ���������� ���������
void ShakerSort (vector<int> &); // ��������� ����������
void QuickSort (vector<int> &, int, int); // ������� ����������


int main(void)
{
    setlocale(LC_ALL, "Rus"); 
    vector<int> array; // ������ ������ ������ ������
    
    readfile(array, N1); // ��������� ������ �� �����
    BubbleSort(array);
    for(int i = 0; i < array.size(); i++)
    {
        cout << array[i] << endl;
    }
    
    while(cin.get() != '\n');
    return 1;
}

int readfile(vector<int> &array, int amount) // ������� ������ �����
{
    int i = 0, itmp; // ��������
    ifstream fin; // ������ �����
    fin.exceptions(ifstream::badbit | ifstream::failbit); // ��� ��������� �������������� �������� ��� ��������
    try
    {
        fin.open("test_numbers.txt"); // ��������� ����� �� ������ �����
        cout << "���� ������� ������" << endl;
    }
    catch(const exception& ex)
    {
        cerr << ex.what() << endl;
        cout << "������ �������� �����" << endl;
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

void BubbleSort (vector<int> &array) // ���������� ���������
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

void ShakerSort (vector<int> &array) // ��������� ����������
{
    int n = array.size();
	int j, k = n - 1, left = 1, right = n - 1, x;
	do
	{
		for (j = right; j >= left; j--)	/*������� ������������� ������ ������*/
			if (array[j - 1]>array[j])
			{
				x = array[j - 1];
				array[j - 1] = array[j];
				array[j] = x;
				k = j;
			}
		left = k + 1;
		for (j = left; j <= right; j++)	/*� ������ ������������� ����� �������*/
			if (array[j - 1]>array[j])
			{
				x = array[j - 1];
				array[j - 1] = array[j];
				array[j] = x;
				k = j;
			}
		right = k-1;
	}
	while (left < right);	/*� ��� �� ��� ���, ���� ���� ��� �������������*/
}

void QuickSort (vector<int> &array, int i, int n) // ������� ����������
{
	int x, itmp, j;
    x = array[n / 2];     /* ������� ������� */
	i = 0; 
    j = n - 1;
	do
	{
		while (array[i] < x) i++; /* ����� ������� ������� ������ �������� */
		while (x < array[j]) j--; /* ������ ������� ������� ������ �������� */
		if (i <= j)
		{
			itmp = array[i]; 
            array[i] = array[j]; 
            array[j] = itmp; /* ������ ��������� �������� ������� */
			i++; 
            j--;
		}
	}
	while (i < j); /* �� ���������� ����� ����� �� �������� �������� �����, ������� �, � ������ - ������� */
	/* ��������� ��� �� ����� � ������ ����� */
	if (j > 0)
		QuickSort (array, 0, j + 1); // ��������� ����� �����
	if (i < n-1)
		QuickSort (array, i, n - i); // ��������� ������ �����
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
	do 				/*����� �� ����� ���������� �������*/
	{
		left = stack[s].left;
		right = stack[s].right;
		s--;
		do			/*���������� �[left]� a[right]*/
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
			if (i<right && right-i>=j-left)     /*���� ������ ����� �� ������ �����*/
			{                                   /*������ � ���� ������ ������ �����*/
				s++;
				stack[s].left = i;
				stack[s].right = right;
				right = j;      /*������ left � right ������������ ����� �����*/
			}
			else if (j>left && j-left>right-i)   /*���� ����� ����� ������ ������*/
			{                                    /*������ � ���� ������ ����� �����*/
				s++;
				stack[s].left = left;
				stack[s].right = j;
				left = i;      /*������ left � right ������������ ������ �����*/
			}
			else left = right;     /*������ ������ ������, �������� "������������"*/
		}
		while (left<right);
	}
	while (s>-1);
	free (stack);
}