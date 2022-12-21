//Дан текстовый файл с некоторым текстом на русском или английском языках 
//произвольной длины(организовать чтение).Выбрав некоторую хеш - функцию, создать хеш - таблицу с :
//Лаба №13 “с наложением”!
// Хеш-таблица - это структура данных, которая сопоставляет ключи со значениями и использует хеш-функцию для вычисления индексов ключа.
// В данном случае, чтобы избавиться от коллизии, используем метод открытой адресации (с наложением)
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
	int buff = 17, size = 17;
	std::vector <Element> table;

	int hash(std::string s) // хеш ф - ия для присваивания индекса 
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
			table.push_back(Element("", 0));
	}

	void add(std::string s)//запись таблицы
	{
		int h = hash(s);
		while (table[h].key != "" && table[h].key != s && h < (size - 1))
			h++;
		if (table[h].key == "")
			table[h] = Element(s, 1);
		else if (table[h].key == s)
			table[h].value++;
		else
		{
			size++;
			table.push_back(Element(s, 1));
		}
	}

	std::string out() // вывод таблицы
	{
		std::string tmp;
		for (int i = 0; i < table.size(); i++)
			if (table[i].value)
				tmp += table[i].key + ' ' + std::to_string(table[i].value) + '\n';
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
