#pragma once
#include "wx/wx.h"

class Singleton
{
public:
	static Singleton* Instance();
	//new calculation method 
	double Calculate(const wxString& expression);

protected:
	Singleton();

private:
	static Singleton* _instance;
};