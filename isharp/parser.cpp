#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "helperclasses.h"
#include "Parser.h"
#include "VarManager.h"

/**

splitColinGet
Splits a string at the ':' character and returns either the part before or after the ':' depending on the value of index.
@param token - the string to split
@param index - 0 to return the part before ':', 1 to return the part after ':'
@return - the specified part of the split string
*/
string Parser::splitColinGet(string token, int index) {
	if (token.find(":") == string::npos) return "NULL";
	vector<string> splitColin;
	splitColin.resize(20);
	splitColin = helperclasses::split(token, ':');
	if (index == 1) {
		string return_ = helperclasses::arrayPassArgs(splitColin, 0, ':');
		return return_;
	}
	return splitColin[index];
}

/**

@brief Splits a string by a specified delimiter character and returns the string at a specified index
@param token the string to be split
@param delimeter the character to split the string by
@param index the index of the split string to be returned
@return the string at the specified index after the string has been split
*/
string Parser::split(string token, char delimer, int index) {
	if (token.find(delimer) == string::npos) return "NULL";
	vector<string> splitColin;
	splitColin.resize(20);
	splitColin = helperclasses::split(token, delimer);
	return splitColin[index];
}

/**
Removes the quotes from the start and end of a string
@param toRemove The string to remove the quotes from
@return The string without the quotes
*/
string Parser::removeQuotes(string toRemove) {
	toRemove.erase(0, 1);
	toRemove.erase(toRemove.size() - 1);
	return toRemove;
}

/**

Prints the contents of a vector to the console, with each element separated by a newline.
@param vs The vector to print.
*/
void Parser::printVector(vector<string> vs) {
	for each (string a in vs)
	{
		cout << a << endl;
	}
}

/**
Parses a given list of tokens and executes their corresponding actions.
@param tokens A list of tokens to be parsed and executed.
*/
void Parser::parse(vector<string> tokens) {
	// CODE BEFORE STARTING THE PARSER...
	VarManager varManager = VarManager();

	srand(time(NULL)); // RANDOM FROM CURRENT TIME..

	SetConsoleTitle(varManager.titleName.c_str());

	// END CODE

	string LineNameToGoto = "Main"; // sets the defualt goto as the Main 
	string LastGoto = "Main";
	vector<string> goto_arguments;

	bool lookingForIf = false; // are we looking for a if statement?
	bool ifStatementBool = false; // the actuall value of the statment
	bool ifIsEndOfIf = false;
	bool findingEndIf = false;
	bool findingElse = false;
top: // used for GOTO and functions...

	bool fromThere = false;

	for (int i = 0; i < (int)(tokens.size()); i++) {
		if (!fromThere) {
			if (tokens[i] == "LABEL:" + LineNameToGoto) {
				fromThere = true;
			}
			else if (lookingForIf && (tokens[i] + " " + tokens[i + 1] + " EQUALS " + tokens[i + 3] == LineNameToGoto)) {

				if (ifIsEndOfIf) {
					findingEndIf = true;
				}
				else {
					if (ifStatementBool) {
						fromThere = true;
					}
					else {
						findingElse = true;
					}
				}
			}
			else if (findingEndIf && (tokens[i] == "ENDIF")) {
				lookingForIf = false;
				ifStatementBool = false;
				ifIsEndOfIf = false;
				findingEndIf = false;
				fromThere = true;
			}
			else if (findingElse && (tokens[i] == "ELSE")) {
				fromThere = true;
				findingElse = false;
			}
			continue;
		}

		if (tokens[i] == "NULL") helperclasses::error("An unidentifyed error has occoured..");

		if (tokens[i] == "IF") {
			if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) + " " + splitColinGet(tokens[i + 6], 0) == "IF VAR EQUALS VAR GOTO GODIR GOFUNC" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) + " " + splitColinGet(tokens[i + 6], 0) == "IF VAR EQUALS STRING GOTO GODIR GOFUNC" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) + " " + splitColinGet(tokens[i + 6], 0) == "IF STRING EQUALS VAR GOTO GODIR GOFUNC" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) + " " + splitColinGet(tokens[i + 6], 0) == "IF STRING EQUALS STRING GOTO GODIR GOFUNC" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) + " " + splitColinGet(tokens[i + 6], 0) == "IF INT EQUALS VAR GOTO GODIR GOFUNC" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) + " " + splitColinGet(tokens[i + 6], 0) == "IF VAR EQUALS INT GOTO GODIR GOFUNC" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) + " " + splitColinGet(tokens[i + 6], 0) == "IF INT EQUALS INT GOTO GODIR GOFUNC") {
				// finds the If statement here... If it's else still finds the if statement than finds the next else, 
				// when it's done ether way it goes to the endif.

				string one = "";
				if (splitColinGet(tokens[i + 1], 0) == "VAR") {
					if (varManager.getVar(splitColinGet(tokens[i + 1], 1))[0] == '"') {
						one = removeQuotes(varManager.getVar(splitColinGet(tokens[i + 1], 1)));
					}
					else {
						one = varManager.getVar(splitColinGet(tokens[i + 1], 1));
					}
				}
				else if (splitColinGet(tokens[i + 1], 0) == "STRING") {
					one = removeQuotes(splitColinGet(tokens[i + 1], 1));
				}
				else if (splitColinGet(tokens[i + 1], 0) == "INT") {
					one = splitColinGet(tokens[i + 1], 1);
				}
				else {
					helperclasses::error("The value type \"" + splitColinGet(tokens[i + 1], 0) + "\" is not suitable for an if statement.");
				}


				string two = "";
				if (splitColinGet(tokens[i + 3], 0) == "VAR") {
					if (varManager.getVar(splitColinGet(tokens[i + 3], 1))[0] == '"') {
						two = removeQuotes(varManager.getVar(splitColinGet(tokens[i + 3], 1)));
					}
					else {
						two = varManager.getVar(splitColinGet(tokens[i + 3], 1));
					}
				}
				else if (splitColinGet(tokens[i + 3], 0) == "STRING") {
					two = removeQuotes(splitColinGet(tokens[i + 3], 1));
				}
				else if (splitColinGet(tokens[i + 3], 0) == "INT") {
					two = splitColinGet(tokens[i + 3], 1);
				}
				else {
					helperclasses::error("The value type \"" + splitColinGet(tokens[i + 3], 0) + "\" is not suitable for an if statement.");
				}

				if (one == two) {
					LastGoto = LineNameToGoto;
					LineNameToGoto = splitColinGet(tokens[i + 5], 1);
					//goto_arguments = ;
					vector<string> tempArgs = helperclasses::split(splitColinGet(tokens[i + 6], 1), ',');

					int counter = 0;
					for each (string temp in tempArgs) {
						if (temp[0] == '$') {
							varManager.addVar("$args[" + to_string(counter) + "]", varManager.getVar(temp));
							counter++;
						}
						else {
							varManager.addVar("$args[" + to_string(counter) + "]", temp);
							counter++;
						}
					}

					fromThere = false;
					goto top;
				}
				else {
				}
				i += 5;
			}

			else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) == "IF VAR EQUALS VAR GOTO GODIR" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) == "IF VAR EQUALS STRING GOTO GODIR" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) == "IF STRING EQUALS VAR GOTO GODIR" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) == "IF STRING EQUALS STRING GOTO GODIR" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) == "IF INT EQUALS VAR GOTO GODIR" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) == "IF VAR EQUALS INT GOTO GODIR" ||
				tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " EQUALS " + splitColinGet(tokens[i + 3], 0) + " " + tokens[i + 4] + " " + splitColinGet(tokens[i + 5], 0) == "IF INT EQUALS INT GOTO GODIR") {
				// finds the If statement here... If it's else still finds the if statement than finds the next else, 
				// when it's done ether way it goes to the endif.

				string one = "";
				if (splitColinGet(tokens[i + 1], 0) == "VAR") {
					if (varManager.getVar(splitColinGet(tokens[i + 1], 1))[0] == '"') {
						one = removeQuotes(varManager.getVar(splitColinGet(tokens[i + 1], 1)));
					}
					else {
						one = varManager.getVar(splitColinGet(tokens[i + 1], 1));
					}
				}
				else if (splitColinGet(tokens[i + 1], 0) == "STRING") {
					one = removeQuotes(splitColinGet(tokens[i + 1], 1));
				}
				else if (splitColinGet(tokens[i + 1], 0) == "INT") {
					one = splitColinGet(tokens[i + 1], 1);
				}
				else {
					helperclasses::error("The value type \"" + splitColinGet(tokens[i + 1], 0) + "\" is not suitable for an if statement.");
				}


				string two = "";
				if (splitColinGet(tokens[i + 3], 0) == "VAR") {
					if (varManager.getVar(splitColinGet(tokens[i + 3], 1))[0] == '"') {
						two = removeQuotes(varManager.getVar(splitColinGet(tokens[i + 3], 1)));
					}
					else {
						two = varManager.getVar(splitColinGet(tokens[i + 3], 1));
					}
				}
				else if (splitColinGet(tokens[i + 3], 0) == "STRING") {
					two = removeQuotes(splitColinGet(tokens[i + 3], 1));
				}
				else if (splitColinGet(tokens[i + 3], 0) == "INT") {
					two = splitColinGet(tokens[i + 3], 1);
				}
				else {
					helperclasses::error("The value type \"" + splitColinGet(tokens[i + 3], 0) + "\" is not suitable for an if statement.");
				}

				if (one == two) {
					LastGoto = LineNameToGoto;
					LineNameToGoto = splitColinGet(tokens[i + 5], 1);
					fromThere = false;
					goto top;
					i++;
				}
				else {
				}
				i += 5;
			}
		}

		if (trim_functions::trim_copy(splitColinGet(tokens[i], 0)) == "VAR") {

			if (tokens[i + 1] == "++") {
				int nowInt = atoi(varManager.getVar(splitColinGet(tokens[i], 1)).c_str());
				nowInt++;
				varManager.addVar(splitColinGet(tokens[i], 1), to_string(nowInt));
			}

			if (tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "EQUALS STRING" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "EQUALS INT") {
				string content = splitColinGet(tokens[i + 2], 1);
				varManager.addVar(splitColinGet(tokens[i], 1), content);
				i += 2;
			}
			else if (tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "EQUALS VAR") {
				string s = splitColinGet(tokens[i + 2], 1);
				for (int i = 0; i < s.length(); i++) {
					if (s[i] == ' ') s.erase(i, 1);
				}

				if (s.find("+") == string::npos) {
					string toPrint = varManager.getVar(splitColinGet(tokens[i + 2], 1));
					if (toPrint.find("\"") != string::npos) {
						varManager.addVar(splitColinGet(tokens[i], 1), removeQuotes(varManager.getVar(splitColinGet(tokens[i + 2], 1))));
					}
					else {
						varManager.addVar(splitColinGet(tokens[i], 1), varManager.getVar(splitColinGet(tokens[i + 2], 1)));
					}
					i++;
				}
				else {
					string togther_temp = "";
					vector<string> splitFromPlus = helperclasses::split(s, '+');
					for each (string var in splitFromPlus)
					{
						if (var.find("\"") != string::npos) {
							var = removeQuotes(var);
							togther_temp += var;
						}
						else {
							string var_ = varManager.getVar(var);
							if (var_.find("\"") != string::npos)
								var_ = removeQuotes(var_);
							togther_temp += var_;
							i++;
						}
					}

					if (togther_temp.find("\"") != string::npos) {
						togther_temp = removeQuotes(togther_temp);
					}

					varManager.addVar(splitColinGet(tokens[i], 1), togther_temp);
					i++;
				}
			}
			else if (tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "+EQUALS INT" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "-EQUALS INT" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "*EQUALS INT" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "/EQUALS INT" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "%EQUALS INT") {

				if (tokens[i + 1] == "+EQUALS") {
					//varManager.addVar(splitColinGet(token, 1), splitColinGet(tokens[i + 2], 1));
					int nowInt = atoi(varManager.getVar(splitColinGet(tokens[i], 1)).c_str());
					nowInt += atoi(splitColinGet(tokens[i + 2], 1).c_str());
					varManager.addVar(splitColinGet(tokens[i], 1), to_string(nowInt));
				}
				else if (tokens[i + 1] == "-EQUALS") {
					//varManager.addVar(splitColinGet(token, 1), splitColinGet(tokens[i + 2], 1));
					int nowInt = atoi(varManager.getVar(splitColinGet(tokens[i], 1)).c_str());
					nowInt -= atoi(splitColinGet(tokens[i + 2], 1).c_str());
					varManager.addVar(splitColinGet(tokens[i], 1), to_string(nowInt));
				}
				else if (tokens[i + 1] == "*EQUALS") {
					//varManager.addVar(splitColinGet(token, 1), splitColinGet(tokens[i + 2], 1));
					int nowInt = atoi(varManager.getVar(splitColinGet(tokens[i], 1)).c_str());
					nowInt *= atoi(splitColinGet(tokens[i + 2], 1).c_str());
					varManager.addVar(splitColinGet(tokens[i], 1), to_string(nowInt));
				}
				else if (tokens[i + 1] == "/EQUALS") {
					//varManager.addVar(splitColinGet(token, 1), splitColinGet(tokens[i + 2], 1));
					int nowInt = atoi(varManager.getVar(splitColinGet(tokens[i], 1)).c_str());
					nowInt /= atoi(splitColinGet(tokens[i + 2], 1).c_str());
					varManager.addVar(splitColinGet(tokens[i], 1), to_string(nowInt));
				}
				else if (tokens[i + 1] == "%EQUALS") {
					//varManager.addVar(splitColinGet(token, 1), splitColinGet(tokens[i + 2], 1));
					int nowInt = atoi(varManager.getVar(splitColinGet(tokens[i], 1)).c_str());
					nowInt %= atoi(splitColinGet(tokens[i + 2], 1).c_str());
					varManager.addVar(splitColinGet(tokens[i], 1), to_string(nowInt));
				}
				else {
					helperclasses::error(tokens[i + 1] + " is not a valid equals operator.");
				}
			}

			else if (tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "+EQUALS VAR" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "-EQUALS VAR" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "*EQUALS VAR" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "/EQUALS VAR" ||
				tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "%EQUALS VAR") {

				int nowInt = atoi(varManager.getVar(splitColinGet(tokens[i], 1)).c_str());
				if (tokens[i + 1] == "+EQUALS")
					nowInt += atoi(varManager.getVar(splitColinGet(tokens[i + 2], 1)).c_str());
				else if (tokens[i + 1] == "-EQUALS")
					nowInt -= atoi(varManager.getVar(splitColinGet(tokens[i + 2], 1)).c_str());
				else if (tokens[i + 1] == "*EQUALS")
					nowInt *= atoi(varManager.getVar(splitColinGet(tokens[i + 2], 1)).c_str());
				else if (tokens[i + 1] == "/EQUALS")
					nowInt /= atoi(varManager.getVar(splitColinGet(tokens[i + 2], 1)).c_str());
				else if (tokens[i + 1] == "%EQUALS")
					nowInt %= atoi(varManager.getVar(splitColinGet(tokens[i + 2], 1)).c_str());

				varManager.addVar(splitColinGet(tokens[i], 1), to_string(nowInt));
			}

			else if (tokens[i + 1] + " " + tokens[i + 2] + " " + splitColinGet(tokens[i + 3], 0) == "EQUALS MSGBOX STRING") {
				int selected = MessageBoxA(nullptr, removeQuotes(splitColinGet(tokens[i + 3], 1)).c_str(), "~ Mouse Script Host ~", MB_YESNO);
				string content = "";
				if (selected == 6) { // yes
					content = "yes";
				}
				else if (selected == 7) {
					content = "no";
				}
				else {
					helperclasses::error("The msgbox input \"" + content + "\" is unidentifyable.");
				}
				varManager.addVar(splitColinGet(tokens[i], 1), content);
				i += 2;
			}
			else if (tokens[i + 1] + " " + splitColinGet(tokens[i + 2], 0) == "EQUALS ANY") {
				if (splitColinGet(tokens[i + 2], 1) == "KEYDOWN") {
					string pressed = keys::logger(1);
					varManager.addVar(splitColinGet(tokens[i], 1), pressed);
					i += 2;
				}
				else if (splitColinGet(tokens[i + 2], 1) == "XMOUSEPOS") {
					POINT mouse;
					GetCursorPos(&mouse);
					varManager.addVar(splitColinGet(tokens[i], 1), to_string(mouse.x));
					i += 2;
				}
				else if (splitColinGet(tokens[i + 2], 1) == "YMOUSEPOS") {
					POINT mouse;
					GetCursorPos(&mouse);
					varManager.addVar(splitColinGet(tokens[i], 1), to_string(mouse.y));
					i += 2;
				}
			}

		}


		if (tokens[i] == "RETURN") {
			LineNameToGoto = LastGoto;
			fromThere = false;
			goto top;
			i++;
		}
		else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) + " " + splitColinGet(tokens[i + 2], 0) == "GOTO GODIR GOFUNC") {
			LastGoto = LineNameToGoto;
			LineNameToGoto = splitColinGet(tokens[i + 1], 1);
			//goto_arguments = ;
			vector<string> tempArgs = helperclasses::split(splitColinGet(tokens[i + 2], 1), ',');

			int counter = 0;
			for each (string temp in tempArgs) {
				if (temp[0] == '$') {
					varManager.addVar("$args[" + to_string(counter) + "]", varManager.getVar(temp));
					counter++;
				}
				else {
					varManager.addVar("$args[" + to_string(counter) + "]", temp);
					counter++;
				}
			}

			fromThere = false;
			goto top;
			i++;
		}
		else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "GOTO GODIR") {
			LastGoto = LineNameToGoto;
			LineNameToGoto = splitColinGet(tokens[i + 1], 1);
			fromThere = false;
			goto top;
			i++;
		}

		else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "SLEEP INT") {
			Sleep(atoi(splitColinGet(tokens[i + 1], 1).c_str()));
			i++;
		}
		else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "MSGBOX STRING") {
			MessageBoxA(nullptr, removeQuotes(splitColinGet(tokens[i + 1], 1)).c_str(), "~ Mouse Script Host ~", MB_OK);
			i++;
		}
		else if (splitColinGet(tokens[i], 0) + " " + tokens[i + 1] + " " + tokens[i + 2] + tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "FILEREAD STRING") {
			std::ifstream t(splitColinGet(tokens[i + 1], 1)); // starts if sttream with file name
			string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>()); // read file and allocats memory to str
			varManager.addVar(splitColinGet(tokens[i], 1), str);
			i++;
		}
		else if (tokens[i] == "DEFINE") {
			for each (string ks in tokens)
			{
				ks = helperclasses::ReplaceAll(ks, splitColinGet(tokens[i + 1], 1), tokens[i + 2]);
			}
			i += 2;
		}
		else if (tokens[i] == "EXIT") {
			exit(0);
		}


		if (varManager.usingConsole) {
			if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "PRINT VAR") {
				string s = splitColinGet(tokens[i + 1], 1);
				bool canErese = true;
				for (int i = 0; i < s.length(); i++) {
					if (s[i] == '\"') {
						if (canErese)
							canErese = false;
						else
							canErese = true;
					}

					if (canErese) {
						if (s[i] == ' ') s.erase(i, 1);
					}
					else {
						cout << s[i] << endl;
						// do nothing
					}
				}

				if (s.find("+") == string::npos) {
					string toPrint = varManager.getVar(splitColinGet(tokens[i + 1], 1));
					if (toPrint.find("\"") != string::npos) {
						cout << removeQuotes(varManager.getVar(splitColinGet(tokens[i + 1], 1)));
					}
					else {
						cout << varManager.getVar(splitColinGet(tokens[i + 1], 1));
					}
					i++;
				}
				else {
					string togther_temp = "";
					vector<string> splitFromPlus = helperclasses::split(s, '+');
					for each (string var in splitFromPlus)
					{
						if (var.find("\"") != string::npos) {
							var = removeQuotes(var);
							togther_temp += var;
						}
						else {
							string var_ = varManager.getVar(var);
							if (var_.find("\"") != string::npos)
								var_ = removeQuotes(var_);
							togther_temp += var_;
							i++;
						}
					}

					if (togther_temp.find("\"") != string::npos) {
						togther_temp = removeQuotes(togther_temp);
					}

					cout << togther_temp;
					i++;
				}
			}
			else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "ECHO VAR") {
				string s = splitColinGet(tokens[i + 1], 1);
				bool canErese = true;
				for (int i = 0; i < s.length(); i++) {
					if (s[i] == '\"') {
						if (canErese)
							canErese = false;
						else
							canErese = true;
					}

					if (canErese) {
						if (s[i] == ' ') s.erase(i, 1);
					}
					else {
						cout << s[i] << endl;
						// do nothing
					}
				}

				if (s.find("+") == string::npos) {
					string toPrint = varManager.getVar(splitColinGet(tokens[i + 1], 1));
					if (toPrint.find("\"") != string::npos) {
						cout << removeQuotes(varManager.getVar(splitColinGet(tokens[i + 1], 1))) << endl;
					}
					else {
						cout << varManager.getVar(splitColinGet(tokens[i + 1], 1)) << endl;
					}
					i++;
				}
				else {
					string togther_temp = "";
					vector<string> splitFromPlus = helperclasses::split(s, '+');
					for each (string var in splitFromPlus)
					{
						if (var.find("\"") != string::npos) {
							var = removeQuotes(var);
							togther_temp += var;
						}
						else {
							string var_ = varManager.getVar(var);
							if (var_.find("\"") != string::npos)
								var_ = removeQuotes(var_);
							togther_temp += var_;
							i++;
						}
					}

					if (togther_temp.find("\"") != string::npos) {
						togther_temp = removeQuotes(togther_temp);
					}

					cout << togther_temp << endl;
					i++;
				}
			}
			else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "CMD STRING") {
				system(removeQuotes(splitColinGet(tokens[i + 1], 1)).c_str());
				i++;
			}
			else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "INPUT VAR") {
				string userInput = "";
				std::getline(std::cin, userInput);
				varManager.addVar(splitColinGet(tokens[i + 1], 1), userInput);
			}
			else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "PRINT STRING") {
				cout << removeQuotes(splitColinGet(tokens[i + 1], 1));
				i++;
			}
			else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "ECHO STRING") {
				cout << removeQuotes(splitColinGet(tokens[i + 1], 1)) << endl;;
				i++;
			}
			else if (tokens[i] + " " + splitColinGet(tokens[i + 1], 0) == "PRINT INT") {
				cout << splitColinGet(tokens[i + 1], 1);
				i++;
			}
			else if (splitColinGet(tokens[i], 0) + " " + tokens[i + 1] + " " + tokens[i + 2] == "VAR EQUALS INPUT") {
				string userInput = "";
				std::getline(std::cin, userInput);
				varManager.addVar(splitColinGet(tokens[i], 1), userInput);
				i += 2;
			}
			else if (tokens[i] + " " + tokens[i + 1] == "CONSOLE REFRESH") {
				cout << " HERE " << endl;
				CONSOLE_FONT_INFOEX cfi;
				cfi.cbSize = sizeof(cfi);
				cfi.nFont = 0;
				cfi.dwFontSize.X = 0; // Width of each character in the font
				cfi.dwFontSize.Y = atoi(trim_functions::trim_copy(varManager.fontSize).c_str());// Height
				cfi.FontFamily = FF_DONTCARE;
				cfi.FontWeight = FW_NORMAL;
				string font = trim_functions::trim_copy(varManager.fontSize);
				wstring wideFontName;
				for (int i = 0; i < font.length(); ++i)
					wideFontName += wchar_t(font[i]);

				const wchar_t* fontWChar = wideFontName.c_str();

				std::wcscpy(cfi.FaceName, fontWChar); // Choose your font
				SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &cfi);
			}
			else if (tokens[i] + " " + tokens[i + 1] == "CONSOLE SHOW") {
				ShowWindow(GetConsoleWindow(), SW_SHOW);
			}
			else if (tokens[i] + " " + tokens[i + 1] == "CONSOLE HIDE") {
				ShowWindow(GetConsoleWindow(), SW_HIDE);
			}
			else if (tokens[i] == "CLS") {
				system("cls");
			}
			else if (tokens[i] == "PAUSE") {
				system("pause");
			}
		}

		if (varManager.usingRandom) {
			if (trim_functions::trim_copy(splitColinGet(tokens[i], 0) + " " + tokens[i + 1] + " " + tokens[i + 2]) + " " + splitColinGet(tokens[i + 3], 0) + " " + splitColinGet(tokens[i + 4], 0) == "VAR EQUALS RANDOM INT INT" ||
				trim_functions::trim_copy(splitColinGet(tokens[i], 0) + " " + tokens[i + 1] + " " + tokens[i + 2]) + " " + splitColinGet(tokens[i + 3], 0) + " " + splitColinGet(tokens[i + 4], 0) == "VAR EQUALS RANDOM VAR VAR" ||
				trim_functions::trim_copy(splitColinGet(tokens[i], 0) + " " + tokens[i + 1] + " " + tokens[i + 2]) + " " + splitColinGet(tokens[i + 3], 0) + " " + splitColinGet(tokens[i + 4], 0) == "VAR EQUALS RANDOM VAR INT" ||
				trim_functions::trim_copy(splitColinGet(tokens[i], 0) + " " + tokens[i + 1] + " " + tokens[i + 2]) + " " + splitColinGet(tokens[i + 3], 0) + " " + splitColinGet(tokens[i + 4], 0) == "VAR EQUALS RANDOM INT VAR") {

				string first = "";
				if (splitColinGet(tokens[i + 4], 1).find("$") != string::npos)
					first = varManager.getVar(splitColinGet(tokens[i + 4], 1));
				else
					first = splitColinGet(tokens[i + 4], 1);

				string last = "";
				if (splitColinGet(tokens[i + 3], 1).find("$") != string::npos)
					last = varManager.getVar(splitColinGet(tokens[i + 3], 1));
				else
					last = splitColinGet(tokens[i + 3], 1);

				int random = rand() % atoi(first.c_str()) + atoi(last.c_str());
				varManager.addVar(splitColinGet(tokens[i], 1), to_string(random));
				i += 4;
			}
		}
	}
}


Parser::Parser()
{
}


Parser::~Parser()
{
}
