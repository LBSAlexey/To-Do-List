#include <iostream>
#include "model/Task.h"
#include "controller/TaskController.h"

#include <locale>
#include <windows.h>

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));
    TaskList list;
    TaskController controller(list);

    // 1. Добавление корректной задачи
    wxDateTime due = wxDateTime::Now() + wxDateSpan::Days(1);
    try {
        controller.addTask("Протестировать контроллер", "Создание, редактирование, удаление", due, false);
        // assert(list.getTasks().size() == 1);
        std::cout << "✅ addTask (валидный) прошёл\n";
    } catch (...) {
        std::cerr << "❌ addTask (валидный) вызвал исключение\n";
    }

    // Получаем id добавленной задачи
    int id = list.getTasks().begin()->first;

    // 2. Попытка добавить задачу с пустым заголовком
    try {
        controller.addTask("", "описание", due, false);
        std::cerr << "❌ addTask (пустой заголовок) не выбросил исключение\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ addTask (пустой заголовок) выбросил: " << e.what() << "\n";
    }

    // 3. Получение задачи по id
    Task* task = controller.getTask(id);
    assert(task != nullptr);
    assert(task->getTitle() == "Протестировать контроллер");
    std::cout << "✅ getTask работает\n";

    // 4. Редактирование задачи
    wxDateTime newDue = wxDateTime::Now() + wxDateSpan::Days(2);
    controller.editTask(id, "Новый заголовок", "Новое описание", newDue, true);
    Task* updated = controller.getTask(id);
    assert(updated->getTitle() == "Новый заголовок");
    assert(updated->getCompleted() == true);
    std::cout << "✅ editTask работает\n";

    // 5. Удаление задачи
    controller.removeTask(id);
    assert(controller.getTask(id) == nullptr);
    std::cout << "✅ removeTask работает\n";

    // 6. Сохранение и загрузка
    controller.addTask("Задача для сохранения", "Будет сохранена", due, false);
    controller.saveTaskToFile("test_tasks.json");

    TaskList newList;
    TaskController newController(newList);
    newController.loadTaskFromFile("test_tasks.json");
    assert(newList.getTasks().size() == 1);
    std::cout << "✅ save/load работает\n";

    std::cout << "✅ Все тесты прошли\n";
    return 0;
}
