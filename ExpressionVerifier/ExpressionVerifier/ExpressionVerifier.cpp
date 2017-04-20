
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define MAX 100

struct stack {
	char items[MAX];
	int iItems[MAX];
	int top;
};

void push(stack *s, char key) {
	s->items[++s->top] = key;
}

void iPush(stack *s, int key) {
	s->iItems[++s->top] = key;
}

char pop(stack *s) {
	return s->items[s->top--];
}

int iPop(stack *s) {
	return s->iItems[s->top--];
}

char peek(stack *s) {
	return s->items[s->top];
}

char iPeek(stack *s) {
	return s->iItems[s->top];
}

bool empty(stack *s) {
	if (s->top == -1) {
		return true;
	}
	else return false;
}

void startStack(stack *s) {
	s->top = -1;
}


bool isOperator(char operatorValue) {

	if (operatorValue == '+' || operatorValue == '-' || operatorValue == '*' || operatorValue == '/' || operatorValue == '^' || operatorValue == '%')
		return true;

	return false;
}

bool isBoolOperator(char operatorValue) {

	if (operatorValue == '+' || operatorValue == '*')
		return true;

	return false;
}

int checkBoolPrecedence(char key) {
	if (key == '+') {
		return 1;
	}
	else if (key == '*') {
		return 2;
	}
	else return 0;
}

int checkSetPrecedence(char key) {
	if (key == '+') {
		return 1;
	}
	else if (key == '*') {
		return 2;
	}
	else return 0;
}

int checkPrecedence(char key) {
	if (key == '+' || key == '-') {
		return 1;
	}
	else if (key == '*') {
		return 2;
	}
	else if (key == '^') {
		return 3;
	}
	else return 0;
}

bool orderBoolCheck(char key1, char key2) {
	if (checkBoolPrecedence(key1) < checkBoolPrecedence(key2)) {
		return true;
	}
	else return false;
}

bool orderSetCheck(char key1, char key2) {
	if (checkSetPrecedence(key1) < checkSetPrecedence(key2)) {
		return true;
	}
	else return false;
}

bool orderCheck(char key1, char key2) {
	if (checkPrecedence(key1) < checkPrecedence(key2)) {
		return true;
	}
	else return false;
}

void postfixCalc(const char *str) {
	stack s;
	startStack(&s);
	while (*str != '\0') {
		if (!isOperator(*str)) {
			iPush(&s, *str - 0x30);
		}
		else {
			if (*str == '+') {
				int o2 = iPop(&s);
				int o1 = iPop(&s);
				iPush(&s, (o1 + o2));
			}
			else if (*str == '-') {
				int o2 = iPop(&s);
				int o1 = iPop(&s);
				iPush(&s, (o1 - o2));
			}
			else if (*str == '*') {
				int o2 = iPop(&s);
				int o1 = iPop(&s);
				iPush(&s, (o1 * o2));
			}
			else if (*str == '^') {
				int o2 = iPop(&s);
				int o1 = iPop(&s);
				iPush(&s, (pow(o1, o2)));
			}
			else {
				std::cout << "Invalid Operation: " << *str;
				exit(1);
			}
		}
		str++;
	}
	std::cout << iPop(&s);
}

void infixToPostfix(const char *str) {
	stack s;
	//Stack<char> s;
	startStack(&s);
	char *out = (char *)malloc(strlen(str));
	char *outp = out;

	while (*str != '\0') {
		// case 1: if '(' push to stack
		if (*str == '(')
		{
			push(&s, '(');
		}

		// case 2: if ')' pop all from stack until '('
		else if (*str == ')') {
			while (!empty(&s) && peek(&s) != '(') {
				*out = pop(&s);
				out++;
			}
			if (!empty(&s)) pop(&s);
		}
		// case 3: If operator, pop all operator with more precedence. Push it to stack.
		else if (isOperator(*str)) {
			while (!empty(&s) && (!orderCheck(peek(&s), *str))) {
				*out = pop(&s);
				out++;
			}
			push(&s, *str);
		}
		// case 4: Add to postfix expression
		else {
			*out = *str;
			out++;
		}
		str++; // next char
	}
	// empty out stack
	while (!empty(&s)) {
		*out = pop(&s);
		out++;
	}
	*out = '\0';
	printf("%s\n", outp);
	postfixCalc(outp);
}

void booleanVerifier(const char *str) {
	stack s;
	startStack(&s);
	char *out = (char *)malloc(strlen(str));
	char *outp = out;

	while (*str != '\0') {
		// case 1: if '(' push to stack
		if (*str == '(')
		{
			push(&s, '(');
		}

		// case 2: if ')' pop all from stack until '('
		else if (*str == ')') {
			while (!empty(&s) && peek(&s) != '(') {
				*out = pop(&s);
				out++;
			}
			if (!empty(&s)) pop(&s);
		}
		// case 3: If operator, pop all operator with more precedence. Push it to stack.
		else if (isBoolOperator(*str)) {
			while (!empty(&s) && (!orderBoolCheck(peek(&s), *str))) {
				*out = pop(&s);
				out++;
			}
			push(&s, *str);
		}
		// case 4: Add to postfix expression
		else {
			*out = *str;
			out++;
		}
		str++; // next char
	}
	// empty out stack
	while (!empty(&s)) {
		*out = pop(&s);
		out++;
	}

	*out = '\0';
	printf("%s\n", outp);
	postfixCalc(outp);
}

bool isSetOperator(char operatorValue) {

	if (operatorValue == '+' || operatorValue == '*')
		return true;

	return false;
}

void setVerifier(const char *str) {
	stack s;
	startStack(&s);
	char *out = (char *)malloc(strlen(str));
	char *outp = out;

	while (*str != '\0') {
		// case 1: if '(' push to stack
		if (*str == '(')
		{
			push(&s, '(');
		}

		// case 2: if ')' pop all from stack until '('
		else if (*str == ')') {
			while (!empty(&s) && peek(&s) != '(') {
				*out = pop(&s);
				out++;
			}
			if (!empty(&s)) pop(&s);
		}
		// case 3: If operator, pop all operator with more precedence. Push it to stack.
		else if (isSetOperator(*str)) {
			while (!empty(&s) && (!orderSetCheck(peek(&s), *str))) {
				*out = pop(&s);
				out++;
			}
			push(&s, *str);
		}
		// case 4: Add to postfix expression
		else {
			*out = *str;
			out++;
		}
		str++; // next char
	}
	// empty out stack
	while (!empty(&s)) {
		*out = pop(&s);
		out++;
	}

	*out = '\0';
	printf("%s\n", outp);
	postfixCalc(outp);
}


enum parserType {
	algebraType,
	booleanType,
	stringType,
	setType,
	nonType //Time before you get to a block

};

void expressionparser(std::fstream &inputfile, parserType type)
{
	char ch;

	while ((ch = inputfile.get()) != '\0') {
		if (ch == ' ')
		{
			continue;
		}
		if (ch == '\t')
		{
			continue;
		}
		if (ch == '<')
		{
			//parse string
			std::string str;
			inputfile >> str;

			if (str == "algebra")
			{
				inputfile >> str;
				expressionparser(inputfile, algebraType);
			}
			else if (str == "boolean")
			{
				inputfile >> str;
				expressionparser(inputfile, booleanType);
			}
			else if (str == "sets")
			{
				inputfile >> str;
				expressionparser(inputfile, setType);
			}
			else if (str == "strings")
			{
				inputfile >> str;
				expressionparser(inputfile, stringType);
			}
			else if (str == "/")
			{
				inputfile >> str;
				return;
			}

			continue;
		}

		std::string algString;
		std::string booleanString;
		std::string setString;
		// specific to what needs to be parsing depending on the type
		switch (type)
		{
		case algebraType:

			while ((ch = inputfile.get()) != '\0')
			{
				if (ch != '<' && ch != ';')
				{
					algString += ch;
				}
				else
					break;
			}
			if (ch == '<')
			{
				inputfile.putback('<');
			}

			infixToPostfix(algString.c_str());
			break;

		case booleanType:
			while ((ch = inputfile.get()) != '\0')
			{
				if (ch != '<')
				{
					if (ch == '=')
					{
						booleanVerifier(booleanString.c_str());
						booleanString = "";
						continue;
					}

					if (ch == '0' || ch == '1' || ch == '+' || ch == '*')
					{
						booleanString += ch;
					}
					else if (ch != ' ')
					{
						std::cout << "Invalid characters for Boolean" << std::endl;
					}
				}
			}

			if (ch == '<')
			{
				inputfile.putback('<');
			}

			booleanVerifier(booleanString.c_str());
			
			break;

		case stringType:
			while ((ch = inputfile.get()) != '\0')
			{

			}

			if (ch == '<')
			{
				inputfile.putback('<');
			}

			break;

		case setType:
			while ((ch = inputfile.get()) != '\0')
			{
				if (ch != '<' && ch != ';')
				{
					if (ch == '=')
					{
						setVerifier(setString.c_str());
						setString = "";
						continue;
					}
					if (ch == '+' || ch == '*' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || (ch >= '0' && ch <= '9'))
					{
						setString += ch;
					}
					else if (ch != ' ')
					{
						std::cout << "Invalid characters for Set" << std::endl;
					}
				}
			}

			if (ch == '<')
			{
				inputfile.putback('<');
			}

			setVerifier(setString.c_str());
			break;

		case nonType:
			break;
		}

	}
}

int main(int argc, char *argv[])
{
	// Instantiate stack.
	// std::vector<std::streamoff> callStack;
	//binaryTree BSTree;

	std::string singleLine = "";
	std::fstream inputFile("input.txt", std::ios_base::in | std::ios_base::binary);
	std::ofstream outputFile("outputFile.txt");
	//stack.assignLabels(inputFile); // Assign labels to a line number.

	std::cout << "\nThe following is what the input file contains: \n\n";

	if (inputFile.is_open())
	{
		//while (!inputFile.eof() && getline(inputFile, singleLine))
		//{
		//	std::cout << singleLine << std::endl;
		//	//BSTree.insertNodeIntoTree(singleLine, BSTree.rootPointer);

		//	

		//}
		expressionparser(inputFile, nonType);

		std::cout << "=======================================Below is what the outcome looks like:" << std::endl;

		//BSTree.postOrder(BSTree.rootPointer);
		infixToPostfix(singleLine.c_str());

		inputFile.close();
	}
	else
	{
		std::cout << "Error: File is unable to open.  Check the location and the name of the file for possible errors.";
	}

	// Wait for user to press 'Enter' to exit program
	outputFile.close();
	char WaitChar;

	std::cout << "\nProccessing finished. Press 'Enter' to exit the program: \n\n";
	std::cin.get(WaitChar);
	return 0;
}