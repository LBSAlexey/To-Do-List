//
// Created by Лёха on 09.08.2025.
//

#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title), controller(taskList) {
    wxWindow::SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial Unicode MS"));
    InitUI();
    LoadTasksFromFile();
}

void MainFrame::InitUI() {

    taskPanel = new TaskPanel(this, controller);

    auto* addBtn = new wxButton(this, ID_ADD, "Add task");
    auto* editBtn = new wxButton(this, ID_EDIT, "Edit task");
    auto* removeBtn = new wxButton(this, ID_REMOVE, "Remove task");

    auto* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addBtn, 0, wxALL, 5);
    buttonSizer->Add(editBtn, 0, wxALL, 5);
    buttonSizer->Add(removeBtn, 0, wxALL, 5);

    auto* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_LEFT);
    mainSizer->Add(taskPanel, 1, wxEXPAND | wxALL, 5);

    addBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAddTask, this);
    editBtn->Bind(wxEVT_BUTTON, &MainFrame::OnEditTask, this);
    removeBtn->Bind(wxEVT_BUTTON, &MainFrame::OnRemoveTask, this);

    SetSizer(mainSizer);
    Layout();
    CreateStatusBar();

}

void MainFrame::OnAddTask(wxCommandEvent& event) {
    TaskDialog dlg(this, "Add task");

    if (dlg.ShowModal() == wxID_OK) {
        wxString title = dlg.GetTitleValue();
        wxString desc = dlg.GetDescriptionValue();
        wxDateTime date = dlg.GetDateValue();
        bool complete = dlg.GetCompletedValue();

        try {
            controller.addTask(title.ToStdString(), desc.ToStdString(), date, complete);
            taskPanel->RefreshList(); // обновляем интерфейс
            SaveTasksToFile();
        } catch (const std::exception& e) {
            wxMessageBox(e.what(), "error", wxICON_ERROR);
        }
    }
}

void MainFrame::OnEditTask(wxCommandEvent& event) {
    int id = taskPanel->GetSelectedTaskId();
    if (id < 0) {
        wxMessageBox("First, select a task", "error", wxICON_WARNING);
        return;
    }

    Task* task = controller.getTask(id);
    if (!task) {
        wxMessageBox("Task not found", "error", wxICON_ERROR);
        return;
    }

    TaskDialog dlg(this, "Edit task", task);
    if (dlg.ShowModal() == wxID_OK) {
        try {
            controller.editTask(
                id,
                dlg.GetTitleValue().ToStdString(),
                dlg.GetDescriptionValue().ToStdString(),
                dlg.GetDateValue(),
                dlg.GetCompletedValue()
            );
            taskPanel->RefreshList();
        } catch (const std::exception& e) {
            wxMessageBox(e.what(), "error", wxICON_ERROR);
        }
    }
}


void MainFrame::OnRemoveTask(wxCommandEvent& event) {
    int id = taskPanel->GetSelectedTaskId();
    if (id < 0) {
        wxMessageBox("Select task", "error", wxICON_WARNING);
        return;
    }

    int answer = wxMessageBox("Sure", "Confirmation", wxYES_NO | wxICON_QUESTION);
    if (answer == wxYES) {
        try {
            controller.removeTask(id);
            taskPanel->RefreshList();
        } catch (const std::exception& e) {
            wxMessageBox(e.what(), "Error while deleting", wxICON_ERROR);
        }
    }
}



void MainFrame::LoadTasksFromFile() {
    wxString defaultDir = wxStandardPaths::Get().GetDocumentsDir();
    wxString defaultFile = defaultDir + wxFILE_SEP_PATH + "tasks.json";

    try {
        controller.loadTaskFromFile(defaultFile.ToStdString());
        taskPanel->RefreshList();
        SetStatusText("Задачи успешно загружены из " + defaultFile);
    } catch (const std::exception& e) {
        // Если файла нет, это нормально - просто начнем с пустого списка
        SetStatusText("Не удалось загрузить задачи: " + wxString(e.what()));
    }
}

void MainFrame::SaveTasksToFile() {
    wxString defaultDir = wxStandardPaths::Get().GetDocumentsDir();
    wxString defaultFile = defaultDir + wxFILE_SEP_PATH + "tasks.json";

    try {
        controller.saveTaskToFile(defaultFile.ToStdString());
        SetStatusText("Задачи успешно сохранены в " + defaultFile);
    } catch (const std::exception& e) {
        wxMessageBox("Ошибка при сохранении задач: " + wxString(e.what()),
                    "Ошибка", wxOK | wxICON_ERROR);
    }
}
