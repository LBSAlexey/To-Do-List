//
// Created by Лёха on 09.08.2025.
//

#include "TaskPanel.h"

#include <wx/msgdlg.h>

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
    listCtrl->InsertColumn(3, "Date", wxLIST_FORMAT_LEFT, wxLIST_AUTOSIZE+ 200);
    listCtrl->InsertColumn(4, "End date");
    listCtrl->InsertColumn(5, "Days left");
    listCtrl->InsertColumn(6, "Status");

    wxBoxSizer *tasksSizer = new wxBoxSizer(wxVERTICAL);
    tasksSizer->Add(listCtrl, 1, wxALL | wxEXPAND, 5);
    SetSizer(tasksSizer);
    Layout();
}

void TaskPanel::Populate() {
    listCtrl->DeleteAllItems();

    for (const auto& [id, task] : controller.getAllTasks()) {
        int row = listCtrl->GetItemCount();
        row = listCtrl->InsertItem(row, wxString::Format("%d", id));
        listCtrl->SetItem(row, 0, wxString::Format("%d", task.getId()));
        listCtrl->SetItem(row, 1, task.getTitle());
        listCtrl->SetItem(row, 2, task.getDescription());
        listCtrl->SetItem(row, 3, task.getDateNow().FormatISOCombined(' '));
        listCtrl->SetItem(row, 4, task.getDateFinish().FormatISOCombined(' '));
        listCtrl->SetItem(row, 5, task.TimeRemaining().Format("Day: %D; Time: %H:%M:%S"));
        listCtrl->SetItem(row, 6, task.getCompleted() ? "Done" : "Not done");
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
