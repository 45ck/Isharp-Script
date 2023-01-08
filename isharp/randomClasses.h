#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <algorithm> 
#include <cctype>
#include <ctime>
#include <random>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
using namespace std;

#include "stdafx.h"


class stackoverflowclasses
{
public:
	stackoverflowclasses();
	~stackoverflowclasses();

	static vector<string> &split(const string &s, char delim, vector<string> &elems) {
		stringstream ss(s);
		string item;
		while (getline(ss, item, delim)) {
			if (item.length() > 0) {
				elems.push_back(item);
			}
		}
		return elems;
	}

	static vector<string> split(const string &s, char delim) {
		vector<string> elems;
		split(s, delim, elems);
		return elems;
	}

	static string ReplaceAll(string str, const string& from, const string& to) {
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}
		return str;
	}

	static string arrayPassArgs(vector<string> args, int pass = 0, char passChar = ' ') {
		string toProduce = "";
		int max = pass;
		int counter = 0;
		for each (string s in args)
		{
			if (counter > max) {
				toProduce += args[counter] + passChar;
			}
			counter++;
		}
		return removeLastCharacter(toProduce);
	}

	static string removeLastCharacter(string str) {
		return str.substr(0, str.length() - 1);;
	}

	static bool contains(string s, string contain) {
		if (s.find(contain) != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}

	static int random(int low, int high) {
		if (low > high) return high;
		return low + (std::rand() % (high - low + 1));
	}

	void eraseSubStr(std::string & mainStr, const std::string & toErase)
	{
		// Search for the substring in string
		size_t pos = mainStr.find(toErase);

		if (pos != std::string::npos)
		{
			// If found then erase it from string
			mainStr.erase(pos, toErase.length());
		}
	}

	void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
	{
		size_t pos = std::string::npos;

		// Search for the substring in string in a loop untill nothing is found
		while ((pos = mainStr.find(toErase)) != std::string::npos)
		{
			// If found then erase it from string
			mainStr.erase(pos, toErase.length());
		}
	}

	//http://blog.mrroa.com/2013/06/06/tiptrick-how-to-retrieve-a-sub-string-between-two-delimiters-using-c/

	static std::string ExtractString(std::string source, std::string start, std::string end)
	{
		std::size_t startIndex = source.find(start);

		// Adding the length of the delimiter to our starting index
		// this will move us to the beginning of our sub-string.
		//
		startIndex += start.length();

		// Looking for the end delimiter
		//
		std::string::size_type endIndex = source.find(end, startIndex);

		// Returning the substring between the start index and
		// the end index. If the endindex is invalid then the
		// returned value is empty string
		return source.substr(startIndex, endIndex - startIndex);
	}


	static std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

	static LPWSTR s2lp(string stzr) {
		string meme = stzr;
		const char* text = meme.c_str();
		wchar_t wstr[256];
		mbstowcs(wstr, text, strlen(text) + 1);//Plus null
		LPWSTR ptr = wstr;
		return ptr;
	}

	static void Send(const TCHAR *CharacterString, HWND hKeepActive)
	{
		TCHAR cChar, FiLoBuffer[32];
		INPUT Input = { 0 };
		KEYBDINPUT kb = { 0 };
		int iModifiers = 0;
		int iUpDown = 0;
		BOOL bNoMoreModifier;

		cChar = *CharacterString;
		BlockInput(TRUE);
		while ((cChar))
		{
			if (hKeepActive != NULL)
			{
				if (IsIconic(hKeepActive)) ShowWindow(hKeepActive, SW_RESTORE);
				if (hKeepActive != GetForegroundWindow()) SetForegroundWindow(hKeepActive);
			}
			ZeroMemory(&kb, sizeof(KEYBDINPUT));
			bNoMoreModifier = FALSE;
			switch (cChar)
			{
			case '!':
				kb.wVk = VK_MENU;
				FiLoBuffer[iModifiers++] = VK_MENU;
				break;
			case '+':
				kb.wVk = VK_SHIFT;
				FiLoBuffer[iModifiers++] = VK_SHIFT;
				break;
			case '^':
				kb.wVk = VK_CONTROL;
				FiLoBuffer[iModifiers++] = VK_CONTROL;
				break;
			case '#':
				kb.wVk = VK_RWIN;
				FiLoBuffer[iModifiers++] = VK_RWIN;
				break;
			default:
				bNoMoreModifier = TRUE;
				break;
			}

			if ((iModifiers > 0) && bNoMoreModifier) //First char after modifierer
			{
				if ((cChar > 0x60) && (cChar < 0x7b))
					kb.wVk = cChar - 0x20;
				else
					kb.wVk = cChar;

				kb.wScan = 0;
			}
			else if (iModifiers > 0)
			{
				kb.wScan = 0;
			}
			else
			{
				kb.wVk = 0;
				kb.wScan = cChar;
			}
			kb.dwFlags = KEYEVENTF_UNICODE;
			Input.type = INPUT_KEYBOARD;
			Input.ki = kb;
			SendInput(1, &Input, sizeof(Input));

			if ((iModifiers == 0) || (bNoMoreModifier))
			{
				if (iModifiers != 0)
				{
					if ((cChar > 0x60) && (cChar < 0x7b))
						kb.wVk = cChar - 0x20;
					else
						kb.wVk = cChar;
					kb.wScan = 0;
				}
				else
				{
					kb.wVk = 0;
					kb.wScan = cChar;
				}
				kb.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
				Input.type = INPUT_KEYBOARD;
				Input.ki = kb;
				SendInput(1, &Input, sizeof(Input));
			}

			if ((bNoMoreModifier || (CharacterString[1] == NULL)) && (iModifiers > 0))
			{
				for (int i = iModifiers - 1; i >= 0; i--)
				{
					kb.wVk = FiLoBuffer[i];
					kb.wScan = 0;
					kb.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
					Input.type = INPUT_KEYBOARD;
					Input.ki = kb;
					SendInput(1, &Input, sizeof(Input));
					FiLoBuffer[i] = 0;
				}
				iModifiers = 0;
			}

			cChar = *++CharacterString;
		}
		BlockInput(FALSE);
	}

	/*,,  0 = down & up, 1 = down , 2 = up,,  */
	static void SendVK(WORD vk, HWND hKeepActive, int iUpDown)
	{
		INPUT Input = { 0 };
		KEYBDINPUT kb = { 0 };

		if (hKeepActive != NULL)
		{
			if (IsIconic(hKeepActive)) ShowWindow(hKeepActive, SW_RESTORE);
			if (hKeepActive != GetForegroundWindow()) SetForegroundWindow(hKeepActive);
		}

		if ((iUpDown == 0) || (iUpDown == 1))
		{
			kb.wVk = vk;
			kb.wScan = 0;
			kb.dwFlags = KEYEVENTF_UNICODE;
			Input.type = INPUT_KEYBOARD;
			Input.ki = kb;
			SendInput(1, &Input, sizeof(Input));
		}

		if ((iUpDown == 0) || (iUpDown == 2))
		{
			kb.wVk = vk;
			kb.wScan = 0;
			kb.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
			Input.type = INPUT_KEYBOARD;
			Input.ki = kb;
			SendInput(1, &Input, sizeof(Input));
		}
	}

	static char pressanykey(const char *prompt)
	{
		DWORD  mode;
		HANDLE hstdin;
		INPUT_RECORD inrec;
		DWORD  count;
		char default_prompt[] = "Press the 'any' key...";
		char result = '\0';

		/* Set the console mode to no-echo, raw input, */
		/* and no window or mouse events.,,,,  */
		hstdin = GetStdHandle(STD_INPUT_HANDLE);
		if (hstdin == INVALID_HANDLE_VALUE
			|| !GetConsoleMode(hstdin, &mode)
			|| !SetConsoleMode(hstdin, 0))
			return result;

		if (!prompt) prompt = default_prompt;

		/* Instruct the user */
		WriteConsole(
			GetStdHandle(STD_OUTPUT_HANDLE),
			prompt,
			lstrlen(prompt),
			&count,
			NULL
		);

		FlushConsoleInputBuffer(hstdin);

		/* Wait for and get a single key PRESS */
		do ReadConsoleInput(hstdin, &inrec, 1, &count);
		while ((inrec.EventType != KEY_EVENT) || !inrec.Event.KeyEvent.bKeyDown);

		/* Remember which key the user pressed */
		result = inrec.Event.KeyEvent.uChar.AsciiChar;

		/* Wait for and get a single key RELEASE */
		do ReadConsoleInput(hstdin, &inrec, 1, &count);
		while ((inrec.EventType != KEY_EVENT) || inrec.Event.KeyEvent.bKeyDown);

		/* Restore the original console mode */
		SetConsoleMode(hstdin, mode);

		return result;
	}

	static std::string execute(std::string cmd) // GETS THE CMD OUTPUT...
	{
		std::string file_name = "temp.mscriptdata";
		std::system((cmd + " > " + file_name).c_str()); // redirect output to file

														// open file for input, return string containing characters in the file
		std::ifstream file(file_name);
		return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
	}

	static std::string encrypt(std::string msg, std::string key)
	{
		// Make sure the key is at least as long as the message
		std::string tmp(key);
		while (key.size() < msg.size())
			key += tmp;

		// And now for the encryption part
		for (std::string::size_type i = 0; i < msg.size(); ++i)
			msg[i] ^= key[i];
		return msg;
	}
	static std::string decrypt(std::string msg, std::string key)
	{
		return encrypt(msg, key); // lol
	}

	static std::string wstrtostr(const std::wstring &wstr)
	{
		std::string strTo;
		char *szTo = new char[wstr.length() + 1];
		szTo[wstr.size()] = '\0';
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL);
		strTo = szTo;
		delete[] szTo;
		return strTo;
	}

	static string getBetwwen(string first, string last, string str) { // MADE BY YA BOI MRCK10 (meh)
		unsigned first_braket = str.find(first); // find the left braket
		unsigned last_braket = str.find(last); // find the right braket
		return str.substr(first_braket, last_braket - first_braket).erase(0, 1); // get the value between the brakets and remove the '(' thats leftover..
	}

	static string ToLower(string str) {
		for (unsigned int i = 0; i < str.length(); ++i) {
			str = tolower(str[i]);
		}
		return str;
	}


};


class express {
public:
	const char * expressionToParse = "3*2+4*1+(4+9)*6";

	char peek()
	{
		return *expressionToParse;
	}

	char get()
	{
		return *expressionToParse++;
	}

	int number()
	{
		int result = get() - '0';
		while (peek() >= '0' && peek() <= '9')
		{
			result = 10 * result + get() - '0';
		}
		return result;
	}

	int factor()
	{
		if (peek() >= '0' && peek() <= '9')
			return number();
		else if (peek() == '(')
		{
			get(); // '('
			int result = expression();
			get(); // ')'
			return result;
		}
		else if (peek() == '-')
		{
			get();
			return -factor();
		}
		return 0; // error
	}

	int term()
	{
		int result = factor();
		while (peek() == '*' || peek() == '/')
			if (get() == '*')
				result *= factor();
			else
				result /= factor();
		return result;
	}

	int expression()
	{
		int result = term();
		while (peek() == '+' || peek() == '-')
			if (get() == '+')
				result += term();
			else
				result -= term();
		return result;
	}

};