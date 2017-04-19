// InfixToPostfix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#define MAX 100

struct stack {
	char items[MAX];
	int top;
};

void push(stack *s, char key) {
	s->items[++s->top] = key;
}

char pop(stack *s) {
	return s->items[s->top--];
}

char peek(stack *s) {
	return s->items[s->top];
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


bool isOperator(char key) {
	if (key == '+' || key == '-' || key == '*' || key == '^') {
		return true;
	}
	else return false;
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

bool orderCheck(char key1, char key2) {
	if (checkPrecedence(key1) < checkPrecedence(key2)) {
		return true;
	}
	else return false;
}

void infixToPostfix(char *str) {
	stack s;
	startStack(&s);
	char *out = (char *) malloc(strlen(str));
	char *outp = out;

	while (*str != '\0') {
		// case 1: if '(' push to stack
		if (*str == '(') push(&s, '(');
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
}

int main()
{
	std::string buf("2*3+1"); // input
	infixToPostfix(cstr);
    return 0;
}

