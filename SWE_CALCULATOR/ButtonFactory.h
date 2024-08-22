#pragma once
#include "wx/wx.h"


class ButtonFactory
{
public:
	static wxButton* CreateButton(wxWindow* parent, const wxString& label);
	static wxButton* CreateNumButton(wxWindow* parent, int number);
	static wxButton* CreateOpButton(wxWindow* parent, const wxString& op);
	static wxButton* CreateFnctnButton(wxWindow* parent, const wxString& funct);
};

