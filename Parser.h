#pragma once

#include "Lexer.h"
#include "Node.h"

class Parser
{
public:
	Parser(vector<Token>* _tokens);
	~Parser();
	Node* Run();

private:
	vector<Token>* tokens;
	int CurrentToken;
	void MoveNextToken() { CurrentToken++; }
	Token GetCurrentToken();
	void Match(TokenType type);
	Node* Factor();
	Node* Term();
	Node* Expression();

	vector<Node*> NodeList; // for Memory Release
};

