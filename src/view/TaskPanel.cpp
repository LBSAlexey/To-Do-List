//
// Created by Лёха on 09.08.2025.
//

#include "TaskPanel.h"
#include <wx/msgdlg.h>
#include <../src/model/Task.h>


TaskPanel::TaskPanel(wxWindow* parent, TaskController& controller)
    : wxPanel(parent), controller(controller) {
    InitUI();
}

void TaskPanel::InitUI() {

    listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    listCtrl->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial"));

    listCtrl->InsertColumn(0, "ID");
    listCtrl->InsertColumn(1, "Task");
    listCtrl->InsertColumn(2, "Description");
    listCtrl->InsertColumn(3, "Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE+ 150);
    listCtrl->InsertColumn(4, "End date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE+ 150);
    listCtrl->InsertColumn(5, "Days left", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE+ 150);
    listCtrl->InsertColumn(6, "Status");

    wxBoxSizer *tasksSizer = new wxBoxSizer(wxVERTICAL);
    tasksSizer->Add(listCtrl, 1, wxALL | wxEXPAND, 5);
    SetSizer(tasksSizer);
    Layout();
}

void TaskPanel::Populate() {
    listCtrl->DeleteAllItems();

    try {
        for (const auto& [id, task] : controller.getAllTasks()) {
            if (!task.isValid()) {
                continue;
            }

            int row = listCtrl->GetItemCount();
            row = listCtrl->InsertItem(row, wxString::Format("%d", id));
            listCtrl->SetItem(row, 0, wxString::Format("%d", task.getId()));
            listCtrl->SetItem(row, 1, task.getTitle());
            listCtrl->SetItem(row, 2, task.getDescription());

            // Форматируем даты для отображения с временем
            wxString startDate = task.getDateNow().IsValid() ?
                task.getDateNow().Format("%Y-%m-%d %H:%M") : "Invalid Date";

            wxString finishDate = task.getDateFinish().IsValid() ?
                task.getDateFinish().Format("%Y-%m-%d %H:%M") : "Invalid Date";

            listCtrl->SetItem(row, 3, startDate);
            listCtrl->SetItem(row, 4, finishDate);

            // Рассчитываем оставшееся время
            wxString timeRemaining;
            if (task.getDateFinish().IsValid() && wxDateTime::Now().IsValid()) {
                wxTimeSpan remaining = task.TimeRemaining();

                if (remaining.IsNegative()) {
                    timeRemaining = "Overdue";
                } else {
                    int days = remaining.GetDays();
                    int hours = remaining.GetHours() % 24;
                    int minutes = remaining.GetMinutes() % 60;

                    timeRemaining = wxString::Format("%d days, %02d:%02d", days, hours, minutes);
                }
            } else {
                timeRemaining = "N/A";
            }

            listCtrl->SetItem(row, 5, timeRemaining);
            listCtrl->SetItem(row, 6, task.getCompleted() ? "Done" : "Not done");
        }
    } catch (const std::exception& e) {
        wxMessageBox("Error loading tasks: " + wxString(e.what()), "Error", wxOK | wxICON_ERROR);
    }
}


void TaskPanel::RefreshList() {
    Populate();
}

int TaskPanel::GetSelectedTaskId() const {
    long itemIndex = listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex != -1) {
        return wxAtoi(listCtrl->GetItemText(itemIndex));
    }
    return -1; // ничего не выбрано

}
