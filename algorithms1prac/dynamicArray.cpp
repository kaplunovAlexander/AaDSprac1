#include "dynamicArray.h"


int dArray::exec()
{
	int key = 1 << (sizeof(int) * 8) - 1;
	array = nullptr;
	len = 0;
	while (true)
	{
		key = menu(key);
		switch (key)
		{
		case 1:
		{
			std::cout << "set the length\n>>";
			len = setLen();
			array = createArray(array, len);
			std::cout << "input " << len << " array elements\n>>";
			fillArray();
			std::cout << "your array: ";
			showArray();
			break;
		}
		case 2:
		{
			std::cout << "your array: ";
			showArray();
			break;
		}
		case 3:
		{
			std::cout << "delete by index(1), by value(2)\n>>";
			int key;
			std::cin >> key;
			switch (key) 
			{
			case 1:
				std::cout << "select the index for delete: ";
				showArray();
				std::cout << ">>";
				int index;
				std::cin >> index;
				deleteElementByIndex(index);
				showArray();
				break;
			case 2:
				std::cout << "select the value for delete: ";
				showArray();
				std::cout << ">>";
				int val;
				std::cin >> val;
				deleteElementByVal(val);
				showArray();
				break;
			}
			break;
		}
		case 4:
		{
			showArray();
			std::cout << "input the value for incert\n>>";
			int val, index;
			std::cin >> val;
			std::cout << "input the index for incert\n>>";
			std::cin >> index;
			incertElement(val, index);
			showArray();
			break;
		}
		case 5:
		{
			std::cout << "select two indexes of elements for swap\n>>";
			showArray();
			int i1, i2;
			std::cin >> i1 >> i2;
			swapElements(i1, i2);
			showArray();
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

int dArray::menu(int key)
{
	if (key == 1 << (sizeof(int) * 8) - 1)
	{
		std::cout << "1. create array\n2. output array\n3. delete element\n4. add element\n5. swap elements\n0. choose another task\n";
	}
	std::cout << ">>";
	std::cin >> key;
	return key;
}

int dArray::setLen()
{
	int len;
	std::cin >> len; 
	return len;
}

int* dArray::createArray(int* array, int len)
{
	return array = new int[len];
}

void dArray::fillArray()
{
	for (int i = 0; i < len; i++)
	{
		std::cin >> array[i];
	}
}

void dArray::showArray()
{
	std::cout << "[ ";
	for (int i = 0; i < len; i++)
	{
		std::cout << array[i] << '(' << i << ") ";
	}
	std::cout << "]\n";
}

void dArray::deleteElementByVal(int val)
{
	int diff = 0;
	for (int i = 0; i < len; i++)
	{
		if (array[i] == val)
			diff++;
	}
	int* temp = new int[len - diff];
	for (int i = 0, k = 0; k < len - diff; k++)
	{
		if (array[i] != val)
		{
			temp[k] = array[i];
			i++;
		}
		else
		{
			if (i < len - 1)
			{
				temp[k] = array[++i];
				i++;
			}
		}
	}
	delete[] array;
	len = len - diff;
	array = new int[len];
	for (int i = 0; i < len; i++)
	{
		array[i] = temp[i];
	}
	delete[] temp;
}

void dArray::deleteElementByIndex(int index)
{
	int* temp = new int[--len];
	for (int i = 0; i < len; i++)
	{
		if (i < index)
		{
			temp[i] = array[i];
		}
		else if (i >= index)
		{
			if (index != len)
			{
				temp[i] = array[i + 1];
			}
		}
	}
	delete[] array;
	array = new int[len];
	for (int i = 0; i < len; i++)
	{
		array[i] = temp[i];
	}
	delete[] temp;
}

void dArray::incertElement(int val, int index)
{
	int* temp = new int[++len];
	for (int i = 0, k = 0; i < len; i++, k++)
	{
		if (k == index)
		{
			if (k < len - 1)
			{
				temp[i] = val;
				temp[++i] = array[k];
			}
			else
				temp[i] = val;
		}
		else
		{
			temp[i] = array[k];
		}
	}
	delete[] array;
	array = new int[len];
	for (int i = 0; i < len; i++)
	{
		array[i] = temp[i];
	}
	delete[] temp;
}

void dArray::swapElements(int i1, int i2) 
{
	std::swap(array[i1], array[i2]);
}