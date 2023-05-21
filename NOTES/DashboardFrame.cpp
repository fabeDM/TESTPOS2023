#include "DashboardFrame.hpp"
#include "EditNoteFrame.hpp"
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/msgdlg.h>
#include <wx/event.h>

DashboardFrame::DashboardFrame()
    : wxFrame(nullptr, wxID_ANY, "Note Dashboard", wxDefaultPosition, wxSize(800, 800))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create a sizer for the input area
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    // TextCtrl for entering new note title
    titleTextCtrl = new wxTextCtrl(this, wxID_ANY);
    inputSizer->Add(titleTextCtrl, 1, wxALL | wxEXPAND, 5);

    // Button to add new note
    wxButton* addButton = new wxButton(this, wxID_ANY, "Add Note");
    addButton->Bind(wxEVT_BUTTON, &DashboardFrame::OnAddNoteClicked, this);
    inputSizer->Add(addButton, 0, wxALL, 5);

    // Button to refresh dashboard
    wxButton* refreshButton = new wxButton(this, wxID_ANY, "Refresh");
    refreshButton->Bind(wxEVT_BUTTON, &DashboardFrame::RefreshButtonLayout, this);
    inputSizer->Add(refreshButton, 0, wxALL, 5);

    mainSizer->Add(inputSizer, 0, wxEXPAND | wxALL, 10);

    // Create a grid sizer for the note boxes
    wxGridSizer* gridSizer = new wxGridSizer(5, 3, 10, 10);

    // Create note boxes
    FetchNotesFromDatabase();

    for (size_t i = 0; i < notes.size(); ++i)
    {
        wxString title = notes[i].title;
        wxButton* button = new wxButton(this, wxID_HIGHEST + i, title, wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
        button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DashboardFrame::OnNoteSelected), nullptr, this);
        gridSizer->Add(button, 0, wxALL | wxEXPAND, 10);
    }

    mainSizer->Add(gridSizer, 1, wxALL | wxEXPAND, 10);

    SetSizerAndFit(mainSizer);
}

void DashboardFrame::OnNoteSelected(wxCommandEvent& event)
{
    FetchNotesFromDatabase();
    int selectedNoteIndex = event.GetId() - wxID_HIGHEST;

    // Open the EditNoteFrame for the selected note
    EditNoteFrame* editFrame = new EditNoteFrame(this, notes[selectedNoteIndex], nullptr);
    editFrame->Show();
}

void DashboardFrame::FetchNotesFromDatabase()
{
    // Open the database connection
    sqlite3* database;
    int rc = sqlite3_open("notes.db", &database);

    if (rc)
    {
        wxMessageBox("Failed to open the database!");
        return;
    }

    // Create the notes table if it doesn't exist
    wxString createTableQuery = "CREATE TABLE IF NOT EXISTS notes (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, content TEXT)";
    rc = sqlite3_exec(database, createTableQuery.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK)
    {
        wxMessageBox("Failed to create the notes table!");
        sqlite3_close(database);
        return;
    }

    // Fetch all notes from the database
    wxString selectQuery = "SELECT title, content FROM notes";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(database, selectQuery.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        wxMessageBox("Failed to prepare the SELECT statement!");
        sqlite3_close(database);
        return;
    }
    // Clear the existing notes vector
    notes.clear();

    // Execute the SELECT statement and fetch the notes
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        wxString title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        wxString content(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        notes.push_back(Note(title, content));
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(database);
}

void DashboardFrame::OnAddNoteClicked(wxCommandEvent& event)
{
    wxString newTitle = titleTextCtrl->GetValue();
    if (!newTitle.IsEmpty())
    {
        // Create a new note with the entered title
        Note newNote(newTitle);

        // Save the new note to the SQLite database
        SaveNoteToDatabase(newNote);

        // Add the new note to the notes vector
        notes.push_back(newNote);

        // Create a new button for the added note
        wxButton* button = new wxButton(this, wxID_HIGHEST + notes.size() - 1, newTitle, wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
        button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DashboardFrame::OnNoteSelected), nullptr, this);

        // Get the grid sizer and insert the new button
        wxSizer* gridSizer = GetSizer()->GetItem(1)->GetSizer();
        gridSizer->Add(button, 0, wxALL | wxEXPAND, 10);

        // Refresh and update the layout
        gridSizer->Layout();
        GetSizer()->Fit(this);

        // Clear the textCtrl
        titleTextCtrl->Clear();
    }
}

void DashboardFrame::SaveNoteToDatabase(const Note& note)
{
    // Open the database connection
    sqlite3* database;
    int rc = sqlite3_open("notes.db", &database);

    if (rc)
    {
        wxMessageBox("Failed to open the database!");
        return;
    }

    wxString query;

    // Prepare the INSERT statement
    query = "INSERT INTO notes (title, content) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        wxMessageBox("Failed to prepare the INSERT statement!");
        sqlite3_close(database);
        return;
    }

    // Bind the values to the statement parameters
    sqlite3_bind_text(stmt, 1, note.title.c_str(), note.title.length(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, note.content.c_str(), note.content.length(), SQLITE_STATIC);

    // Execute the INSERT statement
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        wxMessageBox("Failed to execute the INSERT statement!");
        sqlite3_finalize(stmt);
        sqlite3_close(database);
        return;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database connection
    sqlite3_close(database);
}

void DashboardFrame::RefreshButtonLayout(wxCommandEvent& event)
{
    FetchNotesFromDatabase();
    // Clear the existing buttons
    wxSizer* gridSizer = GetSizer()->GetItem(1)->GetSizer();
    gridSizer->Clear(true);

    // Add new buttons for the updated notes vector
    for (size_t i = 0; i < notes.size(); ++i)
    {
        wxString title = notes[i].title;
        wxButton* button = new wxButton(this, wxID_HIGHEST + i, title, wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
        button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DashboardFrame::OnNoteSelected), nullptr, this);
        gridSizer->Add(button, 0, wxALL | wxEXPAND, 10);
    }

    // Refresh and update the layout
    gridSizer->Layout();
    GetSizer()->Fit(this);
}
