#include "mainframe.hpp"
#include <iostream>
#include <sstream>
#include <wx/wx.h>
#include <wx/spinctrl.h>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);

    wxButton* button7 = new wxButton(panel, wxID_ANY, "7", wxPoint(150, 50), wxSize(50, 50));

    wxButton* button4 = new wxButton(panel, wxID_ANY, "4", wxPoint(150, 100), wxSize(50, 50));

    wxButton* button1 = new wxButton(panel, wxID_ANY, "1", wxPoint(150, 150), wxSize(50, 50));

    wxButton* buttondel = new wxButton(panel, wxID_ANY, "DEL", wxPoint(150, 200), wxSize(100, 50));

    wxButton* button8 = new wxButton(panel, wxID_ANY, "8", wxPoint(200, 50), wxSize(50, 50));

    wxButton* button5 = new wxButton(panel, wxID_ANY, "5", wxPoint(200, 100), wxSize(50, 50));

    wxButton* button2 = new wxButton(panel, wxID_ANY, "2", wxPoint(200, 150), wxSize(50, 50));

    wxButton* button9 = new wxButton(panel, wxID_ANY, "9", wxPoint(250, 50), wxSize(50, 50));

    wxButton* button6 = new wxButton(panel, wxID_ANY, "6", wxPoint(250, 100), wxSize(50, 50));

    wxButton* button3 = new wxButton(panel, wxID_ANY, "3", wxPoint(250, 150), wxSize(50, 50));

    wxButton* button0 = new wxButton(panel, wxID_ANY, "0", wxPoint(250, 200), wxSize(50, 50));

    wxButton* buttondiv = new wxButton(panel, wxID_ANY, "/", wxPoint(300, 50), wxSize(50, 50));

    wxButton* buttonmulti = new wxButton(panel, wxID_ANY, "*", wxPoint(300, 100), wxSize(50, 50));

    wxButton* buttonadd = new wxButton(panel, wxID_ANY, "+", wxPoint(300, 150), wxSize(50, 50));

    wxButton* buttonsub = new wxButton(panel, wxID_ANY, "-", wxPoint(300, 200), wxSize(50, 50));

    wxButton* buttonequals = new wxButton(panel, wxID_ANY, "=", wxPoint(150, 250), wxSize(200, 50));

    myTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 20), wxSize(200, 30));


    button0->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button1->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button2->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button3->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button4->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button5->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button6->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button7->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button8->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    button9->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    buttondiv->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    buttonmulti->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    buttonadd->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);
    buttonsub->Bind(wxEVT_BUTTON, &MainFrame::on_button_add_clicked, this);

    buttondel->Bind(wxEVT_BUTTON, &MainFrame::on_button_remove_clicked, this);

    buttonequals->Bind(wxEVT_BUTTON, &MainFrame::on_button_equals_clicked, this);
}

void MainFrame::on_button_add_clicked(wxCommandEvent& evt) {
    wxButton* button = static_cast<wxButton*>(evt.GetEventObject());
    wxString buttonLabel = button->GetLabel();
    wxString currentText = myTextCtrl->GetValue();
    myTextCtrl->SetValue(currentText + buttonLabel);
}

void MainFrame::on_button_remove_clicked(wxCommandEvent& evt) {
    wxString currentText = myTextCtrl->GetValue();
    myTextCtrl->SetValue("");
}

void MainFrame::on_button_equals_clicked(wxCommandEvent& evt) {
    wxString currentText = myTextCtrl->GetValue();
    std::stringstream calcsstream(currentText.ToStdString());

    double operand1;
    double operand2;
    char op;
    double result;

    calcsstream >> operand1;

    while (calcsstream >> op) {
        
        calcsstream >> operand2;

        if (op == '+') {
            result = operand1 + operand2;
        }
        else if (op == '-') {
            result = operand1 - operand2;
        }
        else if (op == '*') {
            result = operand1 * operand2;
        }
        else if (op == '/') {
            if (operand2 == 0) {
                myTextCtrl->SetValue("Error: Division by zero");
                return;
            }
            result = operand1 / operand2;
        }
        else {
            myTextCtrl->SetValue("Error: Invalid operator");
            return;
        }
    }

    myTextCtrl->SetValue(wxString::Format("%.2f", result));
}

