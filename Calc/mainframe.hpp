#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	wxTextCtrl* myTextCtrl = nullptr;

	void on_button_add_clicked(wxCommandEvent& evt);
	void on_button_remove_clicked(wxCommandEvent& evt);
	void on_button_equals_clicked(wxCommandEvent& evt);

};

#endif  // MAINFRAME_HPP
