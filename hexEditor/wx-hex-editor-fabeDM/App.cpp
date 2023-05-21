#include "App.hpp"

bool HexEditorApp::OnInit()
{
    HexEditorFrame* frame = new HexEditorFrame("Hex Editor");
    frame->Show();
    return true;
}

wxIMPLEMENT_APP(HexEditorApp);
