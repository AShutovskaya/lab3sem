//Лаба №16 “Не рекурсивный прямой обход” (реализуется с помощью стека).!
//В качестве выходных данных формируется строка обхода.Например:
//Бинарное дерево поиска

#include <iostream>
#include <string>
#include <vector>
#include <stack>

const std::string Numerals = { "1234567890" };//набор возможных символов в строке
//читаем выражение s
struct Node
{
	int value;
	Node* left = nullptr, *right = nullptr;
	//создаем бинарное дерево с помощью выражения в s
	Node(std::string& s)
	{
		value = Value(s);
		s.erase(0, raz(value));
		if (s[0] == '(')
			s = bracketopen(s);
		else return;
		if (Digit(s[0]))// условие создания левого поддерева
			left = new Node(s);
		if (s[0] == ',' && Digit(s[1]))//условие создания правого поддерева
		{
			s.erase(0, 1);
			right = new Node(s);
		}
	}

private:
	bool Digit(char c)//считываем строку
	{
		return Numerals.find(c) != std::string::npos;
	}
	int raz(int n)//поразрядно делим
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

	int Value(std::string& s)//преобразование строки в числа
	{
		int i = 0, tmp = 0;
		for (int i = 0; i < s.size(); i++)
			if (Digit(s[i]))
			{
				tmp = tmp * 10 + int(s[i] - 48);
				if (!Digit(s[i + 1]))
					return tmp;
			}
	}

	std::string bracketopen(std::string s)//раскрытие скобок
	{
		int brackets = 0;//счетчик скобок
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

public:
	BinaryTree(std::string s)
	{
		root = new Node(s);//выделяем память под корень 
	}

	void Print()
	{
		std::stack <Node*> stack; //создаем стек
		Node* tmp;
		stack.push(root);//корень-верхний элемент стека
		while (!stack.empty())//пока стек не пуст 
		{
			tmp = stack.top();//верхний элемент
			stack.pop();//удаляем и возвращаем верхний элемент
			//прямой обход дерева
			std::cout << tmp->value << ' ';
			if (tmp->right != nullptr) 
				stack.push(tmp->right);//вставляем объект правого поддерева как верхний элемент стека
			if (tmp->left!= nullptr) 
				stack.push(tmp->left);//вставляем объект левого поддерева как верхний элемент стека
		}
	}

};
int main() {
	std::string s = "8(3(1,6(4,7)),10(,14(13,)))";
	BinaryTree tree(s);
	tree.Print();

	return 0;
}