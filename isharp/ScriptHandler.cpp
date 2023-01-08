#include "stdafx.h"
#include "Parser.h"
#include "Lexor.h"
#include "ScriptHandler.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

ScriptHandler::ScriptHandler() { }
ScriptHandler::~ScriptHandler() { }

void ScriptHandler::runScript(std::vector<std::string> script, std::string argv) {
	// allow console
	WIN32::AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	std::string script_one = "";
	for (const auto& s : script) {
		script_one += trim_functions::trim_copy(s) + '\n';
	}

	Parser parser;
	const auto lexed = lexor.lex(script_one);

	bool print_debug = false;

	if (print_debug) {
		std::cout << " --------------------- " << std::endl;
		std::cout << " LEXOR " << std::endl;
		std::cout << " --------------------- " << std::endl;
		parser.printVector(lexed);
		std::cout << " --------------------- " << std::endl;
		std::cout << " OUTPUT " << std::endl;
		std::cout << " --------------------- " << std::endl;

			std::cout << std::endl << std::endl;
	}

	parser.parse(lexed);
}





