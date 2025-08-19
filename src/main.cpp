#include <wx/wx.h>
#include "view/MainFrame.h"
#include <wx/uilocale.h>

// В начало ToDoApp::OnInit

class ToDoApp : public wxApp {
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(ToDoApp);

bool ToDoApp::OnInit() {
    // Установка локали
    auto* locale = new wxLocale();
    locale->Init(wxLANGUAGE_ENGLISH); // Используем английский как fallback

    // Установка шрифта с поддержкой кириллицы
    wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Arial");
    // wxSystemSettings::SetFont(wxSYS_DEFAULT_GUI_FONT, font);

    auto* frame = new MainFrame("To-Do List");
    frame->SetClientSize(800, 600);
    frame->SetMinClientSize(wxSize(400, 300));
    frame->Centre();
    frame->Show();
    return true;
}
