//Лаба №15 “Рекурсивные обходы(прямой, центральный, концевой)”!
#include <iostream>
#include <string>
const std::string Numerals = { "1234567890" };//объявляем набор возможных символов
//читаем выражение s
struct Node
{
	int value;
	Node* left = nullptr, *right = nullptr;//пустые поддеревья 
	//создаем бинарное дерево с помощью выражения
	Node(std::string& s)
	{
		value = Value(s);
		s.erase(0, raz(value));
		if (s[0] == '(')
			s = bracketopen(s);
		else return;
		if (Digit(s[0]))//условие добавления в левый потомок 
			left = new Node(s);
		if (s[0] == ',' && Digit(s[1]))//условие добавления в правый потомок 
		{
			s.erase(0, 1);
			right = new Node(s);
		}
	}

private:
	bool Digit(char c)//поиск чисел до конца строки 
	{
		return Numerals.find(c) != std::string::npos;
	}
	int raz(int n)//разделяем поразрядно
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

	int Value(std::string& s)////преобразовываем строку в числа
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

public:
	BinaryTree(std::string s)
	{
		root = new Node(s);//выделяем память для корня 
	}

	void preorder()//функция прямого обхода с выводом результата 
	{
		Ppreorder(root);  
		std::cout << "\n";
	}
	void inorder()//функция центрального обхода с выводом результата 
	{
		Iinorder(root); 
		std::cout << "\n";
	}
	void postorder()//функция концевого обхода с выводом результата 
	{ 
		Ppostorder(root);
		std::cout << "\n"; 
	
}

	void Ppreorder(Node* n)//прямой обход
		/*Посетите корневой узел
		Посетите все узлы в левом поддереве
		Посетите все узлы в правом поддереве*/
	{
		if (!n) return;
		std::cout << n->value << " ";
		Ppreorder(n->left);
		Ppreorder(n->right);
	}

	void Iinorder(Node* n)//центральный обход
		/*Сначала посетите все узлы в левом поддереве
		Затем корневой узел
		Посетите все узлы в правом поддереве*/
	{
		if (!n) return;
		Iinorder(n->left);
		std::cout << n->value << " ";
		Iinorder(n->right);
	}

	void Ppostorder(Node* n)//концевой обход
		/*посетить все узлы в левом поддереве
		посетить все узлы в правом поддереве*/
		/*посетить корневой узел*/	
	{
		if (!n) return;
		Ppostorder(n->left);
		Ppostorder(n->right);
		std::cout << n->value << " ";
	}
};
int main() {
	std::string s = "8(3(1,6(4,7)),10(,14(13,)))";//исходная строка
	BinaryTree tree(s);//заполнение дерева
	tree.preorder();//выполнение прямого обхода
	tree.inorder();//выполнение центрального обхода
	tree.postorder();//выполненеие концевого обхода

	return 0;
}