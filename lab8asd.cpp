#include <iostream>
//поразрядная сортировка
int nDigit(int x, int N)
{
	for (int i = 1; i < N; i++)
		x /= 10;
	return x % 10;
}

int main()
{
	int a[10] = { 225,23,634,-234,765,432,76,444,-32,2 }, n = 10;
	int b[10], digit[19], max = a[0], maxD = 0;

	for (int i = 1; i < n; i++)
		if (a[i] > max) max = a[i];
	while (max > 0)
	{
		max /= 10;
		maxD++;
	}

	for (int d = 1; d <= maxD; d++)
	{
		for (int i = 0; i < 19; i++) digit[i] = 0;
		for (int i = 0; i < n; i++)
		{
			digit[nDigit(a[i], d) + 9]++;
			b[i] = a[i];
		}
		for (int i = 1; i < 19; i++) digit[i] += digit[i - 1];
		for (int i = n - 1; i >= 0; i--)
		{
			digit[nDigit(b[i], d) + 9]--;
			a[digit[nDigit(b[i], d) + 9]] = b[i];
		}
	}

	for (int i = 0; i < n; i++)
		std::cout << a[i] << " ";

	return 0;
}