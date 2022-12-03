#include <iostream>
#include <fstream>
#include <omp.h>

using namespace std;


void mul(const char* path1, const char* path2, const char* path3, int row, int col)
{
	ifstream fin;
	fin.open(path1);

	int** a = new int* [row];
	for (int i = 0; i < row; i++)
	{
		a[i] = new int[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fin >> a[i][j];
		}
	}
	fin.close();

	ifstream fin2;
	fin2.open(path2);

	int** b = new int* [row];
	for (int i = 0; i < row; i++)
	{
		b[i] = new int[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fin2 >> b[i][j];
		}
	}
	fin2.close();

	clock_t start;
	start = clock();
	double wtime = omp_get_wtime();

	int** c = new int* [row];
	for (int i = 0; i < row; i++)
	{
		c[i] = new int[col];
	}

	int threads;
#pragma omp parallel shared(threads)
	{
		threads = omp_get_num_threads();
		//cout << threads << endl;

#pragma for
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				c[i][j] = 0;
				for (int k = 0; k < col; k++)
				{
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}
	wtime = omp_get_wtime() - wtime;
	cout << "Elapsed omp time: " << wtime << " seconds" << endl;
	cout << endl << "Num of threads: " << threads << endl << "Calculation time: " << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

	ofstream fout;
	fout.open(path3);
	if (fout.is_open())
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				fout << c[i][j] << " ";
			}
			fout << "\n";
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	//D:\\1_3.txt", "D:\\2_3.txt", "D:\\res_3.txt
	mul("home/2020-02337/1_3.txt", "home/2020-02337/2_3.txt", "home/2020-02337/res_3.txt", 3, 3);
	mul("home/2020-02337/1_10.txt", "home/2020-02337/2_10.txt", "home/2020-02337/res_10.txt", 10, 10);
	mul("home/2020-02337/1_100.txt", "home/2020-02337/2_100.txt", "home/2020-02337/res_100.txt", 100, 100);
	mul("home/2020-02337/1_500.txt", "home/2020-02337/2_500.txt", "home/2020-02337/res_500.txt", 500, 500);
	mul("home/2020-02337/1_1000.txt", "home/2020-02337/2_1000.txt", "home/2020-02337/res_1000.txt", 1000, 1000);
	return 0;
}