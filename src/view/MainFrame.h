#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "../controller/TaskController.h"
#include "TaskPanel.h"
#include "TaskDialog.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
    virtual ~MainFrame() = default;
    void InitUI();

private:
    TaskList taskList;
    TaskController controller{taskList};
    TaskPanel* taskPanel = nullptr;

    void OnAddTask(wxCommandEvent& event);
    void OnEditTask(wxCommandEvent& event);
    void OnRemoveTask(wxCommandEvent& event);
    void RefreshTaskPanel();
    void LoadTasksFromFile();
    void SaveTasksToFile();

    enum {
        ID_ADD = wxID_HIGHEST + 1,
        ID_EDIT,
        ID_REMOVE
    };
};

#endif