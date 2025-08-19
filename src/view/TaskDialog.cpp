//
// Created by Лёха on 09.08.2025.
//

#include "TaskDialog.h"

#include <wx/timer.h>

TaskDialog::TaskDialog(wxWindow* parent, const wxString& title, Task* task)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize) {
    InitUI(task);

}

void TaskDialog::InitUI(Task *task) {
    titleCtrl = new wxTextCtrl(this, wxID_ANY);
    descCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    dateCtrl = new wxDatePickerCtrl(this, wxID_ANY);
    //timeCtrl = new wxTimePickerCtrl(this, wxID_ANY);
    completeCheck = new wxCheckBox(this, wxID_ANY, "Status");
    if (task != nullptr) {
        titleCtrl->SetValue(task->getTitle());
        descCtrl->SetValue(task->getDescription());
        dateCtrl->SetValue(task->getDateFinish());
        completeCheck->SetValue(!task->getCompleted());
    }
    // 1. Сетка для меток и полей
    auto* grid = new wxFlexGridSizer(2, 10, 10); // 2 колонки
    grid->Add(new wxStaticText(this, wxID_ANY, "Name:"));
    grid->Add(titleCtrl);
    grid->Add(new wxStaticText(this, wxID_ANY, "Description:"));
    grid->Add(descCtrl);
    grid->Add(new wxStaticText(this, wxID_ANY, "Completion date:"));
    grid->Add(dateCtrl);
    //grid->Add(new wxStaticText(this, wxID_ANY, "Completion time:"));
    //grid->Add(timeCtrl);

    // 2. Общий вертикальный sizer
    auto* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(grid, 0, wxALL | wxEXPAND, 10);
    vbox->Add(completeCheck, 0, wxALL, 10);

    // auto* ok = new wxButton(this, wxID_OK, "ОК");
    // auto* cancel = new wxButton(this, wxID_CANCEL, "Отмена");
    // ok->Bind(wxEVT_BUTTON, &TaskDialog::OnOk, this);
    // cancel->Bind(wxEVT_BUTTON, &TaskDialog::OnCancel, this);

    auto* btnSizer = new wxStdDialogButtonSizer();
    btnSizer->AddButton(new wxButton(this, wxID_OK));
    btnSizer->AddButton(new wxButton(this, wxID_CANCEL));
    btnSizer->Realize();
    vbox->Add(btnSizer, 0, wxALL | wxALIGN_CENTER, 10);

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
        wxMessageBox("Task name cannot be empty");
        return;
    }
    if (date.IsEarlierThan(wxDateTime::Now()) || date.IsEqualTo(wxDateTime::Now())) {
        wxMessageBox("Time cannot be set earlier or at the present time");
        return;
    }
    EndModal(wxID_OK);
}

void TaskDialog::OnCancel(wxCommandEvent &event) {
    EndModal(wxID_CANCEL);
}

