#pragma once
#include <iostream>
#include "Lexer.h"

class Node
{
public:
	virtual long Visit() = 0;
	virtual void Release() = 0;
};

class BinaryNode : Node
{
public:

	Node* Left;
	Token Operator;
	Node* Right;

	BinaryNode(Node* _Left, Token _Operator, Node* _Right)
	{
		Left = _Left;
		Operator = _Operator;
		Right = _Right;
	}

	long Visit()
	{
	//	std::cout << "BinaryNode Begin" << endl;

		long leftValue = Left->Visit();
		long rightValue = Right->Visit();

		/*
		std::cout << "BinaryNode " << to_string(leftValue);
		switch (Operator.type)
		{
		case TokenType::Plus: std::cout << "+"; break;
		case TokenType::Minus: std::cout << "-"; break;
		case TokenType::Mul: std::cout << "*"; break;
		case TokenType::Div: std::cout << "/"; break;
		}

		std::cout << to_string(rightValue) << endl;*/


	//	std::cout << "BinaryNode End" << endl;

		switch (Operator.type)
		{
		case TokenType::Plus: return leftValue + rightValue;
		case TokenType::Minus: return leftValue - rightValue;
		case TokenType::Mul: return leftValue * rightValue;
		case TokenType::Div:
			if (rightValue == 0)
			{

			}
			return leftValue / rightValue;
		}

		
		return 0;
	}

	void Release() {
		delete this;
	}
};

class IntegerNode : Node
{
public:

	Token Integer;

	IntegerNode(Token integerToken)
	{
		Integer = integerToken;
	}

	long Visit() { 
	//	std::cout << "IntegerNode (" << to_string(Integer.integer) << ")" << endl;
		return Integer.integer;
	}
	void Release() {
		delete this;
	}
};