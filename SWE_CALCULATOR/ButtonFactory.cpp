#include "ButtonFactory.h"


wxButton* ButtonFactory::CreateButton(wxWindow* parent, const wxString& label, const wxPoint& pos, const wxSize& size)
{
	return new wxButton(parent, wxID_ANY, label, pos, size);
}