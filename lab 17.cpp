//Лаба №17 “Операции над БНП : поиск, добавление, удаление”!
//Дерево вводится в программу в формате линейно - скобочной записи.
//Затем появляется меню, в котором доступна операция добавления, удаления и поиска вершины БДП.
//После выполнения операции программа должна возвращаться снова в меню.
//При выходе их него до завершения программы на экран должно быть выведено БДН любым способом
//(в виде линейно - скобочной записи или в графической форме).
#include <iostream>
#include <vector>
#include <string>
const std::string Numerals = { "1234567890" };//объявляем набор возможных символов

struct Node
{
	int value;
	Node* left = nullptr, *right = nullptr;

	Node(std::string& s)//обработка входящих данных
	{
		value = getValue(s);
		s.erase(0, digits(value));
		if (s[0] == '(')
			s = bracketopen(s);
		else return;
		if (isDigit(s[0]))
			left = new Node(s);
		if (s[0] == ',' && isDigit(s[1])) right = new Node(s.erase(0, 1));
	}
public:
	void add(int x)// add - добавление
	{
		//приводим введенное значение к строке
		std::string s = std::to_string(x);
		//в зависимоти от того, больше ли введенное число или меньше относительно имеющегося узла, добавляем число в правую или левую ветвь
		if (x > value && right)
			right->add(x);
		//если узла не существует, мы его создаем и размещаем в него введеное число 
		if (x > value && !right)
			right = new Node(s);
		if (x < value && left)
			left->add(x);
		if (x < value && !left)
			left = new Node(s);
	}

	void del(int x)// del-удаление
	{
		//в зависимости от числа, которое мы хотим удалить, и его расположения в дереве, сначала делаем на его месте nullptr, затем удаляем узел 
		if (x > value && right && right->value == x)
			right = nullptr;
		if (x > value && right && right->value != x)
			right->del(x);
		if (x < value && left && left->value == x)
			left = nullptr;
		if (x < value && left && left->value != x)
			left->del(x);
	}

	bool contains(int x)// c - поиск
	{
		//происходит вызов функции find
		return find(x);
	}

	//находим элемент
	Node* find(int x)
	{
		//если введенное значение равно value, возвращаем указатель на текущий объект
		if (x == value)
			return this;
		//если x <> value, снова вызываем функцию
		if (x > value && right)
			return right->find(x);
		if (x < value && left)
			return left->find(x);
		return nullptr;
	}

	//функция возвращения элементов
	void getElements(std::vector<int>& v)
	{
		//добавляем элемент в конец
		v.push_back(value);
		//возвращаем элемент
		if (left)
			left->getElements(v);
		if (right)
			right->getElements(v);
	}

private:

	bool isDigit(char c)//поиск чисел до конца строки 
	{ 
		return Numerals.find(c) != std::string::npos;
	
	}
	int digits(int n)//разделяем поразрядно
	{
		int i = 0;
		if (n == 0) return 1;
		while (n > 0)
		{
			n /= 10;
			i++;
		}
		return i;
	}

	int getValue(std::string& s)//преобразовываем строку в числа
	{
		int n = s.size(), i = 1;
		while (i < n) if (isDigit(s[i++])) break;
		return std::stoi(s.substr(0, i));
	}

	std::string bracketopen(std::string s)//раскрытие скобок
	{
		int brackets = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '(') brackets++;//если ( то увелививаем счетчик 
			if (s[i] == ')') brackets--;//если ) то уменьшаем счетчик 
			if (!brackets)
			{
				s.erase(0, 1);
				s.erase(i - 1, 1);
				return s;
			}
		}
		return s;
	
	}
};

class BinaryTree
{
	Node* root = nullptr;//пустой корень

	void print(const std::string& p, const Node* n, bool l)//функия вывода
	{
		if (!n) return;
		std::cout << p << (l ? "|--" : "|--") << n->value << "\n";
		print(p + (l ? "|   " : "    "), n->left, true);
		print(p + (l ? "|   " : "    "), n->right, false);
	}

public:

	BinaryTree(std::string s = "")
	{
		if (!s.empty()) root = new Node(s);
	}

	void print() { if (root) print("", root, 0); else std::cout << "|--\n"; };

	void add(int x)
	{
		std::string s = std::to_string(x);
		if (root) root->add(x);
		else root = new Node(s);
	}

	void del(int x)
	{
		if (!root) return;

		Node* n;
		if (root->value == x) n = root;
		else n = root->find(x);

		std::vector<int> branch;
		if (n->left) n->left->getElements(branch);
		if (n->right) n->right->getElements(branch);

		if (root->value == x) root = nullptr;
		else root->del(x);
		for (int e : branch) add(e);
	}

	bool contains(int x) { return root ? root->contains(x) : false; }
};

int main()
{
	BinaryTree tree;
	//объявляем строку-команду
	std::string command;
	//число х, которое будем вводить в дерево
	int x;
	tree.print();
	//бесконечный цикл
	while (1)
	{
		//вводим команду и число
		std::cin >> command >> x;
		//случай добавления х
		if (command == "add") tree.add(x), tree.print();
		//случай удаления х
		if (command == "del") tree.del(x), tree.print();
		//случай нахождения х в дереве
		if (command == "find")
			std::cout << x << (tree.contains(x) ? " exists\n" : " not exists\n");
	}
	tree.print();
	return 0;
}




