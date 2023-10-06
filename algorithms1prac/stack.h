#pragma once
#include <iostream>

class Stack
{
public:

	struct stack {
		int data;
		stack* tail;
	};

	int exec();

private:

	int menu(int key);

	stack* push(stack* numbers, int c);

	bool empty(stack* numbers);

	stack* pop(stack* numbers);

	int top(stack* numbers);

	int size(stack* numbers);

	void printStack(stack* numbers);
};