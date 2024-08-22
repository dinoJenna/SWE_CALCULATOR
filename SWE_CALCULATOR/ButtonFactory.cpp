#include "ButtonFactory.h"


wxButton* ButtonFactory::CreateButton(wxWindow* parent, const wxString& label)
{
	return new wxButton(parent, wxID_ANY, label);
}

wxButton* ButtonFactory::CreateNumButton(wxWindow* parent, int num)
{
	return CreateButton(parent, wxString::Format("%d", num));
}

wxButton* ButtonFactory::CreateOpButton(wxWindow* parent, const wxString& op)
{
	return CreateButton(parent, op);
}

wxButton* ButtonFactory::CreateFnctnButton(wxWindow* parent, const wxString& funct)
{
	return CreateButton(parent, funct);
}

