#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <queue>

class pNotation
{
public:

	int exec();

private:
	
	int menu(int key);

	int priority(char c);

	bool correction(std::string& s);

	std::string notation(std::string s);

	int calculate(std::string s);

};