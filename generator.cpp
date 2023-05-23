#include "preproc.h"
#include <boost>

// количество повторений каждого элемента
#define R1 10
#define R2 100
#define R3 500
#define R4 1000

using namespace std;

void FillFile(ifstream * fin, ofstream * fout, int reps, int amount); // поток на чтение, поток на печать,


int generator(void) 
{
    int i, j, l;
    ifstream fin; // поток на чтение
    ofstream * files = new ofstream[4]; // массив поток на запись в файл
    string filenames[4] = {"rep_10","rep_100","rep_500","rep_1000"}, stmp; // названия файлов, переменная для временного хранения значения
    int reps[4] = {10, 100, 500, 1000}; // количество повторяющихся элементов в массиве
    fin.exceptions(ifstream::badbit | ifstream::failbit );// акивация флагов ошибок при использовании потока
    try
    {
        fin.open("test_numbers.txt");
        cout << "Р¤Р°Р№Р» СѓСЃРїРµС€РЅРѕ РѕС‚РєСЂС‹С‚" << endl;
        for (int i = 0; i < 4; i++)
    	files[i].exceptions(ofstream::badbit | ofstream::failbit);
        for(i = 0; i < 4; i++)
			files[i].open(filenames[i].c_str()); // создаём файлы
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "РћС€РёР±РєР° РѕС‚РєСЂС‹С‚РёСЏ С„Р°Р№Р»Р°" << endl;
        while(cin.get() != '\n');
        return 1;
    }

    boost.thread thr1(FillFile(fin, files[1], reps[1], N2 ));

    FillFile(fin, files[0], reps[0], N1);

    thr1.join();
    fin.close();
    for(i = 0; i < 4; i++)
        files[i].close();
    return 0;
}

void FillFile(ifstream & fin, ofstream & fout, int reps, int amount) // поток на чтение, поток на печать,  
{
    int i = 0, j;
    string stmp;
    while(i < amount)
    {
        getline(fin, stmp); // считываем строку из файла
        for(j = 0; j < reps; j++)
        {
            fout << stmp << endl;
        }
        i += reps;
    }
    return;
}