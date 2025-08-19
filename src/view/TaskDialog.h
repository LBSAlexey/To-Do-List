#ifndef TASKDIALOG_H
#define TASKDIALOG_H
#include <C:/Users/keklo/CLionProjects/toDoList/src/model/Task.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/msgdlg.h>
#include <wx/datetime.h>
#include <wx/spinctrl.h>  // Добавьте этот заголовок

class TaskDialog : public wxDialog {
public:
    TaskDialog(wxWindow* parent, const wxString& title, Task* task = nullptr);

    wxString GetTitleValue() const;
    wxString GetDescriptionValue() const;
    wxDateTime GetDateTimeValue() const;
    bool GetCompletedValue() const;

private:
    wxTextCtrl* titleCtrl = nullptr;
    wxTextCtrl* descCtrl = nullptr;
    wxDatePickerCtrl* dateCtrl = nullptr;
    wxSpinCtrl* hourCtrl = nullptr;    // Для часов
    wxSpinCtrl* minuteCtrl = nullptr;  // Для минут
    wxCheckBox* completeCheck = nullptr;

    void InitUI(Task* task = nullptr);

    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
};

#endif