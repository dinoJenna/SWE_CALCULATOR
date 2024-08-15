#pragma once
#include "wx/wx.h"


class ButtonFactory
{
public:
	static wxButton* CreateButton(wxWindow* parent, const wxString& label, const wxPoint& pos, const wxSize& size);
};

