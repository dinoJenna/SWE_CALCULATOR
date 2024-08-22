#pragma once
#include "wx/wx.h"

class Window : public wxFrame
{
private:
	//text display
	wxTextCtrl* display;
	//updated interface for calculator
	void CreateUI();
	//event handler
	void OnButtonClicked(wxCommandEvent& evt);
	//calculates result
	double Calculate(const wxString& expression);
	bool isOperator(const wxString& token);
	bool isValidExpression(const wxString& expression);

	//event table
	wxDECLARE_EVENT_TABLE();

public:
	//ctor
	Window();
};

