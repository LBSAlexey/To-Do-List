//
// Created by Лёха on 09.08.2025.
//
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "TaskPanel.h"
#include "../model/TaskList.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    // === Модель ===
    TaskList* m_taskList; // указатель на список задач (данные)

    // === View ===
    TaskPanel* m_taskPanel; // панель со списком задач

    // === Методы инициализации ===
    void InitMenuBar();
    void InitToolBar();
    void InitStatusBar();
    void InitTaskPanel();

    // === Обработчики событий ===
    void OnAddTask(wxCommandEvent& event);
    void OnEditTask(wxCommandEvent& event);
    void OnDeleteTask(wxCommandEvent& event);
    void OnSaveTasks(wxCommandEvent& event);
    void OnLoadTasks(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE(); // если используешь старый макросный способ
};


#endif //MAINFRAME_H
