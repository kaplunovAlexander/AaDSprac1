#include "stack.h"

int Stack::exec()
{
	int key = 1 << (sizeof(int) * 8) - 1;
	stack* newStack = nullptr;
	while (true)
	{
		key = menu(key);
		switch (key)
		{
		case 1:
		{
			int value;
			std::cout << "input value\n>>";
			std::cin >> value;
			newStack = push(newStack, value);
			std::cout << "element added\n";
			break;
		}
		case 2:
		{
			newStack = pop(newStack);
			std::cout << "element poped\n";
			break;
		}
		case 3:
		{
			std::cout << "top element: " << top(newStack) << '\n';
			break;
		}
		case 4:
		{
			std::cout << "stack size: " << size(newStack) << '\n';
			break;
		}
		case 5:
		{
			printStack(newStack);
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

int Stack::menu(int key)
{
	if (key == 1 << (sizeof(int) * 8) - 1)
	{
		std::cout << "STACK\n1. push element\n2. pop element\n3. return top\n4. return stack size\n5. print stack\n0. choose another task\n";
	}
	std::cout << ">>";
	std::cin >> key;
	return key;
}

Stack::stack* Stack::push(stack* numbers, int c) 
{
	stack* next = new stack;
	next->data = c;
	next->tail = numbers;
	return next;
}

bool Stack::empty(stack* numbers) 
{
	if (!numbers) return 1;
	else return 0;
}

Stack::stack* Stack::pop(stack* numbers) 
{
	stack* prev = numbers->tail;
	delete numbers;
	numbers = prev;
	return numbers;
}

int Stack::top(stack* numbers) 
{
	return numbers->data;
}

int Stack::size(stack* numbers) 
{
	int size = 0; 
	while (!empty(numbers)) 
	{
		size++;
		numbers = numbers->tail;
	}
	return size;
}

void Stack::printStack(stack* numbers)
{
	while (!empty(numbers)) 
	{
		std::cout << numbers->data << ' ';
		numbers = numbers->tail;
	}
	std::cout << '\n';
}
