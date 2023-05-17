#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <locale.h>
#define N1 1000
#define N2 2000
#define N3 3000
#define N4 4000

using namespace std;

int readfile(vector<int>& , int);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    vector<int> array; // ������ ������ ������ ������
    
    readfile(array, N1);
    for(int i = 0; i < array.size(); i++)
    /* {
        cout << array[i] << endl;
    } */
    
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
    }

    while(i < amount)
    {
        fin >> itmp; 
        array.push_back(itmp);
        i++;
    }
    fin.close();
}