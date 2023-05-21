#ifndef DASHBOARD_FRAME_HPP
#define DASHBOARD_FRAME_HPP


#include <wx/frame.h>
#include <wx/textctrl.h>
#include <vector>
#include <sqlite3.h>

#include "Note.hpp"

class DashboardFrame : public wxFrame
{
public:
    DashboardFrame();

    void OnNoteSelected(wxCommandEvent& event);
    void FetchNotesFromDatabase();
    void OnAddNoteClicked(wxCommandEvent& event);
    void SaveNoteToDatabase(const Note& note);
    void RefreshButtonLayout(wxCommandEvent& event);

private:
    std::vector<Note> notes;
    wxTextCtrl* titleTextCtrl;
};

#endif // DASHBOARD_FRAME_HPP