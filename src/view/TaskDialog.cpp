//
// Created by Лёха on 09.08.2025.
//

#include "TaskDialog.h"


void TaskDialog::InitUI(Task *task) {
    titleCtrl = new wxTextCtrl(this, wxID_ANY);
    descCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    dateCtrl = new wxDatePickerCtrl(this, wxID_ANY);
    completeCheck = new wxCheckBox(this, wxID_ANY, "Статус");
    if (task != nullptr) {
        titleCtrl->SetValue(task->getTitle());
        descCtrl->SetValue(task->getDescription());
        dateCtrl->SetValue(task->getDateFinish());
        completeCheck->SetValue(task->getCompleted());
    }
    // 1. Сетка для меток и полей
    auto* grid = new wxFlexGridSizer(2, 10, 10); // 2 колонки
    grid->Add(titleCtrl);
    grid->Add(descCtrl);
    grid->Add(dateCtrl);

    // 2. Общий вертикальный sizer
    auto* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(grid, 0, wxALL | wxEXPAND, 10);
    vbox->Add(completeCheck, 0, wxALL, 10);

    auto* ok = new wxButton(this, wxID_OK, "ОК");
    auto* cancel = new wxButton(this, wxID_CANCEL, "Отмена");

    vbox->Add(ok, 0, wxALL, 10);
    vbox->Add(cancel, 0, wxALL, 10);

    SetSizerAndFit(vbox);
    Layout();
    Centre(); // по центру экрана
}

wxString TaskDialog::GetTitleValue() const {
    return titleCtrl->GetValue();
}

wxString TaskDialog::GetDescriptionValue() const {
    return descCtrl->GetValue();
}

wxDateTime TaskDialog::GetDateValue() const {
    return dateCtrl->GetValue();
}

bool TaskDialog::GetCompletedValue() const {
    return completeCheck->GetValue();
}

void TaskDialog::OnOk(wxCommandEvent &event) {
    wxString title = titleCtrl->GetValue();
    wxDateTime date = dateCtrl->GetValue();
    if (title.empty()) {
        wxMessageBox("Название задачи не может быть пустым");
        return;
    }
    if (date.IsEarlierThan(wxDateTime::Now()) || date.IsEqualTo(wxDateTime::Now())) {
        wxMessageBox("Время не может выставлено ранее или в настоящее время");
        return;
    }
    EndModal(wxID_OK);
}

void TaskDialog::OnCancel(wxCommandEvent &event) {
    EndModal(wxID_CANCEL);
}

