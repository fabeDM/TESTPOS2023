#pragma once

#include <wx/wx.h>

class HexEditorFrame : public wxFrame
{
public:
    HexEditorFrame(const wxString& title);

private:
    void HexToAscii(wxCommandEvent& event);

    wxTextCtrl* textCtrlHex;
    wxTextCtrl* textCtrlAscii;
};
