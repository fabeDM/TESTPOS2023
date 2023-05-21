#include "hexEditorFrame.hpp"

HexEditorFrame::HexEditorFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    textCtrlHex = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                 wxDefaultPosition, wxSize(500, 200),
                                 wxTE_MULTILINE | wxTE_RICH);

    textCtrlAscii = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                                   wxDefaultPosition, wxSize(500, 200),
                                   wxTE_MULTILINE | wxTE_RICH);

    textCtrlHex->Bind(wxEVT_TEXT, &HexEditorFrame::HexToAscii, this);

    mainSizer->Add(textCtrlHex, 5, wxEXPAND | wxALL, 10);
    mainSizer->Add(textCtrlAscii, 5, wxEXPAND | wxALL, 10);

    SetSizerAndFit(mainSizer);
}

void HexEditorFrame::HexToAscii(wxCommandEvent& event)
{
    wxString hexText = textCtrlHex->GetValue();
    wxString asciiText;

    if (hexText.length() % 2 == 0) {

        for (size_t i = 0; i < hexText.length(); i += 2) {

            wxString hexByte = hexText.Mid(i, 2);

            long value;

            if (hexByte.ToLong(&value, 16)) {

                char asciiChar = static_cast<char>(value);
                asciiText += asciiChar;
            }
        }
    }

    textCtrlAscii->SetValue(asciiText);
}
