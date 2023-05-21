#include "calc.hpp"

#include <wx/wx.h>

#include "mainframe.hpp"

bool App::OnInit() {
	MainFrame* main_frame = new MainFrame("Calculator");
	main_frame->SetClientSize(500, 400);
	main_frame->Center();
	main_frame->Show();
	return true;
}

wxIMPLEMENT_APP(App);
