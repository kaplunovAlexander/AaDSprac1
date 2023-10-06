#pragma once

#include <algorithm>
#include <iostream>

class dArray {

public:

	int len;

	int* array;
	
	int exec();

private:

	int menu(int k);

	int setLen();

	int* createArray(int* array, int len);

	void showArray();
	
	void deleteElementByVal(int val);

	void deleteElementByIndex(int index);

	void incertElement(int val, int index);

	void swapElements(int i1, int i2);

	void fillArray();
};