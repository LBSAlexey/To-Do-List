// Start of wxWidgets "Hello World" Program

// Logger logger("toDolist", "logger.txt");

#include <iostream>
#include "model/Task.h"

#include <locale>
#include <windows.h>

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));

    wxDateTime now = wxDateTime::Now();
    wxDateTime tomorrow = now + wxDateSpan::Days(1);
    wxDateTime yesterday = now - wxDateSpan::Days(1);

    // 1. Создание задачи на завтра
    Task task1("Купить молоко", "Зайти в магазин и купить молоко", tomorrow);
    std::cout << "Задача: " << task1.getTitle() << "\n";
    std::cout << "Описание: " << task1.getDescription() << "\n";
    std::cout << "Просрочена? " << (task1.IsOverdue() ? "Да" : "Нет") << "\n";
    std::cout << "Осталось времени: " << task1.TimeRemaining().GetHours() << " часов\n\n";

    // 2. Задача с дедлайном в прошлом
    Task task2("Сдать проект", "Дедлайн был вчера", yesterday);
    std::cout << "Задача: " << task2.getTitle() << "\n";
    std::cout << "Просрочена? " << (task2.IsOverdue() ? "Да" : "Нет") << "\n";
    std::cout << "Осталось времени: " << task2.TimeRemaining().GetHours() << " часов\n\n";

    // 3. Тест setDateFinish (попробуем поставить дату в прошлом)
    if (!task1.setDateFinish(yesterday)) {
        std::cout << "Нельзя поставить дедлайн в прошлом!\n";
    }

    return 0;
}
