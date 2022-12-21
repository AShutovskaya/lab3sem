//поразрядная сортировка
#include <iostream>
using namespace std;
const int n = 10, count_razr = 3;//максимальное колво разрядов в числе
int velichina_razr(int chi, int razr)
{
	//делим поразрядно числа 
	while (razr > 1)
	{
		chi /= 10;
		razr--;
	}
	return chi % 10;
}

void sort_razr(int mas1[n][n], int mas[n], int razr)
{
	int mas_col[n], i, j, temp = 0;
	for (i = 0; i < n; i++)
		mas_col[i] = 0;//счетчик разрядов 
	for (i = 0; i < n; i++)
	{
		int a = velichina_razr(mas[i], razr);
		mas1[mas_col[a]][a] = mas[i];//распределение исходных чисел по спискам 
	/*	в зависимости от величины рязряда по возрастанию*/
		mas_col[a]++;//увеличиваем счетчик 
	}
	//объединяем в отсортированный массив 
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < mas_col[i]; j++)
		{
			mas[temp] = mas1[j][i];
			temp++;
		}
	}
}

int main()
{

	int razr, i;
	int mas[n] = { 2, 578, 126, 335, 234, 630, 135, 786, 13, 97 };
	int mas1[n][n];
	for (razr = 1; razr < count_razr + 1; razr++)
		sort_razr(mas1, mas, razr);
	for (i = 0; i < n; i++)
		cout << mas[i] << ' ';

		return 0;
}