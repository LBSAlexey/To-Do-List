//
// Created by Лёха on 09.08.2025.
//

#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <wx/dialog.h>         // базовый класс wxDialog
#include <wx/textctrl.h>       // для title и description
#include <wx/datectrl.h>       // базовый класс для wxDatePickerCtrl
#include <wx/dateevt.h>        // события от даты
#include <wx/checkbox.h>       // для галочки "выполнено"
#include <wx/sizer.h>          // компоновка (BoxSizer / GridSizer)
#include <wx/button.h>         // кнопки OK / Cancel
#include <wx/stattext.h>       // подписи к полям
#include <wx/msgdlg.h>         // всплывающие окна (ошибки)
#include <wx/datetime.h>       // работа с датой
#include <wx/timer.h>

#include "../model/Task.h"     // если хочешь передавать/редактировать задачу



class TaskDialog : public wxDialog {
public:
    TaskDialog(wxWindow* parent, const wxString& title, Task* task = nullptr);

    wxString GetTitleValue() const;
    wxString GetDescriptionValue() const;
    wxDateTime GetDateValue() const;
    bool GetCompletedValue() const;

private:
    wxTextCtrl* titleCtrl = nullptr;
    wxTextCtrl* descCtrl = nullptr;
    wxDatePickerCtrl* dateCtrl = nullptr;
    wxTimer *timeCtrl = nullptr;
    wxCheckBox* completeCheck = nullptr;

    void InitUI(Task* task = nullptr); // если task != nullptr → редактирование

    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);


};


#endif //TASKDIALOG_H
