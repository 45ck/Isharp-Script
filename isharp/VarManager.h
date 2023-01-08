#pragma once
#ifndef VAR_MANAGER_H
#define VAR_MANAGER_H

#include <map>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "helperclasses.h"

class VarManager {
public:
	VarManager();
	~VarManager();

	bool usingConsole = false;
	bool usingConsoleExtra = false;
	bool usingRandom = false;

	std::string titleName = "Untilted Mouse Scirpt";
	std::string fontName = "Lucidia Console";
	std::string fontSize = "14";

	std::map<std::string, std::string> variables;
	void addVar(const std::string& name, const std::string& content);
	std::string getVar(const std::string& name);

private:
	bool systemVars(const std::string& name, const std::string& content);
	std::string getSystemVars(const std::string& name);
};

#endif  // VAR_MANAGER_H