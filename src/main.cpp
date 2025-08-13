// Start of wxWidgets "Hello World" Program

// Logger logger("toDolist", "logger.txt");

#include <iostream>
#include "model/Task.h"

#include <locale>
#include <windows.h>

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));

    return 0;
}
