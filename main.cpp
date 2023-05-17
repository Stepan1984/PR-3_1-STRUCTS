#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <math.h>
#include <vector>
#include <chrono>
//#include <time.h>
#include <sstream>

#define N1 10000
#define N2 50000
#define N3 100000
#define N4 150000

using namespace std;

/* ��������������� ������� */
int ReadFile(vector<int> &array, int n); // ������ �����
int WriteFile(int * array, int N, int status_before_sort, int sort_type); // ������ � ���� 
int CopyData(vector<int> &data, int * array, int N); // ����������� ������������ ���������� ���������
void ReverseArray(int * array, int N); // �������� �������

/* ��������� ���������� */
void BubbleSort (int *a, int n, ofstream &fout); // ���������� ���������
void ShakerSort (int *a, int n, ofstream &fout);  // ��������� ����������
void NonRecursiveQuickSort (int *a, int n, ofstream &fout); // ������� ���������� (�������������)
void NaturalMergeSort(int *a, int n, ofstream &fout); // ���������� ������������ ��������



/* ��������������� ������� */
int main(void)
{
    setlocale(LC_ALL, "Rus"); 
	int a ,i, j, l, m, s; // ���������
	int countrM, countrH; // �������� �������� � ��������������� ��������
	int amounts[4] = {N1, N2, N3, N4}, N; // ������ � ������������ ������������ ��-�� � �������� // ���������� ��-�� � ������ �������
	int array[N4]; // ����������� ������
    void (*f[])(int *, int, ofstream &) = {BubbleSort, ShakerSort, NonRecursiveQuickSort , NaturalMergeSort }; // ������ ���������� �� �������
	vector<int> data; // ������ � ��������� ����������
	string table_header = " ����� ��. | ���. | ���������� \n"; // 11|13|12

	ofstream fout_bubble, fout_shaker, fout_quick, fout_merge;
	fout_bubble.exceptions(ofstream::badbit | ofstream::failbit);
	fout_shaker.exceptions(ofstream::badbit | ofstream::failbit);
	fout_quick.exceptions(ofstream::badbit | ofstream::failbit);
	fout_merge.exceptions(ofstream::badbit | ofstream::failbit);
	try
	{ // ������ ����� ��� �������� ������� ������ ����������
		fout_bubble.open("Bubble.txt");
		fout_shaker.open("Shaker.txt");
		fout_quick.open("Quick.txt");
		fout_merge.open("Merge.txt");
		fout_bubble << table_header;
		fout_shaker << table_header;
		fout_quick << table_header;
		fout_merge << table_header;
	}
	catch(const exception& ex)
	{
		cerr << ex.what() << endl;
		std::cout << "������ �������� �����" << endl << "ENTER";
		while(cin.get() != '\n');
		abort;
	}

	if(ReadFile(data, N4)) // ��������� ����������� ���������� ����� �� �����
	{
		std::cout << "ENTER" << endl;
		while(cin.get() != '\n');
		abort;
	}


    for(s = 0; s < 4; s++) // ������� �������� �������
	{
		N = amounts[s]; // ���������� ���������� ��-�� � �������� �������
		for(a = 0; a < 4; a++) // ������� ���������� ����������
		{
			CopyData(data, array, N); // �������� ������ � ������
			for(m = 0; m < 3; m++) // ������� �������� ��������� ������� (0 - ��������������, 1 - ������������, 2 - ��������)
			{
				if(!m) // ���� ������ �� ������������
				{
					f[a](array, N, (!a? fout_bubble: a == 1? fout_shaker: a == 2? fout_quick : fout_merge )); // ��������� ������
					//WriteFile(array, N, 0, a); // ���������� ��������� � ���� ��� ��������
					(!a? fout_bubble: a == 1? fout_shaker: a == 2? fout_quick : fout_merge ) << " | �� ������������" << endl;
				}
				if(m == 1) // ���� ������ ������������
				{
					f[a](array, N, (!a? fout_bubble: a == 1? fout_shaker: a == 2? fout_quick : fout_merge )); // ��������� ������
					//WriteFile(array, N, 1, a); // ���������� ��������� � ����
					(!a? fout_bubble: a == 1? fout_shaker: a == 2? fout_quick : fout_merge ) << " | ������������" << endl;
				}
				if(m == 2) // ���� ������ ������������, �� ����� ��� ����������
				{
					ReverseArray(array, N); // ������������� ������
					f[a](array, N, (!a? fout_bubble: a == 1? fout_shaker: a == 2? fout_quick : fout_merge)); // ��������� ������
					//WriteFile(array, N, 2, a); // ���������� ��������� � ���� ��� ��������
					(!a? fout_bubble: a == 1? fout_shaker: a == 2? fout_quick : fout_merge ) << " | ��������" << endl;
				}
			}
		}
	}
	fout_bubble.close();
	fout_shaker.close();
	fout_quick.close();
	fout_merge.close();
    return 1;
}

int ReadFile(vector<int> &array, int n) // ������� ������ �����
{
    int i = 0, itmp;
    ifstream fin; // ������ �����
    fin.exceptions(ifstream::badbit | ifstream::failbit); // ��� ��������� �������������� �������� ��� ��������
    try
    {
        fin.open("test_numbers.txt"); // ��������� ����� �� ������ �����
        cout << "���� ������� ������" << endl;
		while(i < n) // ���� �� ������� ������ ���������� ����� �� �����
		{
			fin >> itmp; 
			array.push_back(itmp); // ����� �������� � ����� �������
			i++;
		}
    }
    catch(const exception& ex) // ����������� ������ ��� ��������
    {
        cerr << ex.what() << endl;
        cout << "������ �������� �����" << endl;
        while(cin.get() != '\n');
		return 1;
    }

    fin.close(); // ��������� �����
	return 0;
}

int WriteFile(int * array, int N, int status_before_sort, int sort_type) // type(0 - unsorted, 1 - sorted, 2 - reverse)
{
	int i, j, itmp;
	string filename;
	ofstream fout;

	filename.append((!sort_type? "Bubble " : sort_type == 1? "Shake " : "Quick "));
	filename.append(to_string(N / 1000));
	filename.append((!status_before_sort? " unsorted" : status_before_sort == 1? " sorted" : " reverse" ));


	fout.exceptions(ofstream::badbit | ofstream::failbit);
	try
	{
		fout.open(filename);
		cout << "���� ������� ������" << endl;
		i = 0;
		while(i < N)
		{
			for(j = 0; j < 10; j++)
			{
				fout << array[i] << ' '; 
				i++; j++;
			}
			fout << endl;
		}
	}
	catch(const exception& ex)
	{
		cerr << ex.what() << endl;
		cout << "������ �������� �����" << endl;
		while(cin.get() != '\n');
	}
	fout.close();
}

int CopyData(vector<int> &data, int * array, int N)
{
	if(data.empty())
		return 0;

	int i = 0;
	while(i < N)
	{
		array[i] = data[i];
		i++;
	}
}

void ReverseArray(int * array, int N) // ������� ��������� �������
{
	int itmp, half = N / 2;
	for(int i = 0, j = N - 1; i < half; i++, j--)
	{
		itmp = array[i];
		array[i] = array[j];
		array[j] = itmp;
	}
}


/* ��������� ���������� */
void BubbleSort (int *a, int n, ofstream &fout) // ���������� ���������
{
	int i, j, itmp;
	chrono::steady_clock::time_point start_time, end_time; // ���������� ��� �������� ������� ������ ���������
    start_time = chrono::steady_clock::now();
	for (i = 1; i < n; i++)
		for (j = n - 1; j >= i; j--)
			if (a[j-1] > a[j])
			{
				itmp = a[j-1];
				a[j-1] = a[j];
				a[j] = itmp;
			}
	end_time = chrono::steady_clock::now();
	fout << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << " | " << n/1000;
}

void ShakerSort (int *a, int n, ofstream &fout)
{
	int j, k = n-1, left = 1, right = n-1, x;
	chrono::steady_clock::time_point start_time, end_time; // ���������� ��� �������� ������� ������ ���������
    start_time = chrono::steady_clock::now();
	do
	{
		for (j=right; j>=left; j--)	//������� ������������� ������ ������
			if (a[j-1]>a[j])
			{
				x = a[j-1];
				a[j-1] = a[j];
				a[j] = x;
				k = j;
			}
		left = k+1;
		for (j=left; j<=right; j++)	//� ������ ������������� ����� �������
			if (a[j-1]>a[j])
			{
				x = a[j-1];
				a[j-1] = a[j];
				a[j] = x;
				k = j;
			}
		right = k-1;
	}
	while (left<right);	//� ��� �� ��� ���, ���� ���� ��� �������������
	end_time = chrono::steady_clock::now();
	fout << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << " | " << n/1000;
}

void NonRecursiveQuickSort (int *a, int n, ofstream &fout)
{
	const int M=log(n)/log(2)+1;
	int i, j, left, right, s, x, w;
	struct stack {int left, right;} *stack;
	stack = (struct stack *) malloc (M*sizeof(struct stack));
	s = 0;
	stack[0].left = 0;
	stack[0].right = n-1;

	chrono::steady_clock::time_point start_time, end_time; // ���������� ��� �������� ������� ������ ���������
    start_time = chrono::steady_clock::now();

	do 				//����� �� ����� ���������� �������
	{
		left = stack[s].left;
		right = stack[s].right;
		s--;
		do			//���������� �[left]� a[right]
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
			if (i<right && right-i>=j-left)     //���� ������ ����� �� ������ �����
			{                                   //������ � ���� ������ ������ �����
				s++;
				stack[s].left = i;
				stack[s].right = right;
				right = j;      //������ left � right ������������ ����� �����
			}
			else if (j>left && j-left>right-i)   //���� ����� ����� ������ ������
			{                                    //������ � ���� ������ ����� �����
				s++;
				stack[s].left = left;
				stack[s].right = j;
				left = i;      //������ left � right ������������ ������ �����
			}
			else left = right;     //������ ������ ������, �������� "������������"

		}while (left<right);

	}while (s>-1);
	end_time = chrono::steady_clock::now();
	fout << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << " | " << n / 1000 ;
	free (stack);
}

void NaturalMergeSort(int *a, int n, ofstream &fout)
{
    int split;                   // ������, �� �������� ����� ������
    int last, end, i, *p=a, *tmp;
    char flag = 0, sorted = 0;
    int pos1, pos2, pos3;
    tmp = (int*) malloc (n*sizeof(int));

	chrono::steady_clock::time_point start_time, end_time; // ���������� ��� �������� ������� ������ ���������
    start_time = chrono::steady_clock::now();

    do                 // ���� ���� ����� 1 ��������
    {
        end = n; pos2 = pos3 = 0;
        do
        {
            p += pos2; end = n - pos3;
            for (split=1; split < end && p[split-1] <= p[split]; split++); //������ �����
            if (split == n) {sorted = 1 ; break;}
            pos1 = 0; pos2 = split;
            while ( pos1 < split && pos2 < end ) 	// ���� �������, ���� ���� ���� ���� ������� � ������ �����
            {
                if (p[pos1] < p[pos2])
                    tmp[pos3++] = p[pos1++];
                else
                {
                    tmp[pos3++] = p[pos2++];
                    if (p[pos2] < p[pos2-1]) break;
                }
            }
            // ���� ������������������ ����������� - ���������� ������� ������ � ����� ������
            while ( pos2 < end && tmp[pos3-1]<=p[pos2] )  			 // ���� ������ ������������������ �� �����
                tmp[pos3++] = p[pos2++];
            while ( pos1 < split )  		// ���� ������ ������������������ �� �����
                tmp[pos3++] = p[pos1++];
        }
        while (pos3 < n );
        if (sorted) break;
        p = tmp;
        tmp = a;
        a = p;
        flag = !flag;
    }
    while (split<n);
    if (flag)
    {
        for (pos1 = 0; pos1 < n; pos1++)
            tmp[pos1] = a[pos1];
        free (a);
    }
    else
        free (tmp);
	
	end_time = chrono::steady_clock::now();
	fout << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << " | " << n / 1000 ;
}