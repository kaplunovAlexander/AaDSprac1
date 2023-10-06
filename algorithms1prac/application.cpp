#include "application.h"
#include <iostream>
#include <cstdlib>

const std::string red("\033[0;31m");
const std::string green("\033[0;32m");
const std::string blue("\033[0;34m");
std::string reset("\033[0m");

int Algorithm::exec()
{
	int key = -1;
	while (true) 
	{
		key = menu(key);
		switch (key) 
		{
			case 1:
			{
				if (system("CLS")) system("clear");
				dArray arr;
				arr.exec();
				if (system("CLS")) system("clear");
				break;
			}
			case 2:
			{
				if (system("CLS")) system("clear");
				doublyLinkedList list;
				list.exec();
				if (system("CLS")) system("clear");
				break;
			}
			case 3:
			{
				if (system("CLS")) system("clear");
				Stack stack;
				stack.exec();
				if (system("CLS")) system("clear");
				break;
			}
			case 4:
			{
				if (system("CLS")) system("clear");
				pNotation notation;
				notation.exec();
				if (system("CLS")) system("clear");
				break;
			}
			case 0:
			{
				return 0;
			}
			default:
			{
				std::cout << "invalid input\n";
				key = menu(key);
				break;
			}
		}
	}
}

int Algorithm::menu(int key)
{
	std::cout << "1. Dynamic array\n2. Doubly linked list\n3. Stack\n4. Postfix notation\n0. Close the application\n";
	std::cout << ">>";
	std::cin >> key;
	return key;
}
