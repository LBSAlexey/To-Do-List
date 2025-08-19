#include "TaskDialog.h"

TaskDialog::TaskDialog(wxWindow* parent, const wxString& title, Task* task)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize) {
    InitUI(task);
}

void TaskDialog::InitUI(Task *task) {
    titleCtrl = new wxTextCtrl(this, wxID_ANY);
    descCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    dateCtrl = new wxDatePickerCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT | wxDP_SHOWCENTURY);

    // Создаем элементы для выбора времени (часы и минуты)
    hourCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 23);
    minuteCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59);

    completeCheck = new wxCheckBox(this, wxID_ANY, "Status");

    if (task != nullptr) {
        titleCtrl->SetValue(task->getTitle());
        descCtrl->SetValue(task->getDescription());

        // Установите дату и время из задачи
        wxDateTime taskDateTime = task->getDateFinish();
        dateCtrl->SetValue(taskDateTime);

        // Установите часы и минуты
        if (taskDateTime.IsValid()) {
            hourCtrl->SetValue(taskDateTime.GetHour());
            minuteCtrl->SetValue(taskDateTime.GetMinute());
        } else {
            // Установите значения по умолчанию
            hourCtrl->SetValue(12);
            minuteCtrl->SetValue(0);
        }

        completeCheck->SetValue(!task->getCompleted());
    } else {
        // Установите текущие дату и время по умолчанию для новых задач
        wxDateTime now = wxDateTime::Now();
        dateCtrl->SetValue(now);

        // Установите время на текущее
        hourCtrl->SetValue(now.GetHour());
        minuteCtrl->SetValue(now.GetMinute());
    }

    // 1. Сетка для меток и полей
    auto* grid = new wxFlexGridSizer(4, 10, 10); // 4 колонки
    grid->Add(new wxStaticText(this, wxID_ANY, "Name:"));
    grid->Add(titleCtrl, 1, wxEXPAND);
    grid->Add(new wxStaticText(this, wxID_ANY, "Description:"));
    grid->Add(descCtrl, 1, wxEXPAND);
    grid->Add(new wxStaticText(this, wxID_ANY, "Completion date:"));
    grid->Add(dateCtrl, 1, wxEXPAND);

    // Добавьте элементы для выбора времени
    auto* timeSizer = new wxBoxSizer(wxHORIZONTAL);
    timeSizer->Add(hourCtrl, 0, wxRIGHT, 5);
    timeSizer->Add(new wxStaticText(this, wxID_ANY, ":"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    timeSizer->Add(minuteCtrl, 0);

    grid->Add(new wxStaticText(this, wxID_ANY, "Completion time:"));
    grid->Add(timeSizer, 1, wxEXPAND);

    // 2. Общий вертикальный sizer
    auto* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(grid, 0, wxALL | wxEXPAND, 10);
    vbox->Add(completeCheck, 0, wxALL, 10);

    auto* btnSizer = new wxStdDialogButtonSizer();
    btnSizer->AddButton(new wxButton(this, wxID_OK));
    btnSizer->AddButton(new wxButton(this, wxID_CANCEL));
    btnSizer->Realize();
    vbox->Add(btnSizer, 0, wxALL | wxALIGN_CENTER, 10);

    SetSizerAndFit(vbox);
    Layout();
    Centre();
}

wxString TaskDialog::GetTitleValue() const {
    return titleCtrl->GetValue();
}

wxString TaskDialog::GetDescriptionValue() const {
    return descCtrl->GetValue();
}

wxDateTime TaskDialog::GetDateTimeValue() const {
    // Получите дату из dateCtrl
    wxDateTime date = dateCtrl->GetValue();

    // Получите время из spin-контролов
    int hours = hourCtrl->GetValue();
    int minutes = minuteCtrl->GetValue();

    // Установите время
    date.SetHour(hours);
    date.SetMinute(minutes);
    date.SetSecond(0); // Установите секунды в 0

    return date;
}

bool TaskDialog::GetCompletedValue() const {
    return completeCheck->GetValue();
}

void TaskDialog::OnOk(wxCommandEvent &event) {
    wxString title = titleCtrl->GetValue();
    wxDateTime dateTime = GetDateTimeValue();
    
    if (title.empty()) {
        wxMessageBox("Task name cannot be empty");
        return;
    }
    
    // Получите текущую дату и время
    wxDateTime now = wxDateTime::Now();
    
    if (dateTime < now) {
        wxMessageBox("Date and time cannot be in the past");
        return;
    }
    
    EndModal(wxID_OK);
}

void TaskDialog::OnCancel(wxCommandEvent &event) {
    EndModal(wxID_CANCEL);
}