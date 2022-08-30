#include "Parser.h"
#include <iostream>


/* EBNF
factor = ( [ "+" | "-" ], integer ) | ( "(", expression, ")" )
term = factor, { "*" | "/", factor }
expression = term, { "+" | "-", term }
*/


int NodeNumber = 0;

Parser::Parser(vector<Token>* _tokens)
{
	tokens = _tokens;
	CurrentToken = 0;
}
Parser::~Parser()
{
	for (auto v = NodeList.begin(); v != NodeList.end(); v++)
	{
		(*v)->Release();
	}
}

Node* Parser::Run()
{
	return Expression();
}


Node* Parser::Factor()
{
	Token token = GetCurrentToken();
	MoveNextToken();

	switch (token.type)
	{
	case TokenType::Plus:
	case TokenType::Minus:
	{
		Token integerToken = GetCurrentToken();
		Match(TokenType::Integer);
		if (token.type == TokenType::Minus) integerToken.integer = -integerToken.integer;
		Node* node = (Node*)(new IntegerNode(integerToken));
		NodeList.push_back(node);
		return node;
	}
	case TokenType::Integer:
	{

		Node* node = (Node*)(new IntegerNode(token));
		NodeList.push_back(node);
		return node;
	}
	case TokenType::LeftParens:
	{
		Node* node = Expression();
		Match(TokenType::RightParens);
		return node;
	}
	}

	return NULL;
}


Node* Parser::Term()
{
	Node* leftNode = Factor();
	Token token = GetCurrentToken();
	while (token.type == TokenType::Mul || token.type == TokenType::Div)
	{
		MoveNextToken();
		leftNode = (Node*)(new BinaryNode(leftNode, token, Factor()));
		NodeList.push_back(leftNode);
		token = GetCurrentToken();
	}
	return leftNode;
}

Node* Parser::Expression()
{
	Node* leftNode = Term();
	Token token = GetCurrentToken();
	while (token.type == TokenType::Plus || token.type == TokenType::Minus)
	{
		MoveNextToken();
		leftNode = (Node*)(new BinaryNode(leftNode, token, Term()));
		NodeList.push_back(leftNode);
		token = GetCurrentToken();
	}
	return leftNode;
}

Token Parser::GetCurrentToken() {

	if (CurrentToken < tokens->size())
		return tokens->at(CurrentToken);

	Token token;
	token.integer = 0;
	token.type = TokenType::EndToken;
	return token;
};

void Parser::Match(TokenType type)
{
	if (GetCurrentToken().type != type) {
		std::cout << "Interpreter Match Error\n";
	}
	MoveNextToken();
}