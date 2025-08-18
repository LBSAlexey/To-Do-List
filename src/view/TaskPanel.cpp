//
// Created by Лёха on 09.08.2025.
//

#include "TaskPanel.h"

void TaskPanel::InitUI() {
    listCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    listCtrl->InsertColumn(0, "ID");
    listCtrl->InsertColumn(1, "Задача");
    listCtrl->InsertColumn(2, "Описание");
    listCtrl->InsertColumn(3, "Дата");
    listCtrl->InsertColumn(4, "Конечная дата");
    listCtrl->InsertColumn(5, "Осталось дней");
    listCtrl->InsertColumn(6, "Статус");

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
        listCtrl->SetItem(row, 6, task.getCompleted() ? "Выполнено" : "Не выполнено");
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
