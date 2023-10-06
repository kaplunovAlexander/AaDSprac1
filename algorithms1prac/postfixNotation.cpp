#include "postfixNotation.h"

int pNotation::exec()
{
	int key = 1 << (sizeof(int) * 8) - 1; 
	std::string str, str_out;
	while (true)
	{
		key = menu(key);
		switch (key)
		{
		case 1:
		{
			std::cin.ignore();
			std::cout << "input expression: ";
			std::getline(std::cin, str);
			while (str == "" || !correction(str)) {
				std::cout << "Invalid input\n\ninput expression: ";
				std::getline(std::cin, str);
			}
			str_out = notation(str);
			std::cout << "Reverse Polish notation: " << str_out << '\n';
			std::cout << "calculations: \n";
			std::cout << "ans: " << calculate(str_out) << "\n\n";
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

int pNotation::menu(int key)
{
	if (key == 1 << (sizeof(int) * 8) - 1)
	{
		std::cout << "1. input expression to convert\n0. choose another task\n";
	}
	std::cout << ">>";
	std::cin >> key;
	return key;
}

int pNotation::priority(char c)
{
	switch (c) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	default: return -1;
	}
}

bool pNotation::correction(std::string& s)
{
	std::stack <char> par;
	for (int i = 1; i < s.length() - 1; i++) {
		if (s[i] == ' ' && priority(s[i - 1]) == -1 && priority(s[i + 1]) == -1) return 0;
	}
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') s.erase(i, 1);
	}
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') par.push(s[i]);
		else if (s[i] == ')')
			if (!par.empty()) par.pop();
			else return 0;
	}
	if (!par.empty()) return 0;
	for (int i = 1; i < s.length() - 1; i++) {
		if (s[i] == '(' && (priority(s[i - 1]) == -1 || s[i - 1] == ')')) {
			s.insert(i, "*");
		}
		else if (s[i] == ')' && (priority(s[i + 1]) == -1 || s[i + 1] == '(')) {
			s.insert(i + 1, "*");
		}
	}
	for (int i = 1; i < s.length(); i++) {
		if (s[i - 1] == '+' && s[i] == '-') s.erase(i - 1, 1);
		else if (s[i - 1] == '-' && s[i] == '-') {
			s.insert(i - 1, "+");
			s.erase(i, 2);
		}
		else if (priority(s[i - 1]) > 0 && priority(s[i]) > 0 && s[i] != '-') return 0;
	}
	for (int i = 0, k = 0; i < s.length(); i++) {
		if (priority(s[i]) > 0) k++;
		if (i == 1 && s[i - 1] != '-' && priority(s[i - 1]) > 0) return 0;
		else if (i == s.length() - 1 && priority(s[i]) > 0 || i == s.length() - 1 && !k) return 0;
	}
	return 1;
}

std::string pNotation::notation(std::string s)
{
	std::cout << "corrected expression: " << s << '\n';
	std::string n;
	std::stack <char> stack;
	std::queue <char> queue;
	for (int i = 0, flag; i < s.length(); i++) {
		if (s[i] == '-') {
			if (i == 0 && priority(s[i + 1]) == -1) {
				queue.push(s[i]);
				continue;
			}
			else if (priority(s[i - 1]) > 1 && priority(s[i + 1]) == -1) {
				queue.push(s[i]);
				continue;
			}
		}
		flag = priority(s[i]);
		if (flag == 0) {
			if (s[i] == '(') {
				while (!queue.empty()) {
					n += queue.front();
					queue.pop();
					if (queue.empty()) n += ' ';
				}
				stack.push(s[i]);
			}
			else {
				while (!queue.empty()) {
					n += queue.front();
					queue.pop();
					if (queue.empty()) n += ' ';
				}
				while (!stack.empty()) {
					if (stack.top() != '(') {
						n += stack.top();
						stack.pop();
						n += ' ';
					}
					else {
						stack.pop();
						break;
					}
				}
			}
		}
		else if (flag == 1) {
			while (!queue.empty()) {
				n += queue.front();
				queue.pop();
				if (queue.empty()) n += ' ';
			}
			if (stack.empty() || priority(stack.top()) < flag) {
				stack.push(s[i]);
			}
			else {
				while (!stack.empty() && priority(stack.top()) >= flag) {
					n += stack.top();
					stack.pop();
					n += ' ';
				}
				stack.push(s[i]);
			}
		}
		else if (flag == 2) {
			while (!queue.empty()) {
				n += queue.front();
				queue.pop();
				if (queue.empty()) n += ' ';
			}
			if (stack.empty() || priority(stack.top()) < flag) {
				stack.push(s[i]);
			}
			else {
				while (!stack.empty() && priority(stack.top()) >= flag) {
					n += stack.top();
					stack.pop();
					n += ' ';
				}
				stack.push(s[i]);
			}
		}
		else queue.push(s[i]);
	}
	while (!queue.empty()) {
		n += queue.front();
		queue.pop();
		if (queue.empty()) n += ' ';
	}
	while (!stack.empty()) {
		n += stack.top();
		stack.pop();
		n += ' ';
	}
	return n;
}

int pNotation::calculate(std::string s)
{
	std::string num = "";
	int num_1, num_2;
	std::stack <int> stack;
	for (int i = 0, k = 1; i < s.length(); i++) {
		if (priority(s[i]) == -1 && s[i] != ' ') {
			while (s[i] != ' ') {
				num += s[i];
				i++;
			}
			stack.push(stoi(num));
			std::cout << k << ". put on the stack " << num << '\n';
			k++;
			num = "";
		}
		else if (priority(s[i]) == 1) {
			if (s[i] == '+') {
				num_1 = stack.top();
				stack.pop();
				num_2 = stack.top();
				stack.pop();
				stack.push(num_2 + num_1);
				std::cout << k << ". remove from the stack " << num_2 << " è " << num_1 << ", adding up and put on the stack " << num_1 + num_2 << '\n';
				k++;
			}
			if (s[i] == '-' && i < s.length() - 1 && s[i + 1] == ' ') {
				num_1 = stack.top();
				stack.pop();
				num_2 = stack.top();
				stack.pop();
				stack.push(num_2 - num_1);
				std::cout << k << ". remove from the stack " << num_2 << " è " << num_1 << ", subtract and put on the stack " << num_2 - num_1 << '\n';
				k++;
			}
			else if (s[i] == '-' && i < s.length() - 1 && priority(s[i + 1]) == -1) {
				while (s[i] != ' ') {
					num += s[i];
					i++;
				}
				stack.push(stoi(num));
				std::cout << k << ". put on the stack " << num << '\n';
				k++;
				num = "";
			}
		}
		else if (priority(s[i]) == 2) {
			if (s[i] == '*') {
				num_1 = stack.top();
				stack.pop();
				num_2 = stack.top();
				stack.pop();
				stack.push(num_2 * num_1);
				std::cout << k << ". remove from the stack " << num_2 << " è " << num_1 << ", multiply and put on the stack " << num_1 * num_2 << '\n';
				k++;
			}
			if (s[i] == '/') {
				num_1 = stack.top();
				stack.pop();
				num_2 = stack.top();
				stack.pop();
				stack.push(num_2 / num_1);
				std::cout << k << ". remove from the stack " << num_2 << " è " << num_1 << ", divide and put on the stack " << num_2 / num_1 << '\n';
				k++;
			}
		}
	}
	std::cout << "returning the top element of the stack\n";
	return stack.top();
}
