#include <iostream>
#include "model/TaskList.h"

int main() {
    TaskList list;

    // Добавляем задачи
    list.AddTask("Купить хлеб", "Сходить в магазин", wxDateTime::Now() + wxDateSpan::Days(1), false);
    list.AddTask("Написать код", "Доделать проект", wxDateTime::Now() + wxDateSpan::Days(3), false);

    // Сохраняем
    list.saveToJson("tasks.json");

    // Загружаем
    TaskList loaded;
    loaded.loadFromJson("tasks.json");

    // Проверяем вывод
    for (const auto& [id, task] : loaded.getTasks()) {
        std::cout << id << ": " << task.getTitle() << " - "
                  << (task.getCompleted() ? "Выполнено" : "Не выполнено") << "\n";
    }

    return 0;
}
