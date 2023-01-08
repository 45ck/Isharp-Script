#include "VarManager.h"

#include <cstdlib>
#include <stdexcept>

#include "helperclasses.h"

namespace {
    // Helper function for setting console cursor position.
    void SetConsoleCursorPosition(int x, int y) {
        COORD cord;
        cord.X = x;
        cord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
    }
}  

bool VarManager::systemVars(const std::string& name,
    const std::string& content) {
    try {
        size_t t;
        if (content[0] == '"') content = PF::removeQuotes(content);
        if (name == "$using") {
            if (content == "console") {
                usingConsole = true;
            }
            else if (content == "console_Extra") {
                usingConsole = true;
            }
            else if (content == "random") {
                usingRandom = true;
            }
        }
        else if (usingConsole) {
            if (name == "$console_hidden") {
                if (content == "true") {
                    ShowWindow(GetConsoleWindow(), SW_HIDE);
                }
                else if (content == "false") {
                    ShowWindow(GetConsoleWindow(), SW_SHOW);
                }
                else {
                    helperclasses::error("The system variable \"$console_hidden\" does not recognise the value of \"" + content + "\". This variable is a bool (\"true\" or \"false\").");
                }
                return true;
            }
            else if (name == "$console_fontName") {
                fontName = content;
                return true;
            }
            else if (name == "$console_fontSize") {
                fontSize = content;
                return true;
            }
            else if (name == "$console_cursor_pos_x") {
                SetConsoleCursorPosition(std::atoi(content.c_str()), 0);
                return true;
            }
            else if (name == "$console_cursor_pos_y") {
                SetConsoleCursorPosition(0, std::atoi(content.c_str()));
                return true;
            }
            else if (name == "$console_width") {
                console_functions::setConsoleWidth(std::atoi(content.c_str()));
            }
            else if (name == "$console_height") {
                console_functions::setConsoleHeight(std::atoi(content.c_str()));
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    catch (std::exception e) {
        helperclasses::error("A fatal error has occured when trying to set a system variable (name = " + name + ", content = " + content + ").");
        return false;
    }
}

/**
 * Returns the value of the specified system variable. If the variable is not
 * found or is not a system variable, an empty string is returned.
 *
 * @param name The name of the variable.
 * @return The value of the variable, or an empty string if the variable is not
 * found or is not a system variable.
 */
std::string VarManager::getSystemVars(const std::string& name) {
    if (usingConsole) {
        if (name == "$console_hidden") {
            if (IsWindowVisible(GetConsoleWindow()) != FALSE) {
                return "false";
            }
            else {
                return "true";
            }
        }
        else if (name == "$console_fontName") {
            return fontName;
        }
        else if (name == "$console_fontSize") {
            return fontSize;
        }
        else if (name == "$console_cursor_pos_x") {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                return "";
            }
            return std::to_string(csbi.dwCursorPosition.X);
        }
        else if (name == "$console_cursor_pos_y") {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                return "";
            }
            return std::to_string(csbi.dwCursorPosition.Y);
        }
        else if (name == "$console_width") {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                return "";
            }
            return std::to_string(csbi.dwSize.X);
        }
        else if (name == "$console_height") {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                return "";
            }
            return std::to_string(csbi.dwSize.Y);
        }
        else {
            return "";
        }
    }
    else {
        return "";
    }
}

/**
 * Returns the value of the specified variable. If the variable is not found,
 * an error message is printed and an empty string is returned.
 *
 * @param name The name of the variable.
 * @return The value of the variable, or an empty string if the variable is not
 * found.
 */
std::string VarManager::getVar(const std::string& name) {
    std::string systemVar = getSystemVars(name);
    if (!systemVar.empty()) {
        return systemVar;
    }

    if (variables.find(name) == variables.end()) {
        helperclasses::error("The variable \"" + name + "\" does not exist in the current context.");
    }
    else {
        return variables[name];
    }
}

/**
 * Adds a variable with the specified name and value. If a variable with the
 * same name already exists, its value is updated. If the variable is a
 * system variable, it is set and the function returns immediately.
 *
 * @param name The name of the variable.
 * @param content The value of the variable.
 */
void VarManager::addVar(const std::string& name, const std::string& content) {
    if (systemVars(name, content)) {
        return;
    }

    if (variables.find(name) != variables.end()) {
        variables[name] = content;
    }
    else {
        variables.insert(std::make_pair(name, content));
    }
}