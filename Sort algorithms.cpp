/***************************************************************************************
*Project Name : Sort algorithms                                                        *
*File Name    : Sort alorithms.cpp                                                     *
*Language     : CPP,MSVS ver 2015 and above                                            *
*Programmers : Ратников Роман Олегович,группа:М3О-210Б-20                              *
*															                           *
*                                                		                               *
*Modified By  :                                                                        *
*Created      : 20/10/2021                                                             *
*Last Revision: 28/10/2021                                                             *
*Comment      :Алгоритмы сортировки													   *
***************************************************************************************/

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;


//Прототипы функций

// Сортировка Шелла
void ShellSort(int* array,      //Массив
			   const int& N,    //Размер массива
			   int& compare,    //Количество сравнений
	           int& transfer);  //Количество пересылок

//Шейкерная сортировка
void Shaker_Sort(int* array, const int& N, int& compare, int& transfer);

//Функция печати

void Print_Array(int* array, const int& N);

void Print_Info(const int& compare, const int& transfer,const float& Time, const int& N);

//Функция получения случайного массива
void Get_Random_Arr(int* array, const int& N);

//Функция сохранения исходного массива

void Save_Array(int* array, int* array_save, const int& N);

//Функция получения убывающего массива

int* Get_Des_Arr(int* array, int* des_array, const int& N);


int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Введите N : ";
	int N;
	cin >> N;
	int* Array = new int[N];
	int* Des_Array = new int[N];  //Убывающий массив
	int* Array_Save = new int[N]; //Исходный массив
	
	int compare; //Число сравнений
	int transfer;//Число пересылок

	Get_Random_Arr(Array, N);
	Save_Array(Array, Array_Save, N);


	//Массив указателей на функции
	void(*arr_f[2])(int*, const int&,  int&, int&) = { ShellSort,Shaker_Sort };

	string info[] = { "Сортировка Шелла: ", "Шейкерная сортировка: " };

	//Массив сообщений
	string info_2[] = { " ",
		"Лучший случай: ","Худший случай: " };


	int* pa[] = { Array, Array_Save};

	

	for (int i = 0;i < 2;++i)

	{
		cout << "-----------------" << endl;

		cout << info[i] << endl;

		for (int j = 0;j < 3;++j)
		{
			cout << "-----------------" << endl;

			cout << info_2[j] << endl;
			if (N <= 15)
			{
				cout << "\n Исходный массив: " << endl;
				cout << "\n";
				if (j != 2)
				{
					Print_Array(pa[i], N);
				}
				else
				{
					Print_Array(Get_Des_Arr(pa[i],Des_Array,N),N);
				}
				cout << "\n\n";
			}




			//Получение времени начала функции

			auto begin = chrono::high_resolution_clock::now();

			cout << "Сортировка массива" << endl;
			if (j != 2)
			{
				arr_f[i](pa[i], N, compare, transfer);
			}
			else
			{
				arr_f[i](Get_Des_Arr(pa[i], Des_Array, N), N, compare, transfer);
			}



			//Получение времени окончания функции

			chrono::duration<double> elapsed_ms = chrono::high_resolution_clock::now() - begin;

			float Time = elapsed_ms.count() * 1000;

			if (N <= 15)
			{
				
				cout << "\n\n";
				cout << " Отсортированный массив: " << endl;
				if (j != 2)
				{
					Print_Array(pa[i], N);
				}
				else
				{
					Print_Array(Des_Array, N);
				}
				
				
			}

			Print_Info(compare, transfer, Time, N);
		}

	}

	delete[] Array;
	delete[] Array_Save;
	delete[] Des_Array;


	return 0;
}


void Get_Random_Arr(int* array, const int& N)
{
	srand(time(0));
	for (int i = 0;i < N;++i)
	{
		array[i] = rand() % 30;
		
	}
}

void Print_Array(int* array, const int& N)
{
	
	for (int i = 0;i < N;++i)
	{
		cout << array[i] << " ";

	}
}

void ShellSort(int* array, const int& N, int& compare, int& transfer)
{
	
	compare = 0;
	transfer = 0;
	int Bufer; //Буфер
	int step = N / 2; //Шаг
	while (step != 0)
	{
		++compare;
		int i = 0;
		for (int j = i + step;j < N; ++j)
		{
			compare++;
			
			int z = i;
			
				 for (int k = j;z>=0 and array[z] > array[k];z = z - step)
				 {
					 compare+=2;
					Bufer = array[z];
					array[z] = array[k];
					array[k] = Bufer;
					++transfer;
					k = k - step;
					
					if (N <= 15)
					{
						
						Print_Array(array, N);
						cout << "\n";
					}
				 }
				 compare+=2;
				 ++i;
		}
		compare++;
		step = step / 2;
	}

	compare++;

}

void Save_Array(int* array, int* array_save, const int& N)
{
	for (int i = 0;i < N;++i)
	{
		array_save[i] = array[i];
	}
}

void Print_Info(const int& compare, const int& transfer,const float& Time,const int& N)

{
	cout << "\nКоличество сравнений: " << compare << endl;
	cout << "Количество пересылок: " << transfer << endl;

	if (N > 1000)
	{
		cout << "Время работы алгоритма: " << Time << "Нс" << endl;
	}
}

int* Get_Des_Arr(int* array, int* des_array, const int& N)
{
	for (int i = 0;i < N;++i)
	{
		des_array[N - 1 - i] = array[i];
	}
	return des_array;
}

void Shaker_Sort(int* array, const int& N, int& compare, int& transfer)
{
	compare = 0;
	transfer = 0;
	int Bufer;
	int begin = 0;
	int end = N;
	cout << "\n";
	while (begin<end)
	{
		compare++;
		int j = begin + 1;
		
		for (int i = begin;i < end-1;++i)
		{
			compare++;
			if (array[i] > array[j])
			{
				compare++;
				Bufer = array[i];
				array[i] = array[j];
				array[j] = Bufer;
				transfer++;
				
				if (N <= 15)
				{
					
					Print_Array(array, N);
					cout << endl;
				}
			}
			compare++;
			j++;
		}
		compare++;
		--end;

		j = end - 1;
		for (int i = end;i > begin;--i)
		{
			compare++;
			if (array[i] < array[j])
			{
				compare++;
				Bufer = array[i];
				array[i] = array[j];
				array[j] = Bufer;
				transfer++;

				if (N <= 15)
				{
					Print_Array(array, N);
					cout << endl;
				}
			}
			compare++;
			j--;

		}
		compare++;
		begin++;

	}
	compare++;
}