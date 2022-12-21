//Дана последовательность чисел.Отсортировать и вывести последовательность чисел, определённым методом.
//№12 Внешняя многофазная
#include <fstream>
#include<iostream>
using namespace std;

int main()
{
	ifstream in, in1, in2;
	ofstream out, out1, out2;

	int a, b, size = 0, countA, countB, count;
	bool flag = true, Aall, Ball;
	//открытие файлов
	in.open("numbers.txt");
	out.open("exit.txt");
	//считаем кол-во чисел и добавляем их в файл вывода
	while (in >> a)
	{
		out << a << " ";
		size++;
	}
	in.close();
	out.close();
	//сортировка
//рассматриваем элементы с промежутком 1,2,4,8 и тд
	for (int part = 1; part < size; part *= 2)
	{
		in.open("exit.txt");
		out1.open("A.txt");
		out2.open("B.txt");
		count = 0;
		//записываем числа в А и В  по приниципу : первая пара чисел на расстоянии 1 в А,
		/*вторая пара чисел на расстоянии 1 в B ,
		первая пара чисел  на расстоянии 2 в А и тд*/
		while (in >> a)
		{

			count++;
			//добавляем число в А
			if (flag) out1 << a << " ";
			//добавляем число в В
			else out2 << a << " ";
			//когда распределили все числа по файлам А и В 
			if (count == part)
			{
				count = 0;
				flag = !flag;
			}
		}
		//закрываем файл
		in.close();
		out1.close();
		out2.close();
		//очищаем файл
		remove("exit.txt");
		//открываем
		in1.open("A.txt");
		in2.open("B.txt");
		out.open("exit.txt");
		//проверяем остались ли числа в том же файле ,в котором и были
		if (in1 >> a)
			Aall = true;
		else Aall = false;
		if (in2 >> b)
			Ball = true;
		else Ball = false;
		//основная сортировка
		for (int i = 0; i < size; i += 2 * part)
		{
			countA = 0; countB = 0;
			//сравниваем по 1 числу из файла А и В
			//,потом  по 2 пары чисел потом по 4 пары ,тк partSize *= 2
			while (countA < part && Aall && countB < part && Ball)
				//если а < b добавляем в А и  считаем сколько там чисел
				if (a < b)
				{
					out << a << " ";
					if (in1 >> a) Aall = true;
					else Aall = false;
					countA++;
				}
			//добавляем в В и считаем сколько там чисел 
				else
				{
					out << b << " ";
					if (in2 >> b) Ball = true;
					else Ball = false;
					countB++;
				}
			//если остались числа в А
			while (countA < part && Aall)
			{
				out << a << " ";
				if (in1 >> a) Aall = true;
				else Aall = false;
				countA++;
			}
			//если остались числа в В
			while (countB < part && Ball)
			{
				out << b << " ";
				if (in2 >> b) Ball = true;
				else Ball = false;
				countB++;
			}

		}
		//закрываем файлы и очищаем их
		in1.close();
		in2.close();
		out.close();
		remove("A.txt");
		remove("B.txt");
	}
	return 0;
}