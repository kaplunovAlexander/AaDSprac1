#pragma once
#include <string>
#include <iostream>

class doublyLinkedList 
{
public:

	struct list
	{
		int data;
		list* head;
		list* tail;
	} *beg;

	int exec();

private:

	list* new_node(list* prev);

	list* list_of_nodes(std::string list_numbers, list* beg);

	void list_output(list* beg);

	list* clear_memory(list*& beg);

	int index_output(list* beg, bool flag = true);

	void list_output_for_swap(list* beg);

	int find_element(list* beg, int index, int value);

	bool delete_element(list*& beg, int index = -1, int value = -9999);

	int length(list* beg);

	list* incert_element(list*& beg, int index = -1, int value = -9999);

	list* swap_elements(int element1, int element2, list* beg);

	int menu(int key);
};


