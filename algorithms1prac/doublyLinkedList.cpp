#include "doublyLinkedList.h"
#include <iostream>
#include <sstream>

using namespace std;

int doublyLinkedList::exec()
{
	int key = 1 << (sizeof(int) * 8) - 1;
	list* beg = nullptr;
	while (true)
	{
		key = menu(key);
		switch (key)
		{
		case 1:
		{
			if (beg)
			{
				clear_memory(beg);
			}
			string list_numbers;
			beg = list_of_nodes(list_numbers, beg);
			list_output(beg);
			break;
		}
		case 2:
		{
			list_output(beg);
			break;
		}
		case 3:
		{
			if (!beg) {
				cout << "error (empty list)\n";
				break;
			}
			int flag;
			std::cout << "delete by index(1) or by value(2)?\n>>";
			std::cin >> flag;
			if (flag == 1)
			{
				index_output(beg);
				int index;
				std::cin >> index;
				delete_element(beg, index);
				list_output(beg);
			}
			else if (flag == 2)
			{
				list_output(beg);
				int value;
				std::cin >> value;
				delete_element(beg, -1, value);
				list_output(beg);
			}
			else
			{
				cout << "invalid input\n>>";
				break;
			}
			break;
		}
		case 4:
		{
			if (!beg) {
				cout << "error (empty list)\n";
				break;
			}
			std::cout << "where should the element be inserted?\n>>";
			index_output(beg, false);
			int index, value;
			std::cin >> index;
			std::cout << "input the value\n>>";
			std::cin >> value;
			beg = incert_element(beg, index, value);
			list_output(beg);
			break;
		}
		case 5:
		{
			if (!beg) {
				cout << "error (empty list)\n";
				break;
			}
			list_output_for_swap(beg);
			int v1, v2;
			std::cout << "input two indexes\n>>";
			std::cin >> v1 >> v2;
			beg = swap_elements(v1, v2, beg);
			list_output(beg);
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

int doublyLinkedList::menu(int key)
{
	if (key == 1 << (sizeof(int) * 8) - 1)
	{
		std::cout << "1. create list\n2. output list\n3. delete element\n4. add element\n5. swap elements\n0. choose another task\n";
	}
	std::cout << ">>";
	std::cin >> key;
	return key;
}

doublyLinkedList::list* doublyLinkedList::new_node(list* prev)
{
	list* curr = new list;
	if (prev) prev->tail = curr;
	curr->head = prev, curr->tail = 0;
	return curr;
}

doublyLinkedList::list* doublyLinkedList::list_of_nodes(std::string list_numbers, list* beg)
{
	cout << "input integer values\n>>";
	cin.ignore();
	getline(cin, list_numbers);
	int node;
	stringstream ss(list_numbers);
	if (!ss) {
		cout << "empty list is created\n";
		return 0;
	}
	while (ss >> node) {
		beg = new_node(beg);
		beg->data = node;
	}
	if (ss.fail() && !ss.eof()) {
		cout << "invalid input\n";
		return 0;
	}
	if (beg) {
		while (beg->head) {
			beg = beg->head;
		}
	}
	return beg;
}

void doublyLinkedList::list_output(list* beg)
{
	cout << "\n[ ";
	do {
		if (!beg) {
			cout << "empty list ]\n";
			return;
		}
		cout << beg->data << " ";
		beg = beg->tail;
	} while (beg);
	cout << "]\n";
}

void doublyLinkedList::list_output_for_swap(list* beg)
{
	int i = 0;
	cout << "\n[ ";
	do {
		if (!beg) {
			cout << "empty list ]\n";
			return;
		}
		cout << beg->data << "(" << i << ")" << " ";
		beg = beg->tail;
		i++;
	} while (beg);
	cout << "]\n";
}

doublyLinkedList::list* doublyLinkedList::clear_memory(list*& beg)
{
	while (beg) {
		list* next = beg->tail;
		delete beg;
		beg = next;
	}
	return beg;
}

int doublyLinkedList::index_output(list* beg, bool flag)
{
	int i = 0;
	cout << "\n[ ";
	while (beg) {
		cout << i << " ";
		beg = beg->tail;
		i++;
	}
	if (flag == true)
	{
		cout << "]\n";
	}
	else
	{
		cout << i << "]\n";
	}
	return i;
}

int doublyLinkedList::find_element(list* beg, int index, int value)
{
	int i = 1;
	if (index) {
		while (beg) {
			if (index == i) {
				return beg->data;
			}
			i++;
			beg = beg->tail;
		}
		return 0;
	}
	else {
		while (beg) {
			if (beg->data == value) {
				return i;
			}
			i++;
			beg = beg->tail;
		}
		return 0;
	}
}

bool doublyLinkedList::delete_element(list*& beg, int index, int value)
{
	int i = 0;
	list* prev = NULL, * next = NULL, * curr = beg;
	while (beg) {
		if (index != -1) {
			if (i == index) {
				prev = beg->head;
				if (prev) {
					prev->tail = beg->tail;
				}
				if (beg->tail) {
					next = beg->tail;
					next->head = beg->head;
				}
				delete beg;
				if (!prev) beg = next;
				else beg = curr;
				return 1;
			}
		}
		else {
			if (beg->data == value) {
				prev = beg->head;
				if (prev) {
					prev->tail = beg->tail;
				}
				if (beg->tail) {
					next = beg->tail;
					next->head = beg->head;
				}
				delete beg;
				if (!prev) beg = next;
				else beg = curr;
				return 1;
			}
		}
		beg = beg->tail;
		i++;
	}
	beg = curr;
	return 0;
}

int doublyLinkedList::length(list* beg)
{
	int i = 0;
	while (beg) {
		i++;
		beg = beg->tail;
	}
	return i;
}

doublyLinkedList::list* doublyLinkedList::incert_element(list*& beg, int index, int value)
{
	int i = 0;
	list* curr = beg, * begin = curr;
	if (!beg) {
		list* new_element = new list;
		new_element->data = value;
		new_element->tail = 0, new_element->head = 0;
		return new_element;
	}
	while (beg) {
		if (i == index) {
			list* new_element = new list, * prev = beg->head;
			new_element->data = value;
			if (prev) prev->tail = new_element;
			beg->head = new_element;
			new_element->head = prev;
			new_element->tail = beg;
			if (!prev) {
				
				return new_element;
			}
			else {
				
				return curr;
			}
		}
		beg = beg->tail;
		i++;
	}
	while (curr->tail) {
		curr = curr->tail;
	}
	list* new_element = new list;
	new_element->data = value;
	curr->tail = new_element;
	new_element->head = curr;
	new_element->tail = NULL;
	return begin;
}

doublyLinkedList::list* doublyLinkedList::swap_elements(int element1, int element2, list* beg)
{
	list* curr = beg, * e1 = NULL, * e2 = NULL;
	int i = 0;
	while (curr) {
		if (i == element2) e2 = curr;
		if (i == element1) e1 = curr;
		curr = curr->tail;
		i++;
	}
	if (!e1 || !e2) {
		cout << "value is not found\n";
		return beg;
	}
	list* prev1 = e1->head, * next1 = e1->tail, * prev2 = e2->head, * next2 = e2->tail;
	if (next1 == e2) {
		e2->tail = e1;
		e2->head = prev1;
		e1->tail = next2;
		e1->head = e2;
		if (next2) next2->head = e1;
		if (prev1) prev1->tail = e2;
	}
	else if (next2 == e1) {
		e1->tail = e2;
		e1->head = prev2;
		e2->tail = next1;
		e2->head = e1;
		if (next1) next1->head = e2;
		if (prev2) prev2->tail = e1;
	}
	else {
		if (prev1) prev1->tail = e2;
		e2->tail = next1;
		if (prev2) prev2->tail = e1;
		e1->tail = next2;
		e2->head = prev1;
		if (next2) next2->head = e1;
		e1->head = prev2;
		if (next1) next1->head = e2;
	}
	if (e1 == beg) {
		return e2;
	}
	if (e2 == beg) {
		return e1;
	}
	return beg;
}
