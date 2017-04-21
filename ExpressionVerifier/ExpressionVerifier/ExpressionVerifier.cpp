#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
std::ofstream outputFile("outputFile.txt");

#define MAX 100


struct stack {
	char items[MAX];
	int iItems[MAX];
	std::string strI[MAX];
	int top;
};

void push(stack *s, char key) {
	s->items[++s->top] = key;
}

void iPush(stack *s, int key) {
	s->iItems[++s->top] = key;
}

void sPush(stack *s, std::string key) {
	s->strI[++s->top] = key;
}

char pop(stack *s) {
	return s->items[s->top--];
}

int iPop(stack *s) {
	return s->iItems[s->top--];
}

std::string sPop(stack *s) {
	return s->strI[s->top--];
}

char peek(stack *s) {
	return s->items[s->top];
}

char iPeek(stack *s) {
	return s->iItems[s->top];
}

std::string sPeek(stack *s) {
	return s->strI[s->top];
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

stack parser(std::string str) {
	// Take an input string and break it up.
	stack s;
	startStack(&s);
	std::string in = str;
	in.erase(std::remove(in.begin(), in.end(), ' '), in.end()); // remove all spaces

	int numOfEqSigns = std::count(in.begin(), in.end(), '='); // count number of equal signs


															  // if no equal sign, throw error at user and quit
	if (numOfEqSigns == 0) 
	{ 
		std::cout << "Expression cannot be compared."; 
		outputFile << "Expression is invalid" << std::endl;
		exit(1);
	}

	std::string inOne = in.substr(0, in.find('='));
	std::string inTwo = in.substr(in.find('=') + 1, in.size());

	sPush(&s, inOne);
	sPush(&s, inTwo);

	return s;
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

int postfixCalc(const char *str) {
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
				outputFile << "Expression is invalid" << std::endl;
				exit(1);
			}
		}
		str++;
	}
	return iPop(&s);
}

bool infixToPostfix(const char *str) {
	stack s;			// current stack
	startStack(&s);
	char *out = (char *)malloc(strlen(str));
	char *outp = out;

	stack inputStack; // store stack
	startStack(&inputStack);
	inputStack = parser(str);
	stack outputStack; // result stack
	startStack(&outputStack);

	std::string strarry[2];
	int it = 1;

	while (!empty(&inputStack)) 
	{
		const char *tempString = sPop(&inputStack).c_str();
		strarry[it--] = tempString;
		
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
		iPush(&outputStack, 0);//postfixCalc(outp));
	}
	
	//printf("%s\n", outp);
	//std::string rstrarry[2];
	//rstrarry[1] = sPop(&outputStack).c_str();
	//rstrarry[0] = sPop(&outputStack).c_str();


	//for (int i = strarry->size(), j = 0; i > 0; i--, j++) {
	//	std::string str = rstrarry[j];

	//	for (int i = strarry->size(), k = 1; i > 0; i--, k++) {

	//		if (str != rstrarry[k])
	//		{
	//			std::cout << str << "!=" << rstrarry[k];
	//			return false;
	//		}
	//		else
	//		{
	//			std::cout << str << "=" << rstrarry[k];
	//		}
	//	}
	//}
	if (outputStack.top != 1)
	{
		return false;
	}

	return true;
}

bool booleanVerifier(const char *str) {
	stack s;			// current stack
	startStack(&s);
	char *out = (char *)malloc(strlen(str));
	char *outp = out;

	stack inputStack; // store stack
	startStack(&inputStack);
	inputStack = parser(str);
	stack outputStack; // result stack
	startStack(&outputStack);

	std::string strarry[2];
	int it = 1;

	while (!empty(&inputStack))
	{
		const char *tempString = sPop(&inputStack).c_str();
		strarry[it--] = tempString;

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
		//iPush(&outputStack, postfixCalc(outp));
		iPush(&outputStack, 0);
	}

	////printf("%s\n", outp);
	//std::string rstrarry[2];
	//rstrarry[1] = sPop(&outputStack).c_str();
	//rstrarry[0] = sPop(&outputStack).c_str();


	//for (int i = strarry->size(), j = 0; i > 0; i--, j++) {
	//	std::string str = rstrarry[j];

	//	for (int i = strarry->size(), k = 1; i > 0; i--, k++) {

	//		if (str != rstrarry[k])
	//		{
	//			std::cout << str << "!=" << rstrarry[k];
	//			return false;
	//		}
	//		else
	//		{
	//			std::cout << str << "=" << rstrarry[k];
	//		}
	//	}
	//}
	if (outputStack.top != 1)
	{
		return false;
	}

	return true;
}

bool isSetOperator(char operatorValue) {

	if (operatorValue == '+' || operatorValue == '*')
		return true;

	return false;
}

bool setVerifier(const char *str) {
	stack s;			// current stack
	startStack(&s);
	char *out = (char *)malloc(strlen(str));
	char *outp = out;

	stack inputStack; // store stack
	startStack(&inputStack);
	inputStack = parser(str);
	stack outputStack; // result stack
	startStack(&outputStack);

	std::string strarry[2];
	int it = 1;

	while (!empty(&inputStack))
	{
		const char *tempString = sPop(&inputStack).c_str();
		strarry[it--] = tempString;

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
		//iPush(&outputStack, postfixCalc(outp));
		iPush(&outputStack, 0);
	}

	//printf("%s\n", outp);
	//std::string rstrarry[2];
	//rstrarry[1] = sPop(&outputStack).c_str();
	//rstrarry[0] = sPop(&outputStack).c_str();


	//for (int i = strarry->size(), j = 0; i > 0; i--, j++) {
	//	std::string str = rstrarry[j];

	//	for (int i = strarry->size(), k = 1; i > 0; i--, k++) {

	//		if (str != rstrarry[k])
	//		{
	//			std::cout << str << "!=" << rstrarry[k];
	//			return false;
	//		}
	//		else
	//		{
	//			std::cout << str << "=" << rstrarry[k];
	//		}
	//	}
	//}
	if (outputStack.top != 1)
	{
		return false;
	}

	return true;
}


enum parserType {
	algebraType,
	booleanType,
	stringType,
	setType,
	nonType //Time before you get to a block

};

bool expressionParser(std::fstream &inputfile, parserType type, std::ofstream &outputFile)
{
	char isChar;

	while ((isChar = inputfile.get()) != '\0') {
		if (isChar == ' ')
		{
			continue;
		}
		if (isChar == '\t')
		{
			continue;
		}
		if (isChar == '<')
		{
			//parse string
			std::string str;
			inputfile >> str;

			if (str == "algebra")
			{
				inputfile >> str;
				if (str != ">")
				{
					return false;
				}
				expressionParser(inputfile, algebraType, outputFile);
			}
			else if (str == "boolean")
			{
				inputfile >> str;
				if (str != ">")
				{
					return false;
				}
				expressionParser(inputfile, booleanType, outputFile);
			}
			else if (str == "sets")
			{
				inputfile >> str;
				if (str != ">")
				{
					return false;
				}
				expressionParser(inputfile, setType, outputFile);
			}
			else if (str == "strings")
			{
				inputfile >> str;
				if (str != ">")
				{
					return false;
				}
				expressionParser(inputfile, stringType, outputFile);
			}
			else if (str == "/")
			{
				inputfile >> str;
				if (str != ">")
				{
					return false;
				}
				return true;
			}
			else
			{
				return false;
			}

			continue;
		}

		std::string stringsString;
		std::string algString;
		std::string booleanString;
		std::string setString;
		// specific to what needs to be parsing depending on the type
		switch (type)
		{
		case algebraType:

			while ((isChar = inputfile.get()) != '\0')
			{
				if (isChar != '<' && isChar != ';')
				{
					algString += isChar;
				}
				else
					break;
			}
			if (isChar == '<')
			{
				inputfile.putback('<');
			}

			//outputFile << "Expression is = " << infixToPostfix(algString.c_str()) << std::endl;
			if (!infixToPostfix(algString.c_str()))
			{
				return false;
			}

			break;

		case booleanType:
			while ((isChar = inputfile.get()) != '\0')
			{
				if (isChar != '<' && isChar != ';')
				{
					if (isChar == '=')
					{
						booleanVerifier(booleanString.c_str());
						booleanString = "";
						continue;
					}

					if (isChar == '0' || isChar == '1' || isChar == '+' || isChar == '*')
					{
						booleanString += isChar;
					}
					else if (isChar != ' ')
					{
						std::cout << "Invalid characters for Boolean" << std::endl;
					}
				}
			}

			if (isChar == '<')
			{
				inputfile.putback('<');
			}

			//outputFile << "Expression is = " << booleanVerifier(booleanString.c_str()) << std::endl;

			if (!booleanVerifier(booleanString.c_str()))
			{
				return false;
			}
			
			break;

		case stringType:
			while ((isChar = inputfile.get()) != '\0')
			{
				if (isChar != '<' && isChar != ';')
				{
					if (isChar == '=')
					{
						setVerifier(setString.c_str());
						setString = "";
						continue;
					}
					if (isChar == '+' || isChar == '*' || isChar == '{' || isChar == '}' || isChar == '(' || isChar == ')' || (isChar >= '0' && isChar <= '9') || (isChar >= 'a' && isChar <= 'z'))
					{
						setString += isChar;
					}
					else if (isChar != ' ')
					{
						std::cout << "Invalid characters for Set" << std::endl;
					}
				}
			}

			if (isChar == '<')
			{
				inputfile.putback('<');
			}

			//outputFile << "Expression is = " << infixToPostfix(stringsString.c_str()) << std::endl;
			if (!setVerifier(stringsString.c_str()))
			{
				return false;
			}

			break;

		case setType:
			while ((isChar = inputfile.get()) != '\0')
			{
				if (isChar != '<' && isChar != ';')
				{
					if (isChar == '=')
					{
						setVerifier(setString.c_str());
						setString = "";
						continue;
					}
					if (isChar == '+' || isChar == '*' || isChar == '{' || isChar == '}' || isChar == '(' || isChar == ')' || (isChar >= '0' && isChar <= '9'))
					{
						setString += isChar;
					}
					else if (isChar != ' ')
					{
						std::cout << "Invalid characters for Set" << std::endl;
					}
				}
			}

			if (isChar == '<')
			{
				inputfile.putback('<');
			}

			//outputFile << "Expression is = " << setVerifier(setString.c_str()) << std::endl;
			if (!setVerifier(setString.c_str()))
			{
				return false;
			}
			break;

		case nonType:
			break;
		}

	}
	return true;
}

int main(int argc, char *argv[])
{
	std::string singleLine = "";
	std::fstream inputFile("input.txt", std::ios_base::in | std::ios_base::binary);


	std::cout << "\nThe following is what the input file contains: \n\n";

	if (inputFile.is_open())
	{
		if (expressionParser(inputFile, nonType, outputFile))
		{
			outputFile << "Expression is valid" << std::endl;
		}
		else
		{
			outputFile << "Expression is invalid" << std::endl;
		}

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