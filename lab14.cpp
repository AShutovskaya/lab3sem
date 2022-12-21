//Дан текстовый файл с некоторым текстом на русском или английском языках произвольной длины(организовать чтение).Выбрав некоторую хеш - функцию, создать хеш - таблицу с :
//Лаба №14 “со списками”!
// этот метод разрешения коллизий - метод со списками («метод цепочек»)
//  метод предстваляет собой создание независимых цепочек для всех элементов с одинаковым хэш-индексом
// цепочки создаются с помощью связных списков
// когда мы встречаем коллизию, мы добавляем в конфликтную ячейку ссылку на следующее значение 
// (сохраняем значение в какой-то отдельной области памяти)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Element
{
	std::string key;
	int value;
	Element(std::string key = "", int value = 0) : key(key), value(value) {}
};

class HashSet
{
	int buff = 17;
	std::vector <Element> table[17];

	int hash(std::string s)//ф-ция присваивания индекса
	{
		int h = 0, p = 1;
		for (char c : s) // h = c_0 + c_1 * p^1 + c_2 *p^2 + ... , p=3
		{
			h += c * p;
			p *= 3;
		}
		return h % buff;
	}
public:

	HashSet()
	{
		for (int i = 0; i < buff; i++)
			table[i].push_back(Element("", 0));
	}

	void add(std::string s)//запись таблицы
	{
		bool flag = false;
		int h = hash(s);
		if (table[h][0].key == "")
		{
			table[h][0] = Element(s, 1);
			flag = true;
		}
		else
			for (int i = 0; i < table[h].size(); i++)
				if (table[h][i].key == s)
				{
					table[h][i].value++;
					flag = true;
				}
		if (!flag)
			table[h].push_back(Element(s, 1));
	}

	std::string out()//вывод таблицы
	{
		std::string tmp;
		for (int i = 0; i < 17; i++)
			if (table[i][0].key != "")
			{
				tmp += std::to_string(hash(table[i][0].key)) + ' ';
				for (int j = 0; j < table[i].size(); j++)
					tmp += table[i][j].key + ' ' + std::to_string(table[i][j].value) + ' ';
				tmp += '\n';
			}

		return tmp;
	}

};

int main()
{
	std::ifstream fin("text.txt");
	std::ofstream fout("out.txt");

	HashSet set;
	std::string s;
	while (fin >> s) set.add(s);
	fout << set.out();

	fin.close();
	fout.close();

	return 0;
}
