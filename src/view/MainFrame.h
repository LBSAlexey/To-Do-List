//
// Created by Лёха on 09.08.2025.
//
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "../controller/TaskController.h"
#include "TaskPanel.h"
#include "TaskDialog.h"


class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    // === Модель ===
    TaskList taskList;
    TaskController controller;
    TaskPanel* taskPanel = nullptr;

    // Методы-обработчики событий
    void OnAddTask(wxCommandEvent& event);
    void OnEditTask(wxCommandEvent& event);
    void OnRemoveTask(wxCommandEvent& event);

    // Метод обновления UI
    void RefreshTaskPanel();

    wxDECLARE_EVENT_TABLE(); // макрос для регистрации событий
};


#endif //MAINFRAME_H
