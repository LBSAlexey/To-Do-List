#ifndef TASKPANEL_H
#define TASKPANEL_H

#include <wx/panel.h>          // базовый класс wxPanel
#include <wx/listctrl.h>       // wxListCtrl — таблица для отображения задач
#include <wx/sizer.h>          // wxBoxSizer для размещения
#include <wx/string.h>         // wxString (часто используется)
#include "../controller/TaskController.h" // доступ к задачам
#include "../model/Task.h"     // если понадобится доступ к полям Task напрямую


class TaskPanel : public wxPanel {
public:
    TaskPanel(wxWindow* parent, TaskController& controller);
    void RefreshList(); // перерисовывает список задач
    int GetSelectedTaskId() const; // возвращает id выбранной задачи

private:
    TaskController& controller; // ссылка на контроллер
    wxListCtrl* listCtrl = nullptr; // список задач (таблица)

    void InitUI(); // инициализация виджета
    void Populate(); // заполняем список задач
};

#endif //TASKPANEL_H
