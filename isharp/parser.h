#pragma once
#include "stdafx.h"
#include <iostream>
#include "variableHelper.h"
using namespace std;

class Parser
{

public:
	Parser();
	~Parser();

	void parse(vector<string> tokens);

	static std::string splitColinGet(std::string token, int index);

	static std::string split(std::string token, char delimer, int index);

	static std::string removeQuotes(std::string toRemove);

	static void printVector(std::vector<std::string> vs);
};

